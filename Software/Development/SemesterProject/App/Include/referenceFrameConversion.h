/*
 * referenceFrameConversion.h
 *
 *  Created on: Apr 9, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_REFERENCEFRAMECONVERSION_H_
#define APP_INCLUDE_REFERENCEFRAMECONVERSION_H_


/*
 * Temporary declarations To be removed
 */
#include "analogAcquisitionManager.h"
void runClosedLoopControl(void);
/*
 * end of temporaty declarations
 */


typedef struct
{
    float DComponent;
    float QComponent;
}DQObject;

typedef struct
{
    float alphaComponent;
    float betaComponent;
}alphaBetaObject;


DQObject abc2dq(float *currentArray, float thetaRad);
alphaBetaObject dq2alphabeta(DQObject *DQVoltage, float thetaRad);

#endif /* APP_INCLUDE_REFERENCEFRAMECONVERSION_H_ */
