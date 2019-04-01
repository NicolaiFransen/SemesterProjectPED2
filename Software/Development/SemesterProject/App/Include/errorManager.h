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
errorStatus getCurrentErrorStatus(void);
errorStatus getBatteryErrorStatus(void);
errorStatus getAdcErrorStatus(void);


#endif /* APP_INCLUDE_ERRORMANAGER_H_ */
