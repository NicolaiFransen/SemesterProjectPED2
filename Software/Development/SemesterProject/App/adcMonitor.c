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

errorStatus areAdcMeasurementsWithinThresholds(void)
{
    Uint16 analogErrorStatus = getAnalogErrorStatus();
    Uint16 errorStatusPosition;

    for (errorStatusPosition = 5; errorStatusPosition < 14; errorStatusPosition++)
    {
        int errorHasHappened = !((analogErrorStatus & (1 << errorStatusPosition)) >> errorStatusPosition);
        if (errorHasHappened)
            return ERROR;
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
            return ERROR;
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
            return ERROR;
    }
    return NO_ERROR;
}
