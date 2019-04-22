/*
 * referenceFrameConversion.h
 *
 *  Created on: Apr 9, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_REFERENCEFRAMECONVERSION_H_
#define APP_INCLUDE_REFERENCEFRAMECONVERSION_H_

typedef struct
{
    float dComponent;
    float qComponent;
}dqObject;

typedef struct
{
    float alphaComponent;
    float betaComponent;
}alphaBetaObject;


dqObject abc2dq(float *currentArray, float thetaRad);
alphaBetaObject dq2alphabeta(dqObject *dqVoltage, float thetaRad);

#endif /* APP_INCLUDE_REFERENCEFRAMECONVERSION_H_ */
