//###########################################################################
//FILE: digitalInput.c
//
//Project: Electric Go-kart
//
//Author: Nicolas, 3/3/19
//
//Notes: Digital input object
//
//
//###########################################################################

//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "digitalInput.h"

//
// Quasi-global variables definition
//


void DigitalInput_Constructor(DigitalInput *input, int pin)
{
    input->pin = pin;
}

int DigitalInput_ReadState(DigitalInput *input)
{
    input->state = GpioDataRegs.GPBDAT.bit.GPIO52;
    return input->state;
}

int DigitalInput_UpdateState(DigitalInput *input)
{
    //input->state = readGPIO(); // see how the read should actually be done
    return input->state;
}
//
// End of File
//

