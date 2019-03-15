/*
 * dutyCycle.h
 *
 *  Created on: 12 mar. 2019
 *      Author: Aitor Teran
 */

#ifndef APP_DUTYCYCLE_H_
#define APP_DUTYCYCLE_H_

//
// Includes
//
#include "C28x_FPU_FastRTS.h"

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
    float dutyValue;
    Uint16 dutyCompare;
} DutyCycle;

typedef enum
{
    LEG_A,
    LEG_B,
    LEG_C,
    ERROR,
}SysMgrState;


//
// Function prototyping
//
void setDutyCycleA(float);
void setDutyCycleB(float);
void setDutyCycleC(float);
void setAllDuties(float);

#endif /* APP_DUTYCYCLE_H_ */
