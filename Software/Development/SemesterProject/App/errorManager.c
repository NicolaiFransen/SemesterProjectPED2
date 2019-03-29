/*
 * errorManager.c
 *
 *  Created on: 29. mar. 2019
 *      Author: Nicolai Fransen
 */

#include "adcMonitor.h"
#include "errorManager.h"

/*
 * Struct that contains the error status of the different measurements
 */
static struct
{
    errorStatus currentErrorStatus;
    errorStatus batteryErrorStatus;
    errorStatus adcErrorStatus;
} errorStatusList;

/*
 * This function updates the the error status of the different measurements
 */
void monitorErrorSources(void)
{
    errorStatusList.currentErrorStatus = areCurrentMeasurementsWithinThresholds();
    errorStatusList.batteryErrorStatus = areBatteryMeasurementsWithinThresholds();
    errorStatusList.adcErrorStatus = areAdcMeasurementsWithinThresholds();
}

/*
 * This function will call the safety features when an error is detected.
 * This includes:
 * - Disable enable signal to drivers.
 * - Turn on LED indicating an error has happened.
 */
void performSafetyReactions(void)
{
    disableDrivers();
    turnOnErrorLED();
}

void turnOnErrorLED(void)
{
    //setLED17(ON); Uncomment this when merged with digital output manager
}

void turnOffErrorLED(void)
{
    //setLED17(OFF); Uncomment this when merged with digital output manager
}

/*
 * Interface functions to get the three error status'
 */
errorStatus getCurrentErrorStatus(void)
{
    return errorStatusList.currentErrorStatus;
}

errorStatus getBatteryErrorStatus(void)
{
    return errorStatusList.batteryErrorStatus;
}

errorStatus getAdcErrorStatus(void)
{
    return errorStatusList.adcErrorStatus;
}

/*
 * Function to disable drivers when an error happens
 *
 * Determine if this should happen here or in controlTask.
 */
void disableDrivers(void)
{
    // setEnablePWM(OFF); Uncomment this when merged with digital output manager
}
