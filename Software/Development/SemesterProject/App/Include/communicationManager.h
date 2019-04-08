/*
 * communicationManager.h
 *
 *  Created on: Mar 20, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_COMMUNICATIONMANAGER_H_
#define APP_INCLUDE_COMMUNICATIONMANAGER_H_

#include "analogAcquisitionManager.h"
#include "systemManager.h"
#include "digitalInputManager.h"
#include "temperatureManager.h"


struct GUIAnalogSignalsTag getGUIAnalogSignals(void);
void manageCommunications(void);
void getSystemManagerSignals(void);
void getErrorSignals(void);
void getReferenceHandlerSignals(void);
void getAnalogSignals(void);
void getDigitalSignals(void);
void performGUISideTasks(void);



#endif /* APP_INCLUDE_COMMUNICATIONMANAGER_H_ */
