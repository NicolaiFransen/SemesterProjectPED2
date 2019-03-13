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


//
// Quasi-global variables definition
//


static struct dutyCycles
{
    DutyCycle legA;
    DutyCycle legB;
    DutyCycle legC;
}dutyCycleList;


/*
 * Object constructor: sets the pin in object.
 * Args
 *  -object to be initialized
 *  -PWM pin
 *
void dutyCycle_Constructor(dutyCycle *input, int PWMpin)
{
    input->pin = PWMpin;
}*/


/*
 * Duty cycle is set on the leg A.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 */
void setDutyCycleA(float duty)
{

}


/*
 * Duty cycle is set on the leg B.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 */
void setDutyCycleB(float duty)
{

}


/*
 * Duty cycle is set on the leg C.
 * This function expects an input duty value that is the corresponding PWM duty to be set.
 */
void setDutyCycleC(float duty)
{

}


/*
 * All duties are set to the corresponding duty cycle.
 */
void setAllDuties(float duty)
{
    setDutyCycleA(float duty);
    setDutyCycleB(float duty);
    setDutyCycleC(float duty);
}


/*
 * Duty cycle is read from the leg A.
 * This function returns the current duty cycle set on leg A.
 */
void readDutyCycleA()
{
    //return a float (duty cycle value)
}
