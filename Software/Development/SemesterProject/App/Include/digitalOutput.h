/*
 * digitalOutput.h
 *
 *  Created on: 27. mar. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_DIGITALOUTPUT_H_
#define APP_INCLUDE_DIGITALOUTPUT_H_

#include "DSP28x_Project.h"
#include "digitalInput.h"
//
// Digital output definition status
//
typedef enum
{
    OFF,
    ON
} digitalOutputStatus;

//
// Object declaration
//
typedef struct DigitalOutputTag
{
    unsigned char pin:6;
    digitalOutputStatus state;
} DigitalOutput;

//
// Function prototyping
//
void digitalOutput_Constructor(DigitalOutput *output, int pin);
void setDigitalOutput(DigitalOutput *output, digitalOutputStatus state);
void setDigitalOutputHigh(DigitalOutput *output);
void setDigitalOutputLow(DigitalOutput *output);

#endif /* APP_INCLUDE_DIGITALOUTPUT_H_ */
