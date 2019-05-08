/*
 * PIController.h
 *
 *  Created on: 2. apr. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_PICONTROLLER_H_
#define APP_INCLUDE_PICONTROLLER_H_

//
// Includes
//
#include "Constants.h"


typedef struct PIobjectTag
{
    float KP;
    float KI;
    float KPInverse;
    float integrationOfError;
    float previousOutput;
    float previousLimitedOutput;
    int antiWindupFlag;
} PIobject;

/*
 * Initialization functions
 */
void PIObject_Constructor(PIobject *PIcontroller, float KP, float KI, int antiWindupFlag);

float PiCalculation(PIobject *PIcontroller, float reference, float measurementValue);

/*
 * Function to check saturation of output
 */
int isOutputSaturatedPositive(float PIoutput);
int isOutputSaturatedNegative(float PIoutput);

#endif /* APP_INCLUDE_PICONTROLLER_H_ */
