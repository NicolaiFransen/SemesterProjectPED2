/*
 * errorManager.h
 *
 *  Created on: 29. mar. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_ERRORMANAGER_H_
#define APP_INCLUDE_ERRORMANAGER_H_

typedef enum
{
    NO_ERROR,
    ERROR_HAS_HAPPENED,
    IDLE
} errorStatus;

#include "adcMonitor.h"
#include "dutyCycle.h"
#include "digitalOutput.h"
#include "digitalOutputManager.h"
#include "digitalInputManager.h"
#include "Constants.h"
#include "positionCalculator.h"
#include "../scheduler.h"

//
// Function prototyping
//
void monitorHighPriorityErrorSources(void);
void performHighPriorityErrorMonitoring(void);
void monitorLowPriorityErrorSources(void);
void performLowPriorityErrorMonitoring(void);

void performSafetyReactions(void);
void resetSafetyReactions(void);
void disableDrivers(void);
void enableDrivers(void);
void turnOnErrorLED(void);
void turnOffErrorLED(void);
int filtersHaveSettled(void);

void setCurrentAErrorStatus(Uint16 errorStatus);
void setCurrentBErrorStatus(Uint16 errorStatus);
void setCurrentCErrorStatus(Uint16 errorStatus);
void setDCLinkBatteryErrorStatus(Uint16 errorStatus);
void setControlSupplyBatteryErrorStatus(Uint16 errorStatus);
void setTorqueReferenceSliderErrorStatus(Uint16 errorStatus);
void setSpeedReferenceSliderErrorStatus(Uint16 errorStatus);
void setTorqueReferencePedalErrorStatus(Uint16 errorStatus);
void setBrakeReferencePedalErrorStatus(Uint16 errorStatus);
void setThermometer1ErrorStatus(Uint16 errorStatus);
void setThermometer2ErrorStatus(Uint16 errorStatus);
void setRotaryPot1ErrorStatus(Uint16 errorStatus);
void setRotaryPot2ErrorStatus(Uint16 errorStatus);
void setRotaryPot3ErrorStatus(Uint16 errorStatus);
void setForceSystemErrorStatus(void);

errorStatus getCurrentAErrorStatus(void);
errorStatus getCurrentBErrorStatus(void);
errorStatus getCurrentCErrorStatus(void);
errorStatus getDCLinkBatteryErrorStatus(void);
errorStatus getControlSupplyBatteryErrorStatus(void);
errorStatus getTorqueReferenceSliderErrorStatus(void);
errorStatus getSpeedReferenceSliderErrorStatus(void);
errorStatus getTorqueReferencePedalErrorStatus(void);
errorStatus getBrakeReferencePedalErrorStatus(void);
errorStatus getThermometer1ErrorStatus(void);
errorStatus getThermometer2ErrorStatus(void);
errorStatus getRotaryPot1ErrorStatus(void);
errorStatus getRotaryPot2ErrorStatus(void);
errorStatus getRotaryPot3ErrorStatus(void);

errorStatus getErrorManagerStatus(void);

void updateCurrentErrorStatus(Uint16 errorStatus);
void updateVoltageErrorStatus(Uint16 errorStatus);
void updateAdcErrorStatus(Uint16 errorStatus);

void forceSystemError(void);
void resetErrorStatus(void);

void initWatchdog(void);


#endif /* APP_INCLUDE_ERRORMANAGER_H_ */
