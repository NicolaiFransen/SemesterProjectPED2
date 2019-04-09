/*
 * communicationManager.c
 *
 *  Created on: Mar 20, 2019
 *      Author: Nicolas
 *  Description: The communication Manager is the software component that allows
 *  the communication between the GUI and the rest of the system.
 *  In order to allow the read of the variables in the GUI, the variables
 *  must be declared as global. So when manageCommunications() is called from
 *  the scheduler, the CommunicationsManager will update all the variables that
 *  are to be showed in the GUI. That explained the communication
 *                  DSP ----> CommunicationManager --> GUI
 *  Now there are some variables that the user might modify in the GUI, like
 *  a torque reference, in that case the communication will follow the next:
 *                  GUI ---->COmmunicationManager --> ReferenceHandler
 *  In this case, whenever the reference handler calls getGUISignals()
 *  a struct containing all the variables is returned.
 *
 *  Now the system is able to:
 *      *Collect the variables from other SWC:
 *          **AnalogInputMgr
 *          **SystemMgr
 *          **DigitalInputMgr
 *          **ReferenceHandlerMgr
 *          ++closed loop control ----> To be developed
 *          ++ErrorMgr            ----> To be developed
 *      *Get the values from GUI and allow the read from other software components
 *          **struct GUISignalsTag getGUISignals(void)
 */

#include "communicationManager.h"

/*
 * Global variable definition -- Necessary for GUI interaction
 * Volatile variables to be read from GUI must be explicitly initialized to 0.
 */
//Variables provided by other software components
    //Analog Manager
volatile float COMMS_DClinkVoltage, COMMS_ControlSupplyVoltage, COMMS_PCBTorqueReference;
volatile float COMMS_PCBBrakeReference, COMMS_PedalTorqueReference, COMMS_PedalBrakeReference;
volatile float COMMS_Thermometer1, COMMS_Thermometer2;
    //System Manager
volatile SysMgrState COMMS_SysMgrState;
    //DigitalInputManager
volatile int COMMS_PowerEnabledSwitch;
    //Reference Handler
volatile int COMMS_ReferenceSource;
volatile float COMMS_OpenLoopReference, COMMS_speedReference, COMMS_torqueReference;

//Variables updated by GUI
volatile float COMMS_GUITorqueRef = 0.0, COMMS_GUISpeedRef = 0.0, COMMS_GUIBrakeRef = 0.0;
volatile int COMMS_GUIReferenceTypepushbutton = 0, COMMS_GUIReferenceSourcepushbutton = 0;
volatile int COMMS_GUIspeedDecreasePushButton = 0, COMMS_GUIspeedIncreasePushButton = 0;

//Support variables for GUI
volatile int COMMS_TorqueReferenceSliderEnabled = 1, COMMS_TorqueReferenceSliderDisabled;

// Quasi-Global variables
static GUISignalsTag GUISignals;
static struct GUIPushbuttonListTag GUIPushButtonList;

/*
 * This function gathers the variables from the GUI to be used in other SWC
 *                      GUI ---> CommunicationMgr ---> SWC
 */
GUISignalsTag getGUISignals(void)
{
    GUISignals.TorqueReference = COMMS_GUITorqueRef;
    GUISignals.SpeedReference = COMMS_GUISpeedRef;
    GUISignals.BrakeReference = COMMS_GUIBrakeRef;
    GUISignals.ReferenceSourcePushbutton = GUIPushButtonList.referenceSourcePushButton.pushbuttonHasBeenPressed;
    GUISignals.ReferenceTypePushbutton = GUIPushButtonList.referenceTypePushButton.pushbuttonHasBeenPressed;
    GUISignals.SpeedIncreasePushbutton = GUIPushButtonList.speedIncreasePushButton.pushbuttonHasBeenPressed;
    GUISignals.SpeedDecreasePushbutton = GUIPushButtonList.speedDecreasePushButton.pushbuttonHasBeenPressed;

    restartPushbuttonsValue();

    return GUISignals;
}

/*
 * This function gathers the variables to be showed in the GUI from other SWC.
 *                      SWC ---> CommunicationMgr ---> GUI
 */
void manageCommunications(void)
{
    getSystemManagerSignals();
    getAnalogSignals();
    performGUISideTasks();
    getDigitalSignals();
//    getErrorSignals();                todo
    getReferenceHandlerSignals();
//    getClosedLoopControlSignals();    todo
}


void getSystemManagerSignals(void)
{   //Using System Manager Interface
    COMMS_SysMgrState = readSystemState();
}

void getErrorSignals(void)
{   //Using errorManager Interface
    //todo
}

void getReferenceHandlerSignals(void)
{   //Using ReferenceHandler Interface
    COMMS_ReferenceSource = getReferenceSource();
    COMMS_OpenLoopReference = getOpenLoopReference();
    COMMS_speedReference = getSpeedReference();
    COMMS_torqueReference = getTorqueReference();
}

void getAnalogSignals(void)
{   //Using AnalogInputManager Interface
    COMMS_DClinkVoltage = getDCLinkMeasurement();
    COMMS_ControlSupplyVoltage = getControlsupplyMeasurement();
    COMMS_PCBTorqueReference = getTorqueReferenceSliderMeasurement();
//    COMMS_PCBBrakeReference = getBrakeReferenceSliderMeasurement();
    COMMS_PedalTorqueReference = getTorqueReferencePedalMeasurement();
    COMMS_PedalBrakeReference = getBrakeReferencePedalMeasurement();
    COMMS_Thermometer1 = getThermometer1Measurement();
    COMMS_Thermometer2 = getThermometer2Measurement();
}

void getDigitalSignals(void)
{
    COMMS_PowerEnabledSwitch = isPowerSwitchEnabled();
}

void performGUISideTasks(void)
{
    COMMS_TorqueReferenceSliderEnabled = torqueControlIsEnabled();      //Using Reference Handler Interface
    COMMS_TorqueReferenceSliderDisabled = !torqueControlIsEnabled();
    handleGUIPushbuttons();
}

void initializeGUIPushbuttonsStructure(void)
{
    GUIPushbuttonTag *structIterator;
    GUIPushbuttonTag *startPosition = &GUIPushButtonList.speedIncreasePushButton;
    GUIPushbuttonTag *finalPosition = startPosition + sizeof(GUIPushButtonList)/sizeof(GUIPushbuttonTag);
    for (structIterator = startPosition; structIterator < finalPosition; structIterator++)
    {
        structIterator->previousValue = 0;
    }
}

void handleGUIPushbuttons(void)
{
    updatePushButtonList();
    handlePushbuttonsPress();
}

void updatePushButtonList(void)
{
    GUIPushButtonList.referenceSourcePushButton.GUIValue = COMMS_GUIReferenceSourcepushbutton;
    GUIPushButtonList.referenceTypePushButton.GUIValue = COMMS_GUIReferenceTypepushbutton;
    GUIPushButtonList.speedDecreasePushButton.GUIValue = COMMS_GUIspeedDecreasePushButton;
    GUIPushButtonList.speedIncreasePushButton.GUIValue = COMMS_GUIspeedIncreasePushButton;
}

void handlePushbuttonsPress(void)
{
    GUIPushbuttonTag *structIterator;
    GUIPushbuttonTag *startPosition = &GUIPushButtonList.speedIncreasePushButton;
    GUIPushbuttonTag *finalPosition = startPosition + sizeof(GUIPushButtonList)/sizeof(GUIPushbuttonTag);
    for (structIterator = startPosition; structIterator < finalPosition; structIterator++)
    {
        if (structIterator->previousValue < structIterator->GUIValue)
        {
            structIterator->pushbuttonHasBeenPressed = 1;
            structIterator->previousValue = structIterator->GUIValue;
        }
    }
}

void restartPushbuttonsValue(void)
{
    GUIPushbuttonTag *structIterator;
    GUIPushbuttonTag *startPosition = &GUIPushButtonList.speedIncreasePushButton;
    GUIPushbuttonTag *finalPosition = startPosition + sizeof(GUIPushButtonList)/sizeof(GUIPushbuttonTag);
    for (structIterator = startPosition; structIterator < finalPosition; structIterator++)
    {
        structIterator->pushbuttonHasBeenPressed = 0;
    }
}

