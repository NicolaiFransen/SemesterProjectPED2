/*
 * PIController.c
 *
 *  Created on: 2. apr. 2019
 *      Author: Nicolai Fransen
 *
 *  This file includes the PI controllers for the control system.
 *  An anti windup flag is included in the object such that it's possible
 *  to select if the specific controller should include anti windup.
 *
 *  An if-statement is included to check if the output should be limited.
 */

//
// Includes
//
#include "PIController.h"


void PIObject_Constructor(PIobject *PIcontroller, float KP, float KI,
                          float saturationThreshold, int antiWindupFlag)
{
    PIcontroller->KP = KP;
    PIcontroller->KI = KI;
    PIcontroller->KPInverse = 1/KP;
    PIcontroller->saturationLimit = saturationThreshold;

    PIcontroller->integrationOfError = 0;
    PIcontroller->previousOutput = 0;
    PIcontroller->previousLimitedOutput = 0;

    PIcontroller->antiWindupFlag = antiWindupFlag;
}

/*
 * PI controller calculations.
 * Depending on the value of the windup flag, this part will be used or not.
 */
float PiCalculation(PIobject *PIcontroller, float reference, float measuredValue)
{
    float KP = PIcontroller->KP;
    float KI = PIcontroller->KI;
    float KPInverse = PIcontroller->KPInverse;

    float error, PIoutput, outputFeedback;

    // Calculating the difference between the reference and the measured
    error = reference - measuredValue;

    // Calculating the integral part from the error
    PIcontroller->integrationOfError = PIcontroller->integrationOfError + error;

    if (PIcontroller->antiWindupFlag)
    {
        // Calculating the difference between the wanted output and the actual output
        // To be used in the anti-windup of the integrator
        outputFeedback = PIcontroller->previousOutput - PIcontroller->previousLimitedOutput;

        // Calculating the controller output
        PIoutput = KP * error +
                  (KI * PIcontroller->integrationOfError - outputFeedback * KPInverse);
    }
    else
        // Calculating the controller output
        PIoutput = KP * error + KI * PIcontroller->integrationOfError;

    // If the wanted output is outside saturation limits, then limit the output
    if (isOutputSaturatedPositive(PIcontroller, PIoutput))
    {
        PIoutput = PIcontroller->saturationLimit;
    }
    else if (isOutputSaturatedNegative(PIcontroller, PIoutput))
    {
        PIoutput = -(PIcontroller->saturationLimit);
    }

    return PIoutput;
}


/*
 * Functions to check for saturation
 */
int isOutputSaturatedPositive(PIobject *PIcontroller, float PIoutput)
{
    return PIoutput > PIcontroller->saturationLimit;
}

int isOutputSaturatedNegative(PIobject * PIcontroller, float PIoutput)
{
    return PIoutput < -(PIcontroller->saturationLimit);
}



