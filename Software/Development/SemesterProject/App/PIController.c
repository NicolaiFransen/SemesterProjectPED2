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
    PIobject SpeedController;
} PIControllerList;


void PIObject_Constructor(PIobject *PIcontroller, float KP, float KI,
                          float saturationThreshold, int antiWindupFlag)
{
    PIcontroller->KP = KP;
    PIcontroller->KI = KI;
    PIcontroller->saturationLimit = saturationThreshold;

    PIcontroller->integralPart = 0;
    PIcontroller->previousOutput = 0;
    PIcontroller->previousLimitedOutput = 0;

    PIcontroller->antiWindupFlag = antiWindupFlag;
}

void initPIControllers(void)
{
    PIObject_Constructor(&PIControllerList.IdController, KP_ID, KI_ID, CURRENT_LIMIT, 0);
    PIObject_Constructor(&PIControllerList.IqController, KP_IQ, KI_IQ, CURRENT_LIMIT, 0);
    PIObject_Constructor(&PIControllerList.SpeedController, KP_SPEED, KI_SPEED, SPEED_LIMIT, 1);
}

/*
 * PI controller calculations.
 * Depending on the value of the windup falg, this part will be used or not.
 */
float PiCalculation(PIobject *PIcontroller, float measuredValue)
{
    float KP = PIcontroller->KP;
    float KI = PIcontroller->KI;

    float error, PIoutput, outputFeedback;

    // Calculating the difference between the reference and the measured
    error = PIcontroller->referencePoint - measuredValue;

    // Calculating the integral part from the error
    PIcontroller->integralPart = PIcontroller->integralPart + error;

    if (PIcontroller->antiWindupFlag)
    {
        // Calculating the difference between the wanted output and the actual output
        // To be used in the anti-windup of the integrator
        outputFeedback = PIcontroller->previousOutput - PIcontroller->previousLimitedOutput;

        // Calculating the controller output
        PIoutput = KP * error +
                  (KI * PIcontroller->integralPart - outputFeedback / KP);
    }
    else
        // Calculating the controller output
        PIoutput = KP * error + KI * PIcontroller->integralPart;

    // If the wanted output is outside saturation limits, then limit the output
    if (isOutputSaturatedPositive(PIcontroller))
        PIoutput = PIcontroller->saturationLimit;

    else if (isOutputSaturatedNegative(PIcontroller))
        PIoutput = -(PIcontroller->saturationLimit);

    return PIoutput;
}

/*
 * Interface functions to use PI controllers
 */
float PiCalcualtionIQ(float measuredValue)
{
    return PiCalculation(&PIControllerList.IqController, measuredValue);
}

float PiCalculationID(float measuredValue)
{
    return PiCalculation(&PIControllerList.IdController, measuredValue);
}

float PiCalculationSpeed(float measuredValue)
{
    return PiCalculation(&PIControllerList.SpeedController, measuredValue);
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

void setSpeedReferencePoint(float referencePoint)
{
    PIControllerList.SpeedController.referencePoint = referencePoint;
}

