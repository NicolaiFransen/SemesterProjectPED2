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
 *      again to mechanical domain. The relationship between this two depends on the number of poles.
 *
 */

#include "encoderManager.h"


static motorPosSpeed motorPosSpeedObject;
static float poles_inverse;


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
    EQep1Regs.QEPCTL.bit.PCRM = 00;   // PCRM=00 mode - QPOSCNT reset on index event
    EQep1Regs.QEPCTL.bit.SEI = 00;    // Strobe event initialization of position counter. 00->does nothing.
    EQep1Regs.QEPCTL.bit.IEI = 00;    //Do nothing --> 10;    // Index event initialization of counter. 10->init on rising edge.
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

    motorPosSpeedConstructor();
}


/*
 * Encoder constructor.
 * To be called as motorPosSpeedConstructor(&motorPosSpeedObject);
 */
void motorPosSpeedConstructor(void)
{
    motorPosSpeedObject.poles = 2;
    motorPosSpeedObject.dir = 0;
    motorPosSpeedObject.thetaMech = 0;
    motorPosSpeedObject.thetaElec = 0;
    motorPosSpeedObject.thetaElecOld = 0;
    motorPosSpeedObject.speedTempCount = 0;
    motorPosSpeedObject.freqElec = 0;
    motorPosSpeedObject.freqMech = 0;
    motorPosSpeedObject.rpmMech = 0;
    poles_inverse = (float) (1.0 / motorPosSpeedObject.poles);
}


void clearInterruptFlag(void)
{
    EQep1Regs.QCLR.bit.UTO=1; // Clear interrupt flag
}


/*
 * Obtain position and speed of the rotor.
 * Should be called at switch freq.
 */
void posSpeedFromEncoder(void)
{
    motorPosCalc();
    motorSpeedCalc();
    clearInterruptFlag();
}


/*
 * Function that updates the object containing position info from encoder.
 * To be called as motorPosCalc(&motorPosSpeedObject);
 */
void motorPosCalc(void)
{
    // Check motor direction: 0=CCW/reverse, 1=CW/forward.
    motorPosSpeedObject.dir = EQep1Regs.QEPSTS.bit.QDF;

    //Update raw angle with counter, remember that QPOSCNT already takes into account direction.
    motorPosSpeedObject.thetaRaw = EQep1Regs.QPOSCNT;

    // Check an index occurrence
    if (EQep1Regs.QFLG.bit.IEL == 1) EQep1Regs.QCLR.bit.IEL = 1;   // Clear interrupt flag

    //Transform into electrical angle [º]
    motorPosSpeedObject.thetaElec = motorPosSpeedObject.thetaRaw * motorPosSpeedObject.poles * REV_TO_RAD * ENCODER_STEPS_INVERSE;
    if (motorPosSpeedObject.thetaElec >= TWO_PI) motorPosSpeedObject.thetaElec -= TWO_PI;
    motorPosSpeedObject.thetaMech = motorPosSpeedObject.thetaRaw * REV_TO_RAD * ENCODER_STEPS_INVERSE;

    motorPosSpeedObject.speedTempCount += SW_PERIOD_US;
}


/*
 *  To ensure the maximum accuracy in the position, the period between two measurements is minimized to switching frequency.
 *  However, the rotor speed cannot be calculated at the same frequency since it will lead to errors.
 *  Instead, the speed will be calculated every 10 degrees.
 */
void motorSpeedCalc(void)
{
    float deltaTheta;

    //Calculate delta and check if it has jumped to next lap.
    deltaTheta = fabs(motorPosSpeedObject.thetaElec - motorPosSpeedObject.thetaElecOld);
    if (deltaTheta > PI) deltaTheta = fabs(TWO_PI - deltaTheta);

    //Measure speed every 10 degrees.
    if (deltaTheta > DEG_10_TO_RAD)
    {
        if (motorPosSpeedObject.dir == 0) motorPosSpeedObject.freqElec = deltaTheta * RAD_TO_REV * 1000000 / motorPosSpeedObject.speedTempCount;
        else motorPosSpeedObject.freqElec = - deltaTheta * RAD_TO_REV * 1000000 / motorPosSpeedObject.speedTempCount; //Going reverse direction.
        motorPosSpeedObject.thetaElecOld = motorPosSpeedObject.thetaElec;
        motorPosSpeedObject.speedTempCount = 0;
    }

    //Calculate other speeds.
    motorPosSpeedObject.freqMech = motorPosSpeedObject.freqElec * poles_inverse;    //Hz
    motorPosSpeedObject.rpmMech = (int16) (motorPosSpeedObject.freqMech * 60.0);    //To go from Hz to rpm.
}


float readRotorElecAngleRad(void)
{
    return motorPosSpeedObject.thetaElec;
}

float readRotorElecFreqHz(void)
{
    return motorPosSpeedObject.freqElec;
}

float readRotorMechAngleDeg(void)
{
    return motorPosSpeedObject.thetaMech;
}

float readRotorMechFreqHz(void)
{
    return motorPosSpeedObject.freqMech;
}

int16 readRotorRPM(void)
{
    return motorPosSpeedObject.rpmMech;
}
