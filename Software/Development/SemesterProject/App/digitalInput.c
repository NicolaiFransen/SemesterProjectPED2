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

/*
 * Object constructor: sets the pin in the object.
 * Args
 *  -object to be initialized
 *  -GPIO pin
 */
void DigitalInput_Constructor(DigitalInput *input, int GPIOpin)
{
    input->pin = GPIOpin;
}

/*
 * The data from the whole port is accessed. The port contains 32 bits
 * of information. Every bit is equal to the state of every single
 * GPIO pin, as described in figure 1-82 from the technical reference.
 * Then, in order to access to every specific pin, the AND operation is
 * performed to a input.pin length array of '1' and then the result
 * is shifted, obtaining she single bit we are interested in.
 * E.g. input.pin = 0 (GPIO0) will return the state of the first bit.
 * For port B, the content is contained in a different register than port B,
 * then the same logic is followed but 32 bits are subtracted.
 *
 * It has a return which might be used if the value
 */
int DigitalInput_ReadState(DigitalInput *input)
{
    if(pinIsInPortA(input->pin))
    {
        input->state = (GpioDataRegs.GPADAT.all & (1 << input->pin)) >> input->pin;
    }
    if(pinIsInPortB(input->pin))
    {
        int pinReferredToPortB = input->pin - 32;
        input->state = (GpioDataRegs.GPBDAT.all & ( 1 << pinReferredToPortB )) >> pinReferredToPortB;
    }
    return input->state;
}

int pinIsInPortA(int pin)
{
    return (pin < 32);
}

int pinIsInPortB(int pin)
{
    return (pin > 31 && pin < 58);
}
