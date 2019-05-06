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
DutyCycleListType DutyCycleList;


/*
 * Duty cycle is set on the leg A.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyA(float duty)
{
    //Assign duty value to struct.
    DutyCycleList.legA.dutyValue = duty;

    //Obtain comparator value.
    DutyCycleList.legA.dutyCompare = (Uint16)(MAX_DUTY_COMPARE * duty * MAX_DUTY_VALUE_INV);

    //Assign comparator to PWM module.
    EPwm1Regs.CMPA.half.CMPA = DutyCycleList.legA.dutyCompare;
}


/*
 * Duty cycle is set on the leg B.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyB(float duty)
{
    //Assign duty value to struct.
    DutyCycleList.legB.dutyValue = duty;

    //Obtain comparator value.
    DutyCycleList.legB.dutyCompare = (Uint16)(MAX_DUTY_COMPARE * duty * MAX_DUTY_VALUE_INV);

    //Assign comparator to PWM module.
    EPwm2Regs.CMPA.half.CMPA = DutyCycleList.legB.dutyCompare;
}


/*
 * Duty cycle is set on the leg C.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyC(float duty)
{
    //Assign duty value to struct.
    DutyCycleList.legC.dutyValue = duty;

    //Obtain comparator value.
    DutyCycleList.legC.dutyCompare = (Uint16)(MAX_DUTY_COMPARE * duty * MAX_DUTY_VALUE_INV);

    //Assign comparator to PWM module.
    EPwm3Regs.CMPA.half.CMPA = DutyCycleList.legC.dutyCompare;
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
    return DutyCycleList.legA.dutyValue;
}

/*
 * Duty cycle is read from the leg B.
 * This function returns the current duty cycle set on leg B.
 */
float readDutyB()
{
    return DutyCycleList.legB.dutyValue;
}

/*
 * Duty cycle is read from the leg C.
 * This function returns the current duty cycle set on leg C.
 */
float readDutyC()
{
    return DutyCycleList.legC.dutyValue;
}
