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
// Definitions
//
#define MIN_DUTY_VALUE  0.0
#define MAX_DUTY_VALUE  100.0
#define MIN_DUTY_COMPARE    0
//Counter compare module (CMPA) uses the time counter variable to compare in order to set the
//correct PWM duty cycle, for this, it is important to know how many counts there are in a cycle.
//In the PWMConfig.c file, the period of the duty cycle is set by assigning the number of clk of a
//a period, this is done in the command 'EPwm1Regs.TBPRD = INTERNAL_FREQ/(2*SW_FREQ);'
//Since the configured carrier is a symmetrical triangular, the real period is actually twice as
//much but the counter will reach maximum that value.
#define MAX_DUTY_COMPARE    INTERNAL_FREQ/(2*SW_FREQ)


//
// Object declaration
//
typedef struct DutyCycleTag
{
    float dutyValue;
    Uint16 dutyCompare;
} DutyCycle;


typedef struct DutyCycleListTag
{
    DutyCycle legA;
    DutyCycle legB;
    DutyCycle legC;

    float minDutyValue;
    float maxDutyValue;

    Uint16 minDutyCompare;
    Uint16 maxDutyCompare;
} DutyCycleListType;


//
// Function prototyping
//
void initPWM();
void setDutyA(float);
void setDutyB(float);
void setDutyC(float);
void setAllDuties(float);
float readDutyA();
float readDutyB();
float readDutyC();
float readMaxDuty();

#endif /* APP_DUTYCYCLE_H_ */
