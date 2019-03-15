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
static struct dutyCycleTag
{
    DutyCycle legA;
    DutyCycle legB;
    DutyCycle legC;
}dutyCycle;


/* CONSIDER REVISION to reduce computing load.
 * Function for internal use.
 * map function performs a linear regression.
 * Inputs are a value with its corresponding lower and upper limits
 * as well as the lower and upper limits of the variable to return.
 */
Uint16 mapDuty(float x, float x_min, float x_max, Uint16 y_min, Uint16 y_max)
{
    return y_min + (Uint16)((float)(y_max-y_min)*(x-x_min)/(x_max-x_min));
}

/*
 * Function for internal use.
 * The duty cycle is checked in case it lies outside of boundaries.
 * Later the struct containing the duty information gets updated.
 */
void fillDutyStruct(float duty, int leg)
{

    //Counter compare module uses the time counter variable to compare in order to set the
    //correct PWM duty cycle, for this, it is important to know how many counts there are in a cycle.

    //In the PWMConfig.c file, the period of the duty cycle is set by assigning the number of clk of a
    //a period, this is done in the command 'EPwm1Regs.TBPRD = INTERNAL_FREQ/(2*SW_FREQ);'
    //Since the configured carrier is a symmetrical triangular, the real period is actually twice as
    //much but the counter will reach maximum that value.

    //duty cycle float variable must then be converted into a Uint16 with correspondent
    //input 0.00 -> output 0 and input 100.00 -> output INTERNAL_FREQ/(2*SW_FREQ).

    //Error check.
    if (duty > 100)
    {
        //Act accordingly.
        //REPORT ERROR.
        duty = 100; //For now, adjust to limit.
    }
    else if (duty < 0)
    {
        //Act accordingly.
        //REPORT ERROR
        duty = 0; //For now, adjust to limit.
    }


    //No errors so save to struct.
    switch (leg)
    {
        case LEG_A:
        {

            dutyCycle.legA.dutyValue = duty;

            //Transform duty to comparator.
            dutyCycle.legA.dutyCompare = mapDuty(duty, 0.0, 100.0, 0, INTERNAL_FREQ/(2*SW_FREQ));
        }break;

        case LEG_B:
        {
            dutyCycle.legB.dutyValue = duty;

            //Transform duty to comparator.
            dutyCycle.legB.dutyCompare = mapDuty(duty, 0.0, 100.0, 0, INTERNAL_FREQ/(2*SW_FREQ));
        }break;
        case LEG_C:
        {
            dutyCycle.legC.dutyValue = duty;

            //Transform duty to comparator.
            dutyCycle.legC.dutyCompare = mapDuty(duty, 0.0, 100.0, 0, INTERNAL_FREQ/(2*SW_FREQ));
        }break;

        default:
        {

        }break;
    }

}


/*
 * Duty cycle is set on the leg A.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyA(float duty)
{
    fillDutyStruct(duty, LEG_A);

    //Set counter compare to correct value.
    EPwm1Regs.CMPA.half.CMPA = dutyCycle.legA.dutyCompare;
}


/*
 * Duty cycle is set on the leg B.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyB(float duty)
{
    fillDutyStruct(duty, LEG_B);

    //Set counter compare to correct value.
    EPwm2Regs.CMPA.half.CMPA = dutyCycle.legA.dutyCompare;

}


/*
 * Duty cycle is set on the leg C.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 * duty cycle is a float ranging from 0 to 100.
 */
void setDutyC(float duty)
{
    fillDutyStruct(duty, LEG_C);

    //Set counter compare to correct value.
    EPwm3Regs.CMPA.half.CMPA = dutyCycle.legA.dutyCompare;
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
    return dutyCycle.legA.dutyValue;
}

/*
 * Duty cycle is read from the leg B.
 * This function returns the current duty cycle set on leg B.
 */
float readDutyB()
{
    return dutyCycle.legB.dutyValue;
}

/*
 * Duty cycle is read from the leg C.
 * This function returns the current duty cycle set on leg C.
 */
float readDutyC()
{
    return dutyCycle.legC.dutyValue;
}
