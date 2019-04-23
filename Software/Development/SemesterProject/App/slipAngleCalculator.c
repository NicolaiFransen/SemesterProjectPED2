/*
 * SlipAngleCalculator.c
 *
 *  Created on: 17 abr. 2019
 *      Author: Aitor Teran
 *
 *      In this module, information about the position and speed of the rotor flux is calculated.
 *      This values are estimations.
 *      The functions are called from positionCalculator.c
 */

#include "positionCalculator.h"


/*
 * Obtain the slip speed of the rotor flux.
 */
void calcSlipSpeed(motorPosSpeed *motorPosSpeedObject)
{
    float iqsRef = TWO_DIV_3 * LR * LM_INVERSE * LAMDA_R_INVERSE * getTorqueReference();
    motorPosSpeedObject->slipSpeedRadS = TR_INVERSE * iqsRef * ID_RATED_INVERSE;
    motorPosSpeedObject->rotorFluxSpeedRadS = readRotorSpeedRadS() + motorPosSpeedObject->slipSpeedRadS;
}


/*
 * In order to obtain the slip angle of the rotor flux, the speed must be integrated.
 * This function must be called at switching frequency.
 */
void calcSlipAngle(motorPosSpeed *motorPosSpeedObject)
{
    motorPosSpeedObject->slipAngleRad = motorPosSpeedObject->slipSpeedRadS * SW_PERIOD_S;
    motorPosSpeedObject->rotorFluxPosRad = motorPosSpeedObject->slipAngleRad + motorPosSpeedObject->rotorThetaElec;
    //Consider flux limits and correct
    if (motorPosSpeedObject->rotorFluxPosRad >= TWO_PI) motorPosSpeedObject->rotorFluxPosRad -= TWO_PI;
    if (motorPosSpeedObject->rotorFluxPosRad < 0) motorPosSpeedObject->rotorFluxPosRad += TWO_PI;
}
