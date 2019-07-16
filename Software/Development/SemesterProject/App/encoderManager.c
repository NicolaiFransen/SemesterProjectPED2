/*
 * encoderManager.c
 *
 *  Created on: 1 abr. 2019
 *      Author: Aitor Teran
 *
 *      This module reads the encoder values, it obtains measurements from the encoder and transforms them into position of it.
 *      Also rotational speed is calculated here.
 *
 *      In order to have accurate measurements in position, the position is calculated at the same rate as the control is executed.
 *      However, if speed was also calculated at this rate, it would lead to error in the measurements at low speed. For this reason,
 *      speed is only updated when there has been an increase of more than 10 degrees.
 *
 *      The module EQep1Regs is used. This is able to update the counter constantly, the position is saved to QPOSCNT register.
 *      When index occurrence happens, this goes back to 0.
 *
 *      Divisions have been avoided in this file as much as possible, instead, inverse of the constants are created to be able to
 *      multiply by them instead of divide.
 *
 *      Encoder is inputing mechanical speed but all the calculations are measured in the electrical environment, then transformed
 *      again to mechanical domain. The relationship between this two depends on the number of pole pairs.
 */

#include "positionCalculator.h"

void initEncoder(void)
{
    EALLOW;

    // Enable internal pull-up for the selected pins
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pull-up on GPIO20 (EQEP1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pull-up on GPIO21 (EQEP1B)
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;   // Enable pull-up on GPIO23 (EQEP1I)

    // Inputs are synchronized to SYSCLKOUT by default.
    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0;  // Sync to SYSCLKOUT GPIO20 (EQEP1A)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 0;  // Sync to SYSCLKOUT GPIO21 (EQEP1B)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 0;  // Sync to SYSCLKOUT GPIO23 (EQEP1I)

    // This specifies which of the possible GPIO pins will be eQEP1 functional pins.
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;   // Configure GPIO20 as EQEP1A
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;   // Configure GPIO21 as EQEP1B
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;   // Configure GPIO23 as EQEP1I

    //EQep1Regs.QUPRD = 900000;         // Unit Timer for 100Hz at 80 MHz SYSCLKOUT

    EQep1Regs.QDECCTL.bit.QSRC = 00;  // QEP quadrature count mode

    //EQep control:
    EQep1Regs.QEPCTL.bit.FREE_SOFT = 2; // Position counter unaffected by emulation suspension.
    EQep1Regs.QEPCTL.bit.PCRM = 01;   // PCRM=00 mode - QPOSCNT reset on index event
                                      // PCRM=01 mode - QPOSCNT reset on MAX POSITION
    EQep1Regs.QEPCTL.bit.SEI = 00;    // Strobe event initialization of position counter. 00->does nothing.
    EQep1Regs.QEPCTL.bit.IEI = 00;    //Do nothing --> 00;
                                      // Index event initialization of counter. 10->init on rising edge.
    EQep1Regs.QEPCTL.bit.SWI = 0;     // Software init of position counter. 0->do nothing.
    EQep1Regs.QEPCTL.bit.SEL = 1;     // Strobe event latch of pos counter. 1-> Clockwise, latch on rise, counterclockwise, latch on fall.
    EQep1Regs.QEPCTL.bit.IEL = 01;    // Index event latch of pos counter. 01->latches on rising edge of index.
    EQep1Regs.QEPCTL.bit.QPEN = 1;    // Quadrature pos counter enable/software reset. 1->eQEP pos counter enabled.

    //QCLM REGISTER DETERMINES CONSTANT X vs T.
    EQep1Regs.QEPCTL.bit.QCLM = 1;    // eQEP capture latch mode. 1->latch on unit time out
    EQep1Regs.QEPCTL.bit.UTE = 1;     // Unit Timeout Enable. 1->Enabled.
    EQep1Regs.QEPCTL.bit.WDE = 0;     // Watchdog enable. 0->disabled

    EQep1Regs.QPOSMAX = ENCODER_STEPS - 1;         // Maximum possible counter value.
    EQep1Regs.QPOSINIT = 0;           // Position value used to initialize when index event.

    EQep1Regs.QCAPCTL.bit.CEN = 1;    // QEP Capture Enable
    EQep1Regs.QCAPCTL.bit.CCPS = 6;   // 1/64 for CAP clock prescaler
    EQep1Regs.QCAPCTL.bit.UPPS = 5;   // 1/32 for unit position prescaler

    EDIS;

    rotorPosSpeedConstructor();
}


void clearInterruptFlag(void)
{
    EQep1Regs.QCLR.bit.UTO=1; // Clear interrupt flag
}


float obtainDeltaTheta(motorPosSpeed *motorPosSpeedObject)
{
    //Calculate delta and check if it has jumped to next lap.
    float deltaTheta;
    deltaTheta = fabs(motorPosSpeedObject->rotorThetaElec - motorPosSpeedObject->rotorThetaElecOld);
    if (deltaTheta > PI) deltaTheta = fabs(TWO_PI - deltaTheta);
    return deltaTheta;
}


void updateSpeed(motorPosSpeed *motorPosSpeedObject, float deltaTheta)
{
    //Check direction and calculate electrical frequency.
    if (motorPosSpeedObject->dir == 0) motorPosSpeedObject->rotorElecSpeedRadS = - deltaTheta * 1000000 / motorPosSpeedObject->rotorSpeedTimeCount;
    else motorPosSpeedObject->rotorElecSpeedRadS = deltaTheta * 1000000 / motorPosSpeedObject->rotorSpeedTimeCount; //Going reverse direction.


    //Update other values.
    motorPosSpeedObject->rotorThetaElecOld = motorPosSpeedObject->rotorThetaElec;
    motorPosSpeedObject->rotorSpeedTimeCount = 0;
}


/*
 *  To ensure the maximum accuracy in the position, the period between two measurements is minimized to switching frequency.
 *  However, the rotor speed cannot be calculated at the same frequency since it will lead to errors.
 *  Instead, the speed will be calculated every 10 degrees.
 */
void rotorSpeedCalc(motorPosSpeed *motorPosSpeedObject)
{
    float deltaTheta;

    deltaTheta = obtainDeltaTheta(motorPosSpeedObject);

//    if ((getUartCounter() == 3)) UARTIntPrint("dt ", (int)((deltaTheta) * 10000));

    //Speed is only calculated every 30 degrees.
    if (deltaTheta > DEG_30_TO_RAD || motorPosSpeedObject->rotorSpeedTimeCount > 15000)
        //Enter here either if there have been more than 10º or if a time longer than 15ms has passed (for low speeds).

    {
        updateSpeed(motorPosSpeedObject, deltaTheta);
    }
}


/*
 * Obtain the rotor angle from encoder.
 */
void rotorPosCalc(motorPosSpeed *motorPosSpeedObject)
{
    /*
     * Only update the direction flag if there's movement.
     */
    if (motorPosSpeedObject->rotorThetaMech != 0)
    {
        // Check rotor direction: 0=CCW/reverse, 1=CW/forward.
        motorPosSpeedObject->dir = EQep1Regs.QEPSTS.bit.QDF;
    }


    //Update raw angle with counter, remember that QPOSCNT already takes into account direction.
    motorPosSpeedObject->rotorThetaRaw = EQep1Regs.QPOSCNT;
    //Transform into electrical angle [rad]
    motorPosSpeedObject->rotorThetaElec = motorPosSpeedObject->rotorThetaRaw * THETA_RAW_TO_THETA_ELEC;
    if (motorPosSpeedObject->rotorThetaElec >= TWO_PI) motorPosSpeedObject->rotorThetaElec -= TWO_PI;
    if (motorPosSpeedObject->rotorThetaElec < 0) motorPosSpeedObject->rotorThetaElec += TWO_PI;
    motorPosSpeedObject->rotorThetaMech = motorPosSpeedObject->rotorThetaRaw * THETA_RAW_TO_THETA_MECH;

//    if (getUartCounter() == 3) UARTIntPrint("th ", (int)(motorPosSpeedObject->rotorThetaElec));

    motorPosSpeedObject->rotorSpeedTimeCount += SW_PERIOD_US;
}
