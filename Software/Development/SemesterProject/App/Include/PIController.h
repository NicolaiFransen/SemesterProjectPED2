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
    float integrationOfError;
    float previousOutput;
    float previousLimitedOutput;
    float saturationLimit;
    int antiWindupFlag;
} PIobject;

/*
 * Initialization functions
 */
void PIObject_Constructor(PIobject *PIcontroller, float KP, float KI,
                          float saturationLimit, int antiWindupFlag);
void initPIControllers(void);

/*
 * PI controllers
 */
float PiCalculation(PIobject *PIcontroller, float reference, float measurementValue);
float PiCalculationIQ(float reference, float measuredValue);
float PiCalculationID(float reference, float measuredValue);
float PiCalcualtionSpeed(float reference, float measuredValue);

/*
 * Function to check saturation of output
 */
int isOutputSaturatedPositive(PIobject *PIcontroller, float PIoutput);
int isOutputSaturatedNegative(PIobject *PIcontroller, float PIoutput);


#endif /* APP_INCLUDE_PICONTROLLER_H_ */
