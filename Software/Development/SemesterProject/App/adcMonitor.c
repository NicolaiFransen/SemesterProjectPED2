/*
 * adcMonitor.c
 *
 *  Created on: 28. mar. 2019
 *      Author: Nicolai Fransen
 */


//
// Included Files
//
#include "adcMonitor.h"
#include "DSP28x_Project.h"

/*
 * These three functions check different parts of the analogErrorStatus for errors
 * An error in this bit string is a 0, So the function checks the string for 1's.
 * If the for-loop finds a 1 errorHasHappened will be 0, and will therefore not
 * enter the if-statement.
 */
errorStatus areAdcMeasurementsWithinThresholds(void)
{
    Uint16 analogErrorStatus = getAnalogErrorStatus();
    Uint16 errorStatusPosition;

    for (errorStatusPosition = 5; errorStatusPosition < 14; errorStatusPosition++)
    {
        int errorHasHappened = !((analogErrorStatus & (1 << errorStatusPosition)) >> errorStatusPosition);
        if (errorHasHappened)
            return ERROR_HAS_HAPPENED;
    }
    return NO_ERROR;
}


errorStatus areBatteryMeasurementsWithinThresholds(void)
{
    Uint16 analogErrorStatus = getAnalogErrorStatus();
    Uint16 errorStatusPosition;

    for (errorStatusPosition = 3; errorStatusPosition < 5; errorStatusPosition++)
    {
        int errorHasHappened = !((analogErrorStatus & (1 << errorStatusPosition)) >> errorStatusPosition);
        if (errorHasHappened)
            return ERROR_HAS_HAPPENED;
    }
    return NO_ERROR;
}

errorStatus areCurrentMeasurementsWithinThresholds(void)
{
    Uint16 analogErrorStatus = getAnalogErrorStatus();
    Uint16 errorStatusPosition;

    for (errorStatusPosition = 0; errorStatusPosition < 3; errorStatusPosition++)
    {
        int errorHasHappened = !((analogErrorStatus & (1 << errorStatusPosition)) >> errorStatusPosition);
        if (errorHasHappened)
            return ERROR_HAS_HAPPENED;
    }
    return NO_ERROR;
}
