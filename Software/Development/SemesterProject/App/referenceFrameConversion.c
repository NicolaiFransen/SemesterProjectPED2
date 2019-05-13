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
#include "queueObject.h"

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
dqObject abc2dq(float *abcArray, float thetaRad)
{
    dqObject dqStruct;
    int dummyVar = 0;

    float aComponent = *abcArray;
    float bComponent = *(abcArray + 1);
    float cComponent = *(abcArray + 2);

    dqStruct.dComponent = TWO_DIV_3 * (aComponent * cos(thetaRad) +
                                       bComponent * cos(thetaRad - TWO_PI_DIV_3) +
                                       cComponent * cos(thetaRad - FOUR_PI_DIV_3));

    dqStruct.qComponent = -TWO_DIV_3 * (aComponent * sin(thetaRad) +
                                        bComponent * sin(thetaRad - TWO_PI_DIV_3) +
                                        cComponent * sin(thetaRad - FOUR_PI_DIV_3));

//    if ((dummyVar++ % 4) == 0 )
//    {
//        UARTIntPrint("qm ", (int)(dqStruct.qComponent * 100));
//        UARTIntPrint("dm ", (int)(dqStruct.dComponent * 100));
//    }

    return dqStruct;
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
alphaBetaObject dq2alphabeta(dqObject *dqStruct, float thetaRad)
{
    alphaBetaObject alphaBetaStruct;

    alphaBetaStruct.alphaComponent =    dqStruct->dComponent * cos(thetaRad) -
                                        dqStruct->qComponent * sin(thetaRad);

    alphaBetaStruct.betaComponent =     dqStruct->dComponent * sin(thetaRad) +
                                        dqStruct->qComponent * cos(thetaRad);

    return alphaBetaStruct;
}

