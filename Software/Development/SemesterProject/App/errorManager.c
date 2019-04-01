/*
 * errorManager.c
 *
 *  Created on: 29. mar. 2019
 *      Author: Nicolai Fransen
 */

#include "adcMonitor.h"
#include "errorManager.h"
#include "dutyCycle.h"

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

    if (errorStatusList.currentErrorStatus == ERROR ||
        errorStatusList.batteryErrorStatus == ERROR ||
        errorStatusList.adcErrorStatus == ERROR)
            performSafetyReactions();

}

/*
 * This function will call the safety features when an error is detected.
 * This includes:
 * - Set all duty-cycles to 0.
 * - Disable enable signal to drivers.
 * - Turn on LED indicating an error has happened.
 */
void performSafetyReactions(void)
{
    setAllDuties(0);
    disableDrivers();
    turnOnErrorLED();
}

/*
 * Function to disable drivers when an error happens
 */
void disableDrivers(void)
{
    // setEnablePWM(OFF); Uncomment this when merged with digital output manager
}

void turnOnErrorLED(void)
{
    //setErrorLED(ON); Uncomment this when merged with digital output manager (LED17)
}

void turnOffErrorLED(void)
{
    //setErrorLED(OFF); Uncomment this when merged with digital output manager (LED17)
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


