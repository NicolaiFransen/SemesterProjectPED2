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
#include "referenceHandler.h"



typedef struct
{
    int previousValue;
    int GUIValue;
    int pushbuttonHasBeenPressed;
}GUIPushbuttonTag;

struct GUIPushbuttonListTag
{
    GUIPushbuttonTag speedIncreasePushButton;
    GUIPushbuttonTag speedDecreasePushButton;
    GUIPushbuttonTag referenceSourcePushButton;
    GUIPushbuttonTag referenceTypePushButton;
};

typedef struct
{
    float TorqueReference;
    float SpeedReference;
    float BrakeReference;
    int ReferenceTypePushbutton;
    int ReferenceSourcePushbutton;
    int SpeedIncreasePushbutton;
    int SpeedDecreasePushbutton;
}GUISignalsTag;

GUISignalsTag getGUISignals(void);
void manageCommunications(void);
void getSystemManagerSignals(void);
void getErrorSignals(void);
void getReferenceHandlerSignals(void);
void getAnalogSignals(void);
void getDigitalSignals(void);
void performGUISideTasks(void);
void handleGUIPushbuttons(void);
void updatePushButtonList(void);
void handlePushbuttonsPress(void);
void restartPushbuttonsValue(void);
void initializeGUIPushbuttonsStructure(void);


#endif /* APP_INCLUDE_COMMUNICATIONMANAGER_H_ */
