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
    float iqsRef = getIqReferenceTorqueControl();
    float idsRef = readIdReference();
//    float iqsRef = 50;//TORQUE_TO_Q_CURRENT * getTorqueReference();
//    float idsRef = 50;//readIdReference();
    if (fabs(idsRef) > 1) motorPosSpeedObject->slipSpeedRadS = TR_INVERSE * iqsRef / idsRef;
    motorPosSpeedObject->rotorFluxSpeedRadS = readRotorElecSpeedRadS() + motorPosSpeedObject->slipSpeedRadS;
//    if (getUartCounter() == 3) UARTIntPrint("dr ", (int)(idsRef));
//    if (getUartCounter() == 2) UARTIntPrint("qr ", (int)(iqsRef));
}


/*
 * In order to obtain the slip angle of the rotor flux, the speed must be integrated.
 * This function must be called at switching frequency.
 */
void calcSlipAngle(motorPosSpeed *motorPosSpeedObject)
{
    static float previousRotorTethaElec = 0;

    motorPosSpeedObject->slipAngleRad = motorPosSpeedObject->slipSpeedRadS * SW_PERIOD_S;
//    sign(motorPosSpeedObject->dir)*
    motorPosSpeedObject->rotorFluxPosRad += -motorPosSpeedObject->slipAngleRad + (motorPosSpeedObject->rotorThetaElec - previousRotorTethaElec);

    //Consider flux limits and correct
    if (motorPosSpeedObject->rotorFluxPosRad >= TWO_PI) motorPosSpeedObject->rotorFluxPosRad -= TWO_PI;
    if (motorPosSpeedObject->rotorFluxPosRad >= TWO_PI) motorPosSpeedObject->rotorFluxPosRad -= TWO_PI;
    if (motorPosSpeedObject->rotorFluxPosRad < 0) motorPosSpeedObject->rotorFluxPosRad += TWO_PI;
    if (motorPosSpeedObject->rotorFluxPosRad < 0) motorPosSpeedObject->rotorFluxPosRad += TWO_PI;

//        if ((getUartCounter() == 3)) UARTIntPrint("d ", (int)(motorPosSpeedObject->dir));
    //    if ((getUartCounter() == 3)) UARTIntPrint("s ", (int)(motorPosSpeedObject->rotorFluxPosRad*100));
//    if ((getUartCounter() == 3)) UARTIntPrint("re ", (int)(motorPosSpeedObject->rotorThetaElec * 100));
//    if ((getUartCounter() == 4)) UARTIntPrint("rf ", (int)(motorPosSpeedObject->rotorFluxPosRad * 100));


    previousRotorTethaElec = motorPosSpeedObject->rotorThetaElec;
}

int sign(float variable)
{
    if (variable) return 1;
    else if (!variable) return -1;
    else return 0;
}
