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
 * An error in this bit string is a 1.
 * The if statements checks for a 1 in any of the places used in the part of the string that
 * are of interest.
 */
errorStatus areAdcMeasurementsWithinThresholds(void)
{
    Uint16 analogErrorStatus = getAnalogErrorStatus();

    if (analogErrorStatus & 0b0011111111100000)
        return ERROR_HAS_HAPPENED;

    return NO_ERROR;
}


errorStatus areBatteryMeasurementsWithinThresholds(void)
{
    Uint16 analogErrorStatus = getAnalogErrorStatus();

    if (analogErrorStatus & 0b0000000000011000)
        return ERROR_HAS_HAPPENED;

    return NO_ERROR;
}

errorStatus areCurrentMeasurementsWithinThresholds(void)
{
    Uint16 analogErrorStatus = getAnalogErrorStatus();

    if (analogErrorStatus & 0b0000000000000111)
        return ERROR_HAS_HAPPENED;

    return NO_ERROR;
}
