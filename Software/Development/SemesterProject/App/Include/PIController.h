/*
 * PIController.h
 *
 *  Created on: 2. apr. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_PICONTROLLER_H_
#define APP_INCLUDE_PICONTROLLER_H_


typedef struct PIobjectTag
{
    int KP;
    int KI;
    float integralPart;
    float referencePoint;
    float previousOutput;
    float previousLimitedOutput;
    float saturationLimit;
} PIobject;

/*
 * Initialization functions
 */
void PIObject_Constructor(PIobject *PI, int KP, int KI, float saturationLimit);
void initPIControllers(void);

/*
 * PI controllers
 */
float PiCurrentCalculation(PIobject *PI, float measurementValue);
float PiTorqueCalculation(PIobject *PI, float measurementValue);

/*
 * Function to check saturation of output
 */
int isOutputSaturatedPositive(PIobject *PI);
int isOutputSaturatedNegative(PIobject *PI);

/*
 * Functions to change reference point
 */
void setIqReferencePoint(float referencePoint);
void setIdReferencePoint(float referencePoint);
void setTorqueReferencePoint(float referencePoint);

#endif /* APP_INCLUDE_PICONTROLLER_H_ */
