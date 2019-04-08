/*
 * errorManager.h
 *
 *  Created on: 29. mar. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_ERRORMANAGER_H_
#define APP_INCLUDE_ERRORMANAGER_H_

#include "adcMonitor.h"

//
// Function prototyping
//
void monitorErrorSources(void);
void performSafetyReactions(void);
void disableDrivers(void);
void turnOnErrorLED(void);
void turnOffErrorLED(void);
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

errorStatus getErrorStatusInBit(Uint16);

void initWatchdog(void);


#endif /* APP_INCLUDE_ERRORMANAGER_H_ */
