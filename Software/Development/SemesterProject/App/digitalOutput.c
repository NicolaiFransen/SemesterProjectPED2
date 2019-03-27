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
 *  - GPIO pin number
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
void setDigitalOutput(DigitalOutput *output, LEDStatus state)
{
    if (state == ON)
        setDigitalOutputHigh(output);
    else
        setDigitalOutputLow(output);

    output->state = state;
}

/*
 *
 */
void setDigitalOutputHigh(DigitalOutput *output)
{
    if (pinIsInPortA(output->pin))
        GpioDataRegs.GPASET.all |= (1 << output->pin);

    else if (pinIsInPortB(output->pin))
        GpioDataRegs.GPBSET.all | (1 << output->pin);
}

void setDigitalOutputLow(DigitalOutput *output)
{
    if (pinIsInPortA(output->pin))
        GpioDataRegs.GPACLEAR.all | (1 << output->pin);

    else if (pinIsInPortB(output->pin))
        GpioDataRegs.GPBCLEAR.all | (1 << output->pin);
}

