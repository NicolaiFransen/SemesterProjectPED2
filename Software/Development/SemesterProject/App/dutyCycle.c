/*
 * dutyCycle.c
 *
 *  Created on: 12 mar. 2019
 *      Author: Aitor Teran
 */
//
//###########################################################################

//###########################################################################



//
// Includes
//
#include "Include/dutyCycle.h"
#include "../System/Include/PWMConfig.h"


//
// Quasi-global variables definition
//
DutyCycles DutyCycleList;


/*
 * Duty cycle is set on the leg A.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyA(float duty)
{
    //Assign duty value to struct.
    DutyCycleList.dutyA = duty;

    //Calculate and assign comparator to PWM module.
    EPwm1Regs.CMPA.half.CMPA = (Uint16)(MAX_DUTY_COMPARE * duty / 100);
}


/*
 * Duty cycle is set on the leg B.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyB(float duty)
{
    //Assign duty value to struct.
    DutyCycleList.dutyB = duty;

    //Calculate and assign comparator to PWM module.
    EPwm2Regs.CMPA.half.CMPA = (Uint16)(MAX_DUTY_COMPARE * duty / 100);
}


/*
 * Duty cycle is set on the leg C.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyC(float duty)
{
    //Assign duty value to struct.
    DutyCycleList.dutyC = duty;

    //Calculate and assign comparator to PWM module.
    EPwm3Regs.CMPA.half.CMPA = (Uint16)(MAX_DUTY_COMPARE * duty / 100);
}


/*
 * All duties are set to the corresponding duty cycle.
 */
void setAllDuties(float duty)
{
    setDutyA(duty);
    setDutyB(duty);
    setDutyC(duty);
}


/*
 * Duty cycle is read from the leg A.
 * This function returns the current duty cycle set on leg A.
 */
float readDutyA()
{
    return DutyCycleList.dutyA;
}

/*
 * Duty cycle is read from the leg B.
 * This function returns the current duty cycle set on leg B.
 */
float readDutyB()
{
    return DutyCycleList.dutyB;
}

/*
 * Duty cycle is read from the leg C.
 * This function returns the current duty cycle set on leg C.
 */
float readDutyC()
{
    return DutyCycleList.dutyC;
}
