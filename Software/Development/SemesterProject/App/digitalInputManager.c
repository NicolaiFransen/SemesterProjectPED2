//###########################################################################
//FILE: digitalInputManager.c
//
//Project: Electric Go-kart
//
//Author: Nicolas, 3/3/19
//
//Notes:    Digital input manager. This SWC will loop through the digital
//          input array reading its value. It uses digitalInput object.
//
//
//###########################################################################

//###########################################################################

//
// Includes
//
#include "Include/digitalInputManager.h"
#include "digitalInput.h"
#include "../System/Include/GPIOConfig.h"

//
// Quasi-global variables definition
//

// initialization of all digital inputs {pin, state}
static struct digitalInputListTag
{
    DigitalInput regenBrakingPushbutton;
    DigitalInput torqueReferencePushbutton;
    DigitalInput openClosedLoopSelectionSwitch;
    DigitalInput powerSwitch;
    DigitalInput cruiseControlPushbutton;
    DigitalInput antiSlipPushbutton;
}digitalInputList;

/*
 * The goal of this function is to initialize the DigitalInput objects
 * to the desired GPIO pin. For that, GPIOConfig.h is used, where every
 * physical element is linked to a GPIO pin.
 *
 */
void initDigitalInputs(void)
{
    digitalInput_Constructor(&digitalInputList.regenBrakingPushbutton, B2);
    digitalInput_Constructor(&digitalInputList.torqueReferencePushbutton, B1);
    digitalInput_Constructor(&digitalInputList.openClosedLoopSelectionSwitch, S2);
    digitalInput_Constructor(&digitalInputList.powerSwitch, S1);
    digitalInput_Constructor(&digitalInputList.cruiseControlPushbutton, B3);
    digitalInput_Constructor(&digitalInputList.antiSlipPushbutton, B4);
}

/*
 * This function performs the read of all the elements inside DigitalInputList struct.
 * It starts by initializing the structPointer to the memory position of DigitalInputList,
 * then it determines the final position of the struct (where the struct object is finished)
 * and iterates over every DigitalInput object. In every loop, the pointer is pointing to a
 * different element in the list, and the read function is called. The pointer to every
 * DigitalInput object is used as an argument for reading the state.
 */
void readDigitalInputs(void)
{
    DigitalInput *structPointer;
    DigitalInput *initialMemoryPosition = &digitalInputList.regenBrakingPushbutton;
    DigitalInput *finalMemoryPosition = initialMemoryPosition + sizeof(digitalInputList)/sizeof(DigitalInput);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
    {
        digitalInput_ReadState(structPointer);
    }
}

/*
 * Abstraction functions
 */

int isRegenBrakingPushbuttonEnabled(void)
{
    return digitalInputList.regenBrakingPushbutton.state;
}

int isTorqueReferencePushButtonEnabled(void)
{
    return digitalInputList.regenBrakingPushbutton.state;
}

int isOpenClosedLoopSelectionSwitchEnabled(void)
{
    return digitalInputList.openClosedLoopSelectionSwitch.state;
}
int isPowerSwitchEnabled(void)
{
    return digitalInputList.powerSwitch.state;
}

int isCruiseControlPushbuttonEnabled(void)
{
    return digitalInputList.cruiseControlPushbutton.state;
}

int isAntiSlipPushbuttonEnabled(void)
{
    return digitalInputList.antiSlipPushbutton.state;
}

//
// End of File
//

