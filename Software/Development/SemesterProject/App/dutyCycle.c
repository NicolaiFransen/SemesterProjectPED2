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
 * dutyCycleList constructor and initialization.
 */
void dutyConstructor(DutyCycleListType *dutyStruct)
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
    dutyConstructor(&DutyCycleList);
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
void calculateDutyCompare(DutyCycleListType *dutyListStruct, DutyCycle *dutyStruct)
{
    dutyStruct -> dutyCompare = dutyListStruct -> minDutyCompare + (Uint16)((float)(dutyListStruct -> maxDutyCompare - dutyListStruct -> minDutyCompare) * (dutyStruct -> dutyValue - dutyListStruct -> minDutyValue) / (dutyListStruct -> maxDutyValue - dutyListStruct -> minDutyValue));
    //dutyStruct.dutyCompare = MAX_DUTY_COMPARE / 2; //For debugging purposes only (duty = 0.5);
}


/*
 * Set counter compare to correct value on leg A.
 */
void assignDutyToComparatorA()
{
    EPwm1Regs.CMPA.half.CMPA = DutyCycleList.legA.dutyCompare;
}


/*
 * Set counter compare to correct value on leg B.
 */
void assignDutyToComparatorB()
{
    EPwm2Regs.CMPA.half.CMPA = DutyCycleList.legB.dutyCompare;
}


/*
 * Set counter compare to correct value on leg C.
 */
void assignDutyToComparatorC()
{
    EPwm3Regs.CMPA.half.CMPA = DutyCycleList.legC.dutyCompare;
}


/*
 * Function for internal use.
 * Later the struct containing the duty information gets updated.
 */
void fillDutyStruct(float duty, DutyCycleListType *dutyListStruct, DutyCycle *dutyStruct)
{
    assignDuty(duty, dutyStruct);
    calculateDutyCompare(dutyListStruct, dutyStruct); //Transform duty to comparator.
}


/*
 * Duty cycle is set on the leg A.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyA(float duty)
{
    fillDutyStruct(duty, &DutyCycleList, &DutyCycleList.legA);
    assignDutyToComparatorA();
}


/*
 * Duty cycle is set on the leg B.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyB(float duty)
{
    fillDutyStruct(duty, &DutyCycleList, &DutyCycleList.legB);
    assignDutyToComparatorB();
}


/*
 * Duty cycle is set on the leg C.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyC(float duty)
{
    fillDutyStruct(duty, &DutyCycleList,  &DutyCycleList.legC);
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
