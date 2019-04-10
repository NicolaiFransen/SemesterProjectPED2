/*
 * PIController.c
 *
 *  Created on: 2. apr. 2019
 *      Author: Nicolai Fransen
 *
 *  This file includes the PI controllers for the control system.
 *  Two different PI functions have been created because the outer loop
 *  must include anti-windup, such that the integrator will not get stuck.
 *
 *  An if-statement is included to check if the output should be limited.
 */

//
// Includes
//
#include "PIController.h"
#include "DSP28x_Project.h"

//
// Quasi-global variables definition
//
static struct
{
    PIobject IqController;
    PIobject IdController;
    PIobject TorqueController;
} PIControllerList;


void PIObject_Constructor(PIobject *PIcontroller, int KP, int KI, float saturationThreshold)
{
    PIcontroller->KP = KP;
    PIcontroller->KI = KI;
    PIcontroller->saturationLimit = saturationThreshold;

    PIcontroller->integralPart = 0;
    PIcontroller->previousOutput = 0;
    PIcontroller->previousLimitedOutput = 0;
}

void initPIControllers(void)
{
    PIObject_Constructor(&PIControllerList.IdController, 10, 10, 10);
    PIObject_Constructor(&PIControllerList.IdController, 10, 10, 10);
    PIObject_Constructor(&PIControllerList.TorqueController, 10, 10, 10);
}

/*
 * PI controller for the inner loops.
 */
float PiCurrentCalculation(PIobject *PIcontroller, float measureredValue)
{
    int KP = PIcontroller->KP;
    int KI = PIcontroller->KI;

    float error, PiOutput;

    // Calculating the difference between the reference and the measured
    error = PIcontroller->referencePoint - measureredValue;

    // Calculating the integral part from the error
    PIcontroller->integralPart = PIcontroller->integralPart + error;

    // Calculating the controller output
    PiOutput = KP * error + KI * PIcontroller->integralPart;

    // If the wanted output is outside saturation limits, then limit the output
    if (isOutputSaturated(PIcontroller))
        PiOutput = PIcontroller->saturationLimit;

    else if (isOutputSaturatedNegative(PIcontroller))
        PiOutput = -(PIcontroller->saturationLimit);

    return PiOutput;
}

/*
 * PI controller for outer loop.
 * This controller includes an anti-windup feedback for the integrator
 */
float PiTorqueCalculation(PIobject *PIcontroller, float measureredValue)
{
    int KP = PIcontroller->KP;
    int KI = PIcontroller->KI;

    float error, PiOutput, outputFeedback;

    // Calculating the difference between the reference and the measured
    error = PIcontroller->referencePoint - measureredValue;

    // Calculating the integral part from the error
    PIcontroller->integralPart = PIcontroller->integralPart + error;

    // Calculating the difference between the wanted output and the actual output
    // To be used in the anti-windup of the integrator
    outputFeedback = PIcontroller->previousOutput - PIcontroller->previousLimitedOutput;

    // Calculating the controller output
    PiOutput = KP * error +
              (KI * PIcontroller->integralPart - outputFeedback * 1/KP);

    PIcontroller->previousOutput = PiOutput;

    // If the wanted output is outside saturation limits, then limit the output
    if (isOutputSaturatedPositive(PIcontroller))
        PiOutput = PIcontroller->saturationLimit;

    else if (isOutputSaturatedNegative(PIcontroller))
        PiOutput = -(PIcontroller->saturationLimit);

    PIcontroller->previousLimitedOutput = PiOutput;

    return PiOutput;
}

/*
 * Functions to check for saturation
 */
int isOutputSaturatedPositive(PIobject *PIcontroller)
{
    return PIcontroller->previousOutput > PIcontroller->saturationLimit;
}

int isOutputSaturatedNegative(PIobject * PIcontroller)
{
    return PIcontroller->previousOutput < -(PIcontroller->saturationLimit);
}

/*
 * Functions to set reference points for each PI controller
 */
void setIqReferencePoint(float referencePoint)
{
    PIControllerList.IqController.referencePoint = referencePoint;
}

void setIdReferencePoint(float referencePoint)
{
    PIControllerList.IdController.referencePoint = referencePoint;
}

void setTorqueReferencePoint(float referencePoint)
{
    PIControllerList.TorqueController.referencePoint = referencePoint;
}

