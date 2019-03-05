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

}DigitalInputList;

void initInputs(void)
{
    DigitalInput_Constructor(&DigitalInputList.switch_1, 4); // the second argument is the pin,
}

void readDigitalInputs(void)//
{
    DigitalInput_ReadState(&DigitalInputList.switch_1);
}


//
// End of File
//

