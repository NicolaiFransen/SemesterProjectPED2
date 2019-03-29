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
 *  In this case, whenever the reference handler calls getGUIAnalogSignals()
 *  a struct containing all the variables is returned.
 *
 *  Now the system is able to:
 *      *Collect the variables from other SWC:
 *          **AnalogInputMgr
 *          **SystemMgr
 *          **DigitalInputMgr
 *          ++ReferenceHandlerMgr ----> To be developed
 *          ++closed loop control ----> To be developed
 *          ++ErrorMgr            ----> To be developed
 *      *Get the values from GUI and allow the read from other software components
 *          **struct GUIAnalogSignalsTag getGUIAnalogSignals(void)
 */

#include "communicationManager.h"

/*
 * Global variable definition -- Necessary for GUI interaction
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


//Variables updated by GUI
volatile float COMMS_GUITorqueRef, COMMS_GUISpeedRef, COMMS_GUIBrakeRef;
volatile int COMMS_GUICruiseControlEnabled, COMMS_GUIReferenceSourcepushbutton;

//Support variables for GUI
volatile int COMMS_TorqueReferenceSliderEnabled, COMMS_TorqueReferenceSliderDisabled;

// Quasi-Global variables
static struct GUIAnalogSignalsTag
{
    float TorqueReference;
    float SpeedReference;
    float BrakeReference;
    int CruiseControlEnabled;
    int ReferenceSourcePushbutton;
}GUIAnalogSignals;

/*
 * This function gathers the variables from the GUI to be used in other SWC
 *                      GUI ---> CommunicationMgr ---> SWC
 */
struct GUIAnalogSignalsTag getGUIAnalogSignals(void)
{
    GUIAnalogSignals.TorqueReference = COMMS_GUITorqueRef;
    GUIAnalogSignals.SpeedReference = COMMS_GUISpeedRef;
    GUIAnalogSignals.BrakeReference = COMMS_GUIBrakeRef;
    GUIAnalogSignals.ReferenceSourcePushbutton = COMMS_GUIReferenceSourcepushbutton;
    GUIAnalogSignals.CruiseControlEnabled = COMMS_GUICruiseControlEnabled;
    return GUIAnalogSignals;
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
//    getErrorSignals();    todo
//    getReferenceHandlerSignals(); todo
//    getClosedLoopControlSignals(); todo
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
//    COMMS_ReferenceSource = readReferenceSource(void); to be developed
}

void getAnalogSignals(void)
{   //Using AnalogInputManager Interface
    COMMS_DClinkVoltage = getDCLinkMeasurement();
    COMMS_ControlSupplyVoltage = getControlsupplyMeasurement();
    COMMS_PCBTorqueReference = getTorqueReferenceSliderMeasurement();
    COMMS_PCBBrakeReference = getBrakeReferenceSliderMeasurent();
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
    COMMS_TorqueReferenceSliderEnabled = COMMS_GUICruiseControlEnabled;
    COMMS_TorqueReferenceSliderDisabled = !COMMS_GUICruiseControlEnabled;
}


