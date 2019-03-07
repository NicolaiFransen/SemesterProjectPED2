/*
 * digitalInput.h
 *
 *  Created on: Mar 4, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_DIGITALINPUT_H_
#define APP_INCLUDE_DIGITALINPUT_H_

//
// Object declaration
//
typedef struct DigitalInputTag
{
    int pin;
    int state;
} DigitalInput;

//
// Function prototyping
//
void DigitalInput_Constructor(DigitalInput *input, int pin);
int DigitalInput_ReadState(DigitalInput *input);
int pinIsInPortA(int pin);
int pinIsInPortB(int pin);




#endif /* APP_INCLUDE_DIGITALINPUT_H_ */
