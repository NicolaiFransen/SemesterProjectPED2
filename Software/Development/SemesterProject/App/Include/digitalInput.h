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
    unsigned char pin:6;
    unsigned char state:1;
} DigitalInput;

//
// Function prototyping
//
void digitalInput_Constructor(DigitalInput *input, int pin);
int digitalInput_ReadState(DigitalInput *input);
int pinIsInPortA(int pin);
int pinIsInPortB(int pin);




#endif /* APP_INCLUDE_DIGITALINPUT_H_ */
