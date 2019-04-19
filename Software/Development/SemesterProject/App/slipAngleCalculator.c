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
}


/*
 * In order to obtain the slip angle of the rotor flux, the speed must be integrated.
 */
void calcSlipAngle(motorPosSpeed *motorPosSpeedObject)
{

}


void calcRotorFluxPosSpeed(motorPosSpeed *motorPosSpeedObject)
{
    calcSlipSpeed(motorPosSpeedObject);
    calcSlipAngle(motorPosSpeedObject);

    motorPosSpeedObject->rotorFluxSpeedRadS = readRotorSpeedRadS() + motorPosSpeedObject->slipSpeedRadS;
}
