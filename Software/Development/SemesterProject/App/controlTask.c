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
    if (readSystemState() == RUNNING)
    {
        if (isOpenLoopControlSelected())
            // Call open-loop function
            openLoopVFControl();

        // else
            // Call closed-loop function
            // runClosedLoopControl();
    }
    else
        errorReactionControl();

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
 * This function disables the PWM driver circuit, by clearing the enable signal.
 */
void disablePWMDrivers(void)
{
    // Set the enable output to 0
    GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;
}

/*
 * This function will return the state of the open-loop/closed-loop switch.
 */
int isOpenLoopControlSelected(void)
{
    return isOpenClosedLoopSelectionSwitchEnabled();
}

/*
 * This function will be called when system state is not in "Running"
 */
void errorReactionControl(void)
{
    disableDutyCycles();
    disablePWMDrivers();
    // restartControlVariables();  Uncomment when created under  closedLoopControlManager
}
