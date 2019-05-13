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
    errorStatus forceSystemErrorStatus;
} latchingErrorStatusList;

static errorStatus systemErrorStatus = NO_ERROR;

/*
 * This function updates the the error status of the different measurements,
 * and determines if safety reactions should be performed.
 *
 * The error monitoring is divided into high and low priority signals, to minimize
 * the execution time.
 */
void monitorHighPriorityErrorSources(void)
{
    Uint16 errorStatus = getHighPriorityErrorStatus();

    errorStatusList.currentErrorStatus = areCurrentMeasurementsWithinThresholds(errorStatus);

    if (errorStatusList.currentErrorStatus == ERROR_HAS_HAPPENED)
    {
        performSafetyReactions();
        updateCurrentErrorStatus(errorStatus);
    }
}

void performHighPriorityErrorMonitoring(void)
{
    if (isErrorMonitorSwitchEnabled() && filtersHaveSettled())
        monitorHighPriorityErrorSources();
}

void monitorLowPriorityErrorSources(void)
{
    Uint16 errorStatus = getLowPriorityErrorStatus();

    errorStatusList.batteryErrorStatus = areBatteryMeasurementsWithinThresholds(errorStatus);
    errorStatusList.adcErrorStatus = areAdcMeasurementsWithinThresholds(errorStatus);

    if (errorStatusList.batteryErrorStatus == ERROR_HAS_HAPPENED)
    {
        performSafetyReactions();
        updateVoltageErrorStatus(errorStatus);
    }

    if (errorStatusList.adcErrorStatus == ERROR_HAS_HAPPENED)
    {
        performSafetyReactions();
        updateAdcErrorStatus(errorStatus);
    }

    if (readRotorRPM() > MAXIMUM_ROTOR_SPEED)
    {
        performSafetyReactions();
    }
}

void performLowPriorityErrorMonitoring(void)
{
    if (isErrorMonitorSwitchEnabled() && filtersHaveSettled())
        monitorLowPriorityErrorSources();
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
void setCurrentAErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(0, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.currentAErrorStatus = ERROR_HAS_HAPPENED;
}

void setCurrentBErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(1, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.currentBErrorStatus = ERROR_HAS_HAPPENED;
}

void setCurrentCErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(2, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.currentCErrorStatus = ERROR_HAS_HAPPENED;
}

void setControlSupplyBatteryErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(3, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.voltage24ErrorStatus = ERROR_HAS_HAPPENED;
}

void setDCLinkBatteryErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(4, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.voltage36ErrorStatus = ERROR_HAS_HAPPENED;
}

void setThermometer1ErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(5, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.thermometer1ErrorStatus = ERROR_HAS_HAPPENED;
}
void setThermometer2ErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(6, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.thermometer2ErrorStatus = ERROR_HAS_HAPPENED;
}

void setTorqueReferenceSliderErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(7, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.torqueReferenceSliderErrorStatus = ERROR_HAS_HAPPENED;
}

void setSpeedReferenceSliderErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(8, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.speedReferenceSliderErrorStatus = ERROR_HAS_HAPPENED;
}

void setRotaryPot1ErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(9, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.rotaryPot1ErrorStatus = ERROR_HAS_HAPPENED;
}

void setRotaryPot2ErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(10, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.rotaryPot2ErrorStatus = ERROR_HAS_HAPPENED;
}
void setRotaryPot3ErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(11, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.rotaryPot3ErrorStatus = ERROR_HAS_HAPPENED;
}

void setTorqueReferencePedalErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(12, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.torqueReferencePedalErrorStatus = ERROR_HAS_HAPPENED;
}
void setBrakeReferencePedalErrorStatus(Uint16 errorStatus)
{
    if (getErrorStatusInBit(13, errorStatus) == ERROR_HAS_HAPPENED)
        latchingErrorStatusList.brakeReferencePedalErrorStatus = ERROR_HAS_HAPPENED;
}

void setForceSystemErrorStatus(void)
{
    latchingErrorStatusList.forceSystemErrorStatus = ERROR_HAS_HAPPENED;
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
errorStatus getErrorManagerStatus(void)
{
    return systemErrorStatus;
}

/*
 * Functions to update the error status of the signals in the three groups
 */
void updateCurrentErrorStatus(Uint16 errorStatus)
{
    setCurrentAErrorStatus(errorStatus);
    setCurrentBErrorStatus(errorStatus);
    setCurrentCErrorStatus(errorStatus);
}

void updateVoltageErrorStatus(Uint16 errorStatus)
{
    setDCLinkBatteryErrorStatus(errorStatus);
    setControlSupplyBatteryErrorStatus(errorStatus);
}

void updateAdcErrorStatus(Uint16 errorStatus)
{
    setTorqueReferenceSliderErrorStatus(errorStatus);
    setSpeedReferenceSliderErrorStatus(errorStatus);
    setTorqueReferencePedalErrorStatus(errorStatus);
    setBrakeReferencePedalErrorStatus(errorStatus);
    setThermometer1ErrorStatus(errorStatus);
    setThermometer2ErrorStatus(errorStatus);
    setRotaryPot1ErrorStatus(errorStatus);
    setRotaryPot2ErrorStatus(errorStatus);
    setRotaryPot3ErrorStatus(errorStatus);
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
    setForceSystemErrorStatus();
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


