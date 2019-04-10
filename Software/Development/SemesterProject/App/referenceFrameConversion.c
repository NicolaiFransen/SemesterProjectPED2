/*
 * referenceFrameConversion.c
 *
 *  Created on: Apr 8, 2019
 *      Author: Nicolas
 *      This module performs the calculation for changing the
 *      reference frame. C28x_FPU_Fast_RTS library is used.
 *
 *      Detailed explanation of the use of every function is found in
 *      functions' header.
 *
 *      Included reference frame conversions:
 *          **abc2dq()
 *          **dq2alphabeta()
 *
 */
#include <math.h>
#include "Constants.h"
#include "referenceFrameConversion.h"

/*
 * This function performs the calculation of the dq components.
 * It uses theta in radians, provided by the controlTask
 * and abc components. A pointer pointing to the first element of
 * the currents' array is the required argument.
 * The return consist of a structure which contains
 *
 * USE
 *     float ABCCurrent[3] = {0, 0, 0}, theta;
 *     DQObject DQCurrent;
 *
 *     theta = getStatorElecAngle();
 *     getCurrentMeasurements(&ABCCurrent[0]);
 *     DQCurrent = abc2dq(&ABCCurrent[0], theta);
 *
 */
DQObject abc2dq(float *currentArray, float thetaRad)
{
    DQObject DQCurrent;

    float AComponent = *currentArray;
    float BComponent = *(currentArray + 1);
    float CComponent = *(currentArray + 2);

    DQCurrent.DComponent = TWO_DIV_3 * (AComponent * cos(thetaRad) +
                                        BComponent * cos(thetaRad - TWO_PI_DIV_3) +
                                        CComponent * cos(thetaRad - FOUR_PI_DIV_3));

    DQCurrent.QComponent = -TWO_DIV_3 * (AComponent * sin(thetaRad) +
                                         BComponent * sin(thetaRad - TWO_PI_DIV_3) +
                                         CComponent * sin(thetaRad - FOUR_PI_DIV_3));
    return DQCurrent;
}


/*
 * This function performs the calculation of the alpha-beta components.
 * It uses theta in radians and DQ components provided by controlTask.
 * It returns a structure with both alpha and beta components.
 *
 * USE
 *     alphaBetaObject abVoltage;
 *     abVoltage = dq2alphabeta(&DQVoltage, theta);
 *
 */
alphaBetaObject dq2alphabeta(DQObject *DQVoltage, float thetaRad)
{
    alphaBetaObject alphaBetaVoltage;

    alphaBetaVoltage.alphaComponent = DQVoltage->DComponent * cos(thetaRad) -
                                      DQVoltage->QComponent * sin(thetaRad);

    alphaBetaVoltage.betaComponent = DQVoltage->DComponent * sin(thetaRad) +
                                     DQVoltage->QComponent * cos(thetaRad);

    return alphaBetaVoltage;
}

