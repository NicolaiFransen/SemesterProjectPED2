/*
 * encoderManager.c
 *
 *  Created on: 1 abr. 2019
 *      Author: Aitor Teran
 */

#include "encoderManager.h"


static motorPosSpeed motorPosSpeedObject;


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


    EQep1Regs.QUPRD = 900000;         // Unit Timer for 100Hz at 80 MHz SYSCLKOUT

    EQep1Regs.QDECCTL.bit.QSRC = 00;  // QEP quadrature count mode

    //EQep control:
    EQep1Regs.QEPCTL.bit.FREE_SOFT = 2;
    EQep1Regs.QEPCTL.bit.PCRM = 00;   // PCRM=00 mode - QPOSCNT reset on index event
    EQep1Regs.QEPCTL.bit.SEI = 00;    // Strobe event initialization of position counter. 00->does nothing.
    EQep1Regs.QEPCTL.bit.IEI = 10;    // Index event initialization of counter. 10->init on rising edge.
    EQep1Regs.QEPCTL.bit.SWI = 0;     // Software init of position counter. 0->do nothing.
    EQep1Regs.QEPCTL.bit.SEL = 0;     // Strobe event latch of pos counter. 0->latched on rising edge of QEPS ¿?
    EQep1Regs.QEPCTL.bit.IEL = 01;    // Index event latch of pos counter. 01->latches on rising edge of index.
    EQep1Regs.QEPCTL.bit.QPEN = 1;    // Quadrature pos counter enable/software reset. 1->eQEP pos counter enabled.

    //QCLM REGISTER DETERMINES CONSTANT X vs T.
    EQep1Regs.QEPCTL.bit.QCLM = 1;    // eQEP capture latch mode. 1->latch on unit time out
    EQep1Regs.QEPCTL.bit.UTE = 1;     // Unit Timeout Enable. 1->Enabled.
    EQep1Regs.QEPCTL.bit.WDE = 0;     // Watchdog enable. 0->disabled

    EQep1Regs.QPOSMAX = 0xffffffff;   // Maximum possible counter value.
    EQep1Regs.QPOSINIT = 0;           // Position value used to initialize when index event.

    EQep1Regs.QCAPCTL.bit.CEN = 1;    // QEP Capture Enable
    EQep1Regs.QCAPCTL.bit.CCPS = 6;   // 1/64 for CAP clock prescaler
    EQep1Regs.QCAPCTL.bit.UPPS = 5;   // 1/32 for unit position prescaler

    EDIS;

}


/*
 * Encoder constructor.
 * To be called as motorPosSpeedConstructor(&motorPosSpeedObject);
 */
void motorPosSpeedConstructor(motorPosSpeed *motorPosSpeed)
{
    motorPosSpeed->offsetTheta = 0;
    motorPosSpeed->poles = 2;
    motorPosSpeed->stepsPerCycle = ENCODER_STEPS;
}


/*
 * Function that updates the object containing position info from encoder.
 * To be called as motorPosCalc(&motorPosSpeedObject);
 */
void motorPosCalc(motorPosSpeed *motorPosSpeed)
{
    // Check motor direction: 0=CCW/reverse, 1=CW/forward.
    motorPosSpeed->dir = EQep1Regs.QEPSTS.bit.QDF;

/*    // Save previous angle, for later speed calculation.
    motorPosSpeed->oldThetaRaw = motorPosSpeed->thetaRaw;   // According to my understanding of the datasheet, QPOSLAT already saves Xdelta in a time period.
                                                            // So it should be possible to use that as a value for measuring speed.
*/

    //Update raw angle with counter, remember that QPOSCNT already takes into account direction, QPOSCNT is latched into QPOSLAT.
    motorPosSpeed->thetaRaw = EQep1Regs.QPOSLAT;

    // Check an index occurrence
    if (EQep1Regs.QFLG.bit.IEL == 1) EQep1Regs.QCLR.bit.IEL = 1;   // Clear interrupt flag

    motorPosSpeed->thetaElecOld = motorPosSpeed->thetaElec;
    motorPosSpeed->thetaElec = motorPosSpeed->thetaRaw * motorPosSpeed->poles * 360 / ENCODER_STEPS;    //Transform into electrical angle [º]
    motorPosSpeed->thetaMech = motorPosSpeed->thetaElec * 360 / ENCODER_STEPS;
}


/*
 * Function that updates the object containing speed info from encoder.
 * To be called as motorSpeedCalc(&motorPosSpeedObject);
 */
void motorSpeedCalc(motorPosSpeed *motorPosSpeed)
{
    motorPosSpeed->freqElec = ( motorPosSpeed->thetaElec - motorPosSpeed->thetaElecOld ) * ENCODER_INT_FREQ;
    motorPosSpeed->freqMech = motorPosSpeed->freqElec / motorPosSpeed->poles;                                   //Hz
    motorPosSpeed->rpmMech = motorPosSpeed->freqMech * 60; //To go from Hz to rpm.
}


void clearInterruptFlag(void)
{
    EQep1Regs.QCLR.bit.UTO=1; // Clear interrupt flag
}


int16 readRotorElecAngle(void)
{
    return motorPosSpeedObject.thetaElec;
}

float readRotorElecFreq(void)
{
    return motorPosSpeedObject.freqElec;
}

int16 readRotorMechAngle(void)
{
    return motorPosSpeedObject.thetaMech;
}

float readRotorMechFreq(void)
{
    return motorPosSpeedObject.freqMech;
}

int16 readRotorRPM(void)
{
    return motorPosSpeedObject.rpmMech;
}



void posSpeedFromEncoder(void)
{
    motorPosCalc(&motorPosSpeedObject);
    motorSpeedCalc(&motorPosSpeedObject);
    clearInterruptFlag();
}
