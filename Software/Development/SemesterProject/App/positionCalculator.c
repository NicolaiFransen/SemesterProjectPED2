/*
 * PositionCalculator.c
 *
 *  Created on: 17 abr. 2019
 *      Author: Aitor Teran
 */


#include "positionCalculator.h"


static motorPosSpeed motorPosSpeedObject;


/*
 * Encoder constructor.
 */
void rotorPosSpeedConstructor(void)
{
    motorPosSpeedObject.dir = 0;
    motorPosSpeedObject.rotorThetaMech = 0;
    motorPosSpeedObject.rotorThetaElec = 0;
    motorPosSpeedObject.rotorThetaElecOld = 0;
    motorPosSpeedObject.rotorSpeedTempCount = 0;
    motorPosSpeedObject.rotorSpeedRadS = 0;
}


/*
 * Obtain position and speed of the rotor.
 * Should be called at switch freq.
 */
void posSpeedFromEncoder()
{
    rotorPosCalc(&motorPosSpeedObject);
    rotorSpeedCalc(&motorPosSpeedObject);
    clearInterruptFlag();
}


void rotorFluxPosSpeed()
{
    calcSlipSpeed(&motorPosSpeedObject);
}



float readRotorElecAngleRad(void)
{
    return motorPosSpeedObject.rotorThetaElec;
}

float readRotorMechAngleRad(void)
{
    return motorPosSpeedObject.rotorThetaMech;
}


float readRotorSpeedRadS(void)
{
    return motorPosSpeedObject.rotorSpeedRadS;
}

float readRotorElecFreqHz(void)
{
    return motorPosSpeedObject.rotorSpeedRadS * RAD_TO_REV;
}

float readRotorMechFreqHz(void)
{
    return motorPosSpeedObject.rotorSpeedRadS * RAD_TO_REV * POLE_PAIRS_INVERSE;    //Hz
}

int16 readRotorRPM(void)
{
    return (int16) (motorPosSpeedObject.rotorSpeedRadS * RAD_TO_REV * POLE_PAIRS_INVERSE * 60);    //rpm
}
