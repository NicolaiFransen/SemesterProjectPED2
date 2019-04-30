/*
 * PositionCalculator.c
 *
 *  Created on: 17 abr. 2019
 *      Author: Aitor Teran
 *
 *      The module gathers information about the position and speed of the rotor as well  as of it's flux.
 *      The modules encoderManager and slipAngleCalculator are submodules of this and their functions are
 *      called from this module.
 *      All information regarding the position of the rotor or its flux is read from this module.
 *      motorPosSpeedObject includes all the information.
 *
 *      Function to call to calculate parameters is getRotorPosSpeedParameters();
 *      It should be called at switching frequency. This function will then call functions located at
 *      encoderManager.c and slipAngleCalculator.c to obtain encoder readings and estimate flux characteristics.
 */


#include "positionCalculator.h"


static motorPosSpeed motorPosSpeedObject;


/*
 * Obtain position and speed of both rotor and its flux.
 */
void getRotorPosSpeedParameters()
{
    posSpeedFromEncoder();
    rotorFluxPosSpeed();
}


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


/*
 * Obtain position and speed of the rotor flux.
 */
void rotorFluxPosSpeed()
{
    calcSlipSpeed(&motorPosSpeedObject);
    calcSlipAngle(&motorPosSpeedObject);
}


//Read rotor related angles.
float readRotorElecAngleRad(void)
{
    return motorPosSpeedObject.rotorThetaElec;
}

float readRotorMechAngleRad(void)
{
    return motorPosSpeedObject.rotorThetaMech;
}


//Read rotor related speeds.
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


//Read rotor flux speed and position.
float readRotorFluxAngleRad(void)
{
    return motorPosSpeedObject.rotorFluxPosRad;
}

float readRotorFluxSpeedRadS(void)
{
    return motorPosSpeedObject.rotorFluxSpeedRadS;
}


int readRotorThetaRaw(void)
{
    return motorPosSpeedObject.rotorThetaRaw;
}
