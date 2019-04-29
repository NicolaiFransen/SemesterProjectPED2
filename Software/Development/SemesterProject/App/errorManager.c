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

static struct
{
    errorStatus currentAErrorStatus;
    errorStatus currentBErrorStatus;
    errorStatus currentCErrorStatus;
    errorStatus voltage24ErrorStatus;
    errorStatus voltage36ErrorStatus;
    errorStatus thermometer1ErrorStatus;
    errorStatus thermometer2ErrorStatus;
    errorStatus torqueReferenceSliderErrorStatus;
    errorStatus speedReferenceSliderErrorStatus;
    errorStatus rotaryPot1ErrorStatus;
    errorStatus rotaryPot2ErrorStatus;
    errorStatus rotaryPot3ErrorStatus;
    errorStatus torqueReferencePedalErrorStatus;
    errorStatus brakeReferencePedalErrorStatus;
} latchingErrorStatusList;

static errorStatus systemErrorStatus = NO_ERROR;

/*
 * This function updates the the error status of the different measurements,
 * and determines if safety reactions should be performed
 */
void monitorErrorSources(void)
{
    errorStatusList.currentErrorStatus = areCurrentMeasurementsWithinThresholds();
    errorStatusList.batteryErrorStatus = areBatteryMeasurementsWithinThresholds();
    errorStatusList.adcErrorStatus = areAdcMeasurementsWithinThresholds();

    if (errorStatusList.currentErrorStatus == ERROR_HAS_HAPPENED)
    {
        performSafetyReactions();
        updateCurrentErrorStatus();
    }

    if (errorStatusList.batteryErrorStatus == ERROR_HAS_HAPPENED)
    {
        performSafetyReactions();
        updateVoltageErrorStatus();
    }

    if (errorStatusList.adcErrorStatus == ERROR_HAS_HAPPENED)
    {
        performSafetyReactions();
        updateAdcErrorStatus();
    }
}

void performErrorMonitoring(void)
{
    if (isErrorMonitorSwitchEnabled() && filtersHaveSettled())
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
    turnOffErrorLED();
    resetErrorStatus();
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
 * This function returns a '1' when the system clock counter has reached 25,
 * equal to 25*200ms = 5s.
 * This is used to let the filters settle during system startup, so startup
 * errors will not be generated.
 */
int filtersHaveSettled(void)
{
    if(getSystemClock() > 25)
        return 1;
    else
        return 0;
}

/*
 * Functions used to set errorStatus for every bit.
 * This will latch the errors, so resetErrorStatus()
 * will have to be called to reset the errors.
 */
void setCurrentAErrorStatus(void)
{
    if (getErrorStatusInBit(0) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.currentAErrorStatus = ERROR_HAS_HAPPENED;
}

void setCurrentBErrorStatus(void)
{
    if (getErrorStatusInBit(1) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.currentBErrorStatus = ERROR_HAS_HAPPENED;
}

void setCurrentCErrorStatus(void)
{
    if (getErrorStatusInBit(2) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.currentCErrorStatus = ERROR_HAS_HAPPENED;
}

void setControlSupplyBatteryErrorStatus(void)
{
    if (getErrorStatusInBit(3) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.voltage24ErrorStatus = ERROR_HAS_HAPPENED;
}

void setDCLinkBatteryErrorStatus(void)
{
    if (getErrorStatusInBit(4) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.voltage36ErrorStatus = ERROR_HAS_HAPPENED;
}

void setThermometer1ErrorStatus(void)
{
    if (getErrorStatusInBit(5) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.thermometer1ErrorStatus = ERROR_HAS_HAPPENED;
}
void setThermometer2ErrorStatus(void)
{
    if (getErrorStatusInBit(6) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.thermometer2ErrorStatus = ERROR_HAS_HAPPENED;
}

void setTorqueReferenceSliderErrorStatus(void)
{
    if (getErrorStatusInBit(7) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.torqueReferenceSliderErrorStatus = ERROR_HAS_HAPPENED;
}

void setSpeedReferenceSliderErrorStatus(void)
{
    if (getErrorStatusInBit(8) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.speedReferenceSliderErrorStatus = ERROR_HAS_HAPPENED;
}

void setRotaryPot1ErrorStatus(void)
{
    if (getErrorStatusInBit(9) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.rotaryPot1ErrorStatus = ERROR_HAS_HAPPENED;
}

void setRotaryPot2ErrorStatus(void)
{
    if (getErrorStatusInBit(10) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.rotaryPot2ErrorStatus = ERROR_HAS_HAPPENED;
}
void setRotaryPot3ErrorStatus(void)
{
    if (getErrorStatusInBit(11) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.rotaryPot3ErrorStatus = ERROR_HAS_HAPPENED;
}

void setTorqueReferencePedalErrorStatus(void)
{
    if (getErrorStatusInBit(12) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.torqueReferencePedalErrorStatus = ERROR_HAS_HAPPENED;
}
void setBrakeReferencePedalErrorStatus(void)
{
    if (getErrorStatusInBit(13) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.brakeReferencePedalErrorStatus = ERROR_HAS_HAPPENED;
}


/*
 * Interface functions to get the error status of every single bit
 */
errorStatus getCurrentAErrorStatus(void)
{
    return latchingErrorStatusList.currentAErrorStatus;
}

errorStatus getCurrentBErrorStatus(void)
{
    return latchingErrorStatusList.currentBErrorStatus;
}

errorStatus getCurrentCErrorStatus(void)
{
    return latchingErrorStatusList.currentCErrorStatus;
}

errorStatus getControlSupplyBatteryErrorStatus(void)
{
    return latchingErrorStatusList.voltage24ErrorStatus;
}

errorStatus getDCLinkBatteryErrorStatus(void)
{
    return latchingErrorStatusList.voltage36ErrorStatus;
}

errorStatus getThermometer1ErrorStatus(void)
{
    return latchingErrorStatusList.thermometer1ErrorStatus;
}

errorStatus getThermometer2ErrorStatus(void)
{
    return latchingErrorStatusList.thermometer2ErrorStatus;
}

errorStatus getTorqueReferenceSliderErrorStatus(void)
{
    return latchingErrorStatusList.torqueReferenceSliderErrorStatus;
}

errorStatus getSpeedReferenceSliderErrorStatus(void)
{
    return latchingErrorStatusList.speedReferenceSliderErrorStatus;
}

errorStatus getRotaryPot1ErrorStatus(void)
{
    return latchingErrorStatusList.rotaryPot1ErrorStatus;
}

errorStatus getRotaryPot2ErrorStatus(void)
{
    return latchingErrorStatusList.rotaryPot2ErrorStatus;
}

errorStatus getRotaryPot3ErrorStatus(void)
{
    return latchingErrorStatusList.rotaryPot3ErrorStatus;
}

errorStatus getTorqueReferencePedalErrorStatus(void)
{
    return latchingErrorStatusList.torqueReferencePedalErrorStatus;
}

errorStatus getBrakeReferencePedalErrorStatus(void)
{
    return latchingErrorStatusList.brakeReferencePedalErrorStatus;
}



/*
 * This function will return the overall error status of the system.
 */
errorStatus getSystemErrorStatus(void)
{
    return systemErrorStatus;
}

/*
 * Functions to update the error status of the signals in the three groups
 */
void updateCurrentErrorStatus(void)
{
    setCurrentAErrorStatus();
    setCurrentBErrorStatus();
    setCurrentCErrorStatus();
}

void updateVoltageErrorStatus(void)
{
    setDCLinkBatteryErrorStatus();
    setControlSupplyBatteryErrorStatus();
}

void updateAdcErrorStatus(void)
{
    setTorqueReferenceSliderErrorStatus();
    setSpeedReferenceSliderErrorStatus();
    setTorqueReferencePedalErrorStatus();
    setBrakeReferencePedalErrorStatus();
    setThermometer1ErrorStatus();
    setThermometer2ErrorStatus();
    setRotaryPot1ErrorStatus();
    setRotaryPot2ErrorStatus();
    setRotaryPot3ErrorStatus();
}

/*
 * Function to reset all errors.
 * Should only be called when leaving ErrorState.
 */
void resetErrorStatus(void)
{
    errorStatus *structPointer;
    errorStatus *initialMemoryPosition = &latchingErrorStatusList.currentAErrorStatus;
    errorStatus *finalMemoryPosition = initialMemoryPosition + sizeof(latchingErrorStatusList)/sizeof(errorStatus);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
        *structPointer = NO_ERROR;

    systemErrorStatus = NO_ERROR;
}


/*
 * Function to force the system in error state
 */
void forceSystemError(void)
{
    performSafetyReactions();
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


