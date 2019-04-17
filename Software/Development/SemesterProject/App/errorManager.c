/*
 * errorManager.c
 *
 *  Created on: 29. mar. 2019
 *      Author: Nicolai Fransen
 *
 *      The task of the error manager is to detect if an error has happened
 *      somewhere in the system, and perform the necessary safety reactions.
 *      The actual error detection only divides the signals into three groups:
 *      Currents, batteries and the rest. Then the interface functions will
 *      have to be called to discover the exact source of the error.
 *
 *      The errorManager also includes a watchdog that will reset the DSP if
 *      the watchdog counter is not reset within a certain time period
 */

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

errorStatus systemErrorStatus = NO_ERROR;

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
//    else
//        resetSafetyReactions();
}

void performErrorMonitoring(void)
{
    if (isErrorMonitorSwitchEnabled())
        monitorErrorSources();
    else
        resetSafetyReactions();
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
    systemErrorStatus = ERROR_HAS_HAPPENED;
}

/*
 * This function will reset the safety reactions performed in performSafetyReactions().
 */
void resetSafetyReactions(void)
{
    enableDrivers();
    turnOffErrorLED();
    systemErrorStatus = NO_ERROR;
}

/*
 * Functions to disable and enable drivers when an error happens
 */
void disableDrivers(void)
{
    setEnablePWM(OFF);
}

void enableDrivers(void)
{
    setEnablePWM(ON);
}

void turnOnErrorLED(void)
{
    setErrorLED(ON);
}

void turnOffErrorLED(void)
{
    setErrorLED(OFF);
}

/*
 * Interface functions to get the error status of every single bit
 */
errorStatus getCurrentAErrorStatus(void)
{
    return getErrorStatusInBit(0);
}

errorStatus getCurrentBErrorStatus(void)
{
    return getErrorStatusInBit(1);
}

errorStatus getCurrentCErrorStatus(void)
{
    return getErrorStatusInBit(2);
}

errorStatus getControlSupplyBatteryErrorStatus(void)
{
    return getErrorStatusInBit(3);
}

errorStatus getDCLinkBatteryErrorStatus(void)
{
    return getErrorStatusInBit(4);
}

errorStatus getThermometer1ErrorStatus(void)
{
    return getErrorStatusInBit(5);
}

errorStatus getThermometer2ErrorStatus(void)
{
    return getErrorStatusInBit(6);
}

errorStatus getTorqueReferenceSliderErrorStatus(void)
{
    return getErrorStatusInBit(7);
}

errorStatus getSpeedReferenceSliderErrorStatus(void)
{
    return getErrorStatusInBit(8);
}

errorStatus getRotaryPot1ErrorStatus(void)
{
    return getErrorStatusInBit(9);
}

errorStatus getRotaryPot2ErrorStatus(void)
{
    return getErrorStatusInBit(10);
}

errorStatus getRotaryPot3ErrorStatus(void)
{
    return getErrorStatusInBit(11);
}

errorStatus getTorqueReferencePedalErrorStatus(void)
{
    return getErrorStatusInBit(12);
}

errorStatus getBrakeReferencePedalErrorStatus(void)
{
    return getErrorStatusInBit(13);
}

/*
 * This function takes the position of the wanted error status and returns
 * if an error has happened.
 */
errorStatus getErrorStatusInBit(Uint16 position)
{
    Uint16 analogErrorStatus = getAnalogErrorStatus();

    if ((analogErrorStatus & (1<<position)) >> position)
        return ERROR_HAS_HAPPENED;
    else
        return NO_ERROR;
}

/*
 * This function will return the overall error status of the system.
 */
errorStatus getSystemErrorStatus(void)
{
    return systemErrorStatus;
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


