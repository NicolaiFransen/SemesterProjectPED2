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
#include "DSP28x_Project.h"


typedef struct PIobjectTag
{
    float KP;
    float KI;
    float integralPart;
    float referencePoint;
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
float PiCalculation(PIobject *PIcontroller, float measurementValue);
float PiCalculationIQ(float measuredValue);
float PiCalculationID(float measuredValue);
float PiCalcualtionSpeed(float measuredValue);

/*
 * Function to check saturation of output
 */
int isOutputSaturatedPositive(PIobject *PIcontroller);
int isOutputSaturatedNegative(PIobject *PIcontroller);

/*
 * Functions to change reference point
 */
void setIqReferencePoint(float referencePoint);
void setIdReferencePoint(float referencePoint);
void setSpeedReferencePoint(float referencePoint);

#endif /* APP_INCLUDE_PICONTROLLER_H_ */
