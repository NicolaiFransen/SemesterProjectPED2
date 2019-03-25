/*
 * controlTask.c
 *
 *  Created on: 22. mar. 2019
 *      Author: Nicolai Fransen
 */

#include "controlTask.h"

/*
 * This function will check the state of the open-loop/closed-loop switch,
 * and from that execute the desired operation mode.
 */
void executeControl(void)
{
    if (isOpenLoopControlSelected())
        // Call open-loop function
        setFrequencyFromPot();

    // else
        // Call closed-loop function
        // runClosedLoopControl();
}

/*
 * This function should be called when an error happens.
 * It will set all the duties to 0, to stop the motor.
 */
void disableDutyCycles(void)
{
    setAllDuties(0);
    // Consider to disable the PWM enable output pin as well
}

/*
 * This function will return the state of the open-loop/closed-loop switch.
 */
int isOpenLoopControlSelected(void)
{
    return isOpenClosedLoopSelectionSwitchEnabled();
}
