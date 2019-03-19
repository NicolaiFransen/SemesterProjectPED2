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
/*static struct dutyCycleListTag
{
    DutyCycle legA;
    DutyCycle legB;
    DutyCycle legC;
}dutyCycleList;*/


/*
 * dutyCycleList constructor and initialization.
 */
void dutyConstructor(DutyCycle *dutyStruct)
{
    dutyStruct -> minDutyValue = MIN_DUTY_VALUE;
    dutyStruct -> maxDutyValue = MAX_DUTY_VALUE;
    dutyStruct -> minDutyCompare = MIN_DUTY_COMPARE;
    dutyStruct -> maxDutyCompare = MAX_DUTY_COMPARE;
}


/*
 * initPWM() initializes the static structs.
 * This function is only called at STARTUP.
 */
void initPWM(void)
{
    dutyConstructor(&dutyCycleList.legA);
    dutyConstructor(&dutyCycleList.legB);
    dutyConstructor(&dutyCycleList.legC);
}

/*
 * Assign duty value to struct.
 */
void assignDuty(float duty, DutyCycle *dutyStruct)
{
    dutyStruct -> dutyValue = duty;
}


/* CONSIDER REVISION to reduce computing load.
 * Function for internal use.
 * Function performs a linear regression to map the compare value.
 */
void calculateDutyCompare(DutyCycle *dutyStruct)
{
    dutyStruct -> dutyCompare = dutyStruct -> minDutyCompare + (Uint16)((float)(dutyStruct -> maxDutyCompare - dutyStruct -> minDutyCompare) * (dutyStruct -> dutyValue - dutyStruct -> minDutyValue) / (dutyStruct -> maxDutyValue - dutyStruct -> minDutyValue));
    //dutyStruct.dutyCompare = MAX_DUTY_COMPARE / 2; //For debugging purposes only (duty = 0.5);
}


/*
 * Set counter compare to correct value on leg A.
 */
void assignDutyToComparatorA()
{
    EPwm1Regs.CMPA.half.CMPA = dutyCycleList.legA.dutyCompare;
}


/*
 * Set counter compare to correct value on leg B.
 */
void assignDutyToComparatorB()
{
    EPwm2Regs.CMPA.half.CMPA = dutyCycleList.legB.dutyCompare;
}


/*
 * Set counter compare to correct value on leg C.
 */
void assignDutyToComparatorC()
{
    EPwm3Regs.CMPA.half.CMPA = dutyCycleList.legC.dutyCompare;
}


/*
 * Function for internal use.
 * Later the struct containing the duty information gets updated.
 */
void fillDutyStruct(float duty, DutyCycle *dutyStruct)
{
    assignDuty(duty, dutyStruct);
    calculateDutyCompare(dutyStruct); //Transform duty to comparator.
}


/*
 * Duty cycle is set on the leg A.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyA(float duty)
{
    fillDutyStruct(duty, &dutyCycleList.legA);
    assignDutyToComparatorA();
}


/*
 * Duty cycle is set on the leg B.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyB(float duty)
{
    fillDutyStruct(duty, &dutyCycleList.legB);
    assignDutyToComparatorC();
}


/*
 * Duty cycle is set on the leg C.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyC(float duty)
{
    fillDutyStruct(duty,  &dutyCycleList.legC);
    assignDutyToComparatorC();
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
    return dutyCycleList.legA.dutyValue;
}

/*
 * Duty cycle is read from the leg B.
 * This function returns the current duty cycle set on leg B.
 */
float readDutyB()
{
    return dutyCycleList.legB.dutyValue;
}

/*
 * Duty cycle is read from the leg C.
 * This function returns the current duty cycle set on leg C.
 */
float readDutyC()
{
    return dutyCycleList.legC.dutyValue;
}
