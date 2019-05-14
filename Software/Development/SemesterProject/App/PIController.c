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


void PIObject_Constructor(PIobject *PIcontroller, float KP, float KI, int antiWindupFlag, int saturationBlockFlag)
{
    PIcontroller->KP = KP;
    PIcontroller->KI = KI;
    PIcontroller->KPInverse = 1/KP;

    PIcontroller->integrationOfError = 0;
    PIcontroller->previousOutput = 0;
    PIcontroller->previousLimitedOutput = 0;

    PIcontroller->antiWindupFlag = antiWindupFlag;
    PIcontroller->includeSaturationBlock = saturationBlockFlag;
}

/*
 * PI controller calculations.
 * Depending on the value of the windup flag, this part will be used or not.
 */
float PiCalculation(PIobject *PIcontroller, float reference, float measuredValue, int PIIsIqController)
{
    float KP = PIcontroller->KP;
    float KI = PIcontroller->KI;
    float KPInverse = PIcontroller->KPInverse;

    float error, PIoutput, outputFeedback;

    // Calculating the difference between the reference and the measured
    error = reference - measuredValue;
    if (PIIsIqController)
        {
        if (getUartCounter() == 0)  UARTIntPrint("er ", (int)(error));
        }


    // Calculating the integral part from the error
    PIcontroller->integrationOfError = PIcontroller->integrationOfError + error;

    if (PIcontroller->antiWindupFlag)
    {
        // Calculating the difference between the wanted output and the actual output
        // To be used in the anti-windup of the integrator
        outputFeedback = fabs(PIcontroller->previousOutput) - fabs(PIcontroller->previousLimitedOutput);

        // Calculating the controller output
        PIoutput = KP * error +
                  (KI * PIcontroller->integrationOfError - outputFeedback * KPInverse);
    }
    else
        // Calculating the controller output
        PIoutput = KP * error + KI * PIcontroller->integrationOfError;

    PIcontroller->previousOutput = PIoutput;

    if (PIcontroller->includeSaturationBlock)
    {
        if (isOutputSaturatedPositive(PIoutput))
            PIoutput = VOLTAGE_LIMIT;
        else if (isOutputSaturatedNegative(PIoutput))
            PIoutput = -VOLTAGE_LIMIT;
    }

    PIcontroller->previousLimitedOutput = PIoutput;
    return PIoutput;
}


/*
 * Functions to check for saturation
 */
int isOutputSaturatedPositive(float PIoutput)
{
    return PIoutput > CURRENT_LIMIT;
}

int isOutputSaturatedNegative(float PIoutput)
{
    return PIoutput < -(CURRENT_LIMIT);
}



