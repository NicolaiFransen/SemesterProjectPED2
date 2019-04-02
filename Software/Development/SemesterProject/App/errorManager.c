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
 * This function updates the the error status of the different measurements,
 * and determines if safety reactions should be performed
 */
void monitorErrorSources(void)
{
    errorStatusList.currentErrorStatus = areCurrentMeasurementsWithinThresholds();
    errorStatusList.batteryErrorStatus = areBatteryMeasurementsWithinThresholds();
    errorStatusList.adcErrorStatus = areAdcMeasurementsWithinThresholds();

    if (errorStatusList.currentErrorStatus == ERROR_HAS_HAPPENED ||
        errorStatusList.batteryErrorStatus == ERROR_HAS_HAPPENED ||
        errorStatusList.adcErrorStatus == ERROR_HAS_HAPPENED)
            performSafetyReactions();
    else
    {
        turnOffErrorLED();
        //setEnablePWM(ON);
    }

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
    GpioDataRegs.GPASET.bit.GPIO18 = 1;
    //setErrorLED(ON); Uncomment this when merged with digital output manager (LED17)
}

void turnOffErrorLED(void)
{
    GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;
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

/*
 * Function to initialize the watchdog.
 * By setting bit2 in SCSR the watchdog is set to reset the MCU
 */
void initWatchdog(void)
{
    //
    // Connect the watchdog to the reset interrupt of the PIE
    // Write to the whole SCSR register to avoid clearing WDOVERRIDE bit
    //
    EALLOW;
    SysCtrlRegs.SCSR = BIT2;
    EDIS;

    //
    // Reset the watchdog counter
    //
    ServiceDog();

    //
    // Enable the watchdog
    //
    EALLOW;
    SysCtrlRegs.WDCR = 0x0028;
    EDIS;
}


