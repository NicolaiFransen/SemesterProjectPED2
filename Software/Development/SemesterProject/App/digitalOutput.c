/*
 * digitalOutput.c
 *
 *  Created on: 27. mar. 2019
 *      Author: Nicolai Fransen
 */

#include "digitalOutput.h"

/*
 * Object constructor: Sets pin to the object
 * Args:
 *  - Object to be initialized
 *  - GPIO number i.e. GPIO08
 */
void digitalOutput_Constructor(DigitalOutput *output, int GPIOpin)
{
    output->pin = GPIOpin;
    output->state = OFF;
}


/*
 * This function determines if the output shall be set high or low
 * by checking the input argument "state"
 */
void setDigitalOutput(DigitalOutput *output, digitalOutputStatus state)
{
    if (state == ON)
        setDigitalOutputHigh(output);
    else
        setDigitalOutputLow(output);

    output->state = state;
}

/*
 * These functions determines if the desired output is in port A or B.
 * Then sets the bit corresponding to the output to 1 by shifting.
 * To set high we use GPxSET, and to set low we use GPxCLEAR.
 */
void setDigitalOutputHigh(DigitalOutput *output)
{
    if (pinIsInPortA(output->pin))
        GpioDataRegs.GPASET.all |= ((Uint32)1 << output->pin);

    else if (pinIsInPortB(output->pin))
    {
        int pinReferredToPortB = output->pin - 32;
        GpioDataRegs.GPBSET.all |= ((Uint32)1 << pinReferredToPortB);
    }
}

void setDigitalOutputLow(DigitalOutput *output)
{
    if (pinIsInPortA(output->pin))
        GpioDataRegs.GPACLEAR.all |= ((Uint32)1 << output->pin);

    else if (pinIsInPortB(output->pin))
    {
        int pinReferredToPortB = output->pin - 32;
        GpioDataRegs.GPBCLEAR.all |= ((Uint32)1 << pinReferredToPortB);
    }
}

