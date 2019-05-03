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

/*
 * These three functions check different parts of the analogErrorStatus for errors
 * An error in this bit string is a 1.
 * The if statements checks for a 1 in any of the places used in the part of the string that
 * are of interest.
 */
errorStatus areAdcMeasurementsWithinThresholds(Uint16 errorStatus)
{
    if (errorStatus & 0b0011111111100000)
        return ERROR_HAS_HAPPENED;

    return NO_ERROR;
}


errorStatus areBatteryMeasurementsWithinThresholds(Uint16 errorStatus)
{
    if (errorStatus & 0b0000000000011000)
        return ERROR_HAS_HAPPENED;

    return NO_ERROR;
}

errorStatus areCurrentMeasurementsWithinThresholds(Uint16 errorStatus)
{
    if (errorStatus & 0b0000000000000111)
        return ERROR_HAS_HAPPENED;

    return NO_ERROR;
}


/*
 * This function takes the position of the wanted error status and returns
 * if an error has happened.
 * If the position is less than 3, meaning one of the currents, high priority errors
 * are read.
 */
errorStatus getErrorStatusInBit(Uint16 position)
{
    Uint16 errorStatus;

    if(position < 3)
        errorStatus = getHighPriorityErrorStatus();
    else
        errorStatus = getLowPriorityErrorStatus();

    if ((errorStatus & (1<<position)) >> position)
        return ERROR_HAS_HAPPENED;
    else
        return NO_ERROR;
}
