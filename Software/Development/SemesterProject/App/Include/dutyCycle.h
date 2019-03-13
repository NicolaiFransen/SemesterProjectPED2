/*
 * dutyCycle.h
 *
 *  Created on: 12 mar. 2019
 *      Author: Aitor Teran
 */

#ifndef APP_DUTYCYCLE_H_
#define APP_DUTYCYCLE_H_


//
//PIN definition. First item is the pwm to be outputed and
//the second item is the EPWM pin where the connector is placed in the PCB.
//It is in hexadecimal to allow correct understanding of each pin.
//CONSIDER THE LOCATION OF THESE DEFINITIONS AS WELL AS THE HEXADECIMAL FOR REVIEW.
//
#define PWM_A   0xA1
#define PWM_B   0xA2
#define PWM_C   0xA3


//
// Object declaration
//
typedef struct DutyCycleTag
{
    int dutyValue;
    int pin
} DutyCycle;


//
// Function prototyping
//
void setDutyCycleA(float duty);
void setDutyCycleB(float duty);
void setDutyCycleC(float duty);
void setAllDuties(float duty);


#endif /* APP_DUTYCYCLE_H_ */
