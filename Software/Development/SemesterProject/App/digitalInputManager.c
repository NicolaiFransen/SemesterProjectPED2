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
    DigitalInput referenceSourcePushbutton;
    DigitalInput referenceTypePushbutton;
    DigitalInput openClosedLoopSelectionSwitch;
    DigitalInput powerSwitch;
    DigitalInput speedIncreasePushbutton;
    DigitalInput speedDecreasePushbutton;
    DigitalInput userACKPushbutton;
    DigitalInput errorMonitoringEnable;
}digitalInputList;

/*
 * The goal of this function is to initialize the DigitalInput objects
 * to the desired GPIO pin. For that, GPIOConfig.h is used, where every
 * physical element is linked to a GPIO pin.
 *
 */
void initDigitalInputs(void)
{
    digitalInput_Constructor(&digitalInputList.referenceTypePushbutton, B2);
    digitalInput_Constructor(&digitalInputList.referenceSourcePushbutton, B1);
    digitalInput_Constructor(&digitalInputList.openClosedLoopSelectionSwitch, S2);
    digitalInput_Constructor(&digitalInputList.powerSwitch, S1);
    digitalInput_Constructor(&digitalInputList.speedIncreasePushbutton, J10);
    digitalInput_Constructor(&digitalInputList.speedDecreasePushbutton, J9);
    digitalInput_Constructor(&digitalInputList.userACKPushbutton, J12);
    digitalInput_Constructor(&digitalInputList.errorMonitoringEnable, J8);
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
    DigitalInput *initialMemoryPosition = &digitalInputList.referenceSourcePushbutton;
    DigitalInput *finalMemoryPosition = initialMemoryPosition + sizeof(digitalInputList)/sizeof(DigitalInput);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
    {
        digitalInput_ReadState(structPointer);
    }
}

/*
 * Abstraction functions
 *
 */

int isReferenceTypePushbuttonEnabled(void)
{
    return digitalInputList.referenceTypePushbutton.state;
}

int isReferenceSourcePushbuttonEnabled(void)
{
    return digitalInputList.referenceSourcePushbutton.state;
}

int isOpenClosedLoopSelectionSwitchEnabled(void)
{
    return digitalInputList.openClosedLoopSelectionSwitch.state;
}
int isPowerSwitchEnabled(void)
{
    return digitalInputList.powerSwitch.state;
}

int isErrorMonitorSwitchEnabled(void)
{
    return digitalInputList.errorMonitoringEnable.state;
}

int isSpeedIncreasePushbuttonEnabled(void)
{
    return digitalInputList.speedIncreasePushbutton.state;
}

int isSpeedDecreasePushbuttonEnabled(void)
{
    return digitalInputList.speedDecreasePushbutton.state;
}

int isUserACKPushbuttonEnabled(void)
{
    return digitalInputList.userACKPushbutton.state;
}

//
// End of File
//

