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

//
// Quasi-global variables definition
//

// initialization of all digital inputs {pin, state}
static struct
{
    DigitalInput switch_1;
    DigitalInput switch_2;
    DigitalInput powerSwitch;

}DigitalInputList;

/*
 * The goal of this function is to initialize the DigitalInput objects
 * to the desired GPIO pin and TBD if also to set the GPIO configuration
 * for digitalInput (basically following the procedure described in GPIOconfig.c)
 *
 */
void initInputs(void)
{
    DigitalInput_Constructor(&DigitalInputList.switch_1, 4);
    DigitalInput_Constructor(&DigitalInputList.switch_2, 5);
    DigitalInput_Constructor(&DigitalInputList.powerSwitch, 87);
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
    int initialMemoryPosition = &DigitalInputList;
    int finalMemoryPosition = initialMemoryPosition + sizeof(DigitalInputList);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
    {
        DigitalInput_ReadState(structPointer);
    }
}

/*
 * Abstraction functions
 */

int isPowerSwitchEnabled(void)
{
    return DigitalInputList.powerSwitch.state;
}

//
// End of File
//

