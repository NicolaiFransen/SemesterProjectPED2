/*
 * controlTask.c
 *
 *  Created on: 22. mar. 2019
 *      Author: Nicolai Fransen
 */

void executeControl(void)
{
    if (isOpenLoopControlSelected())
        // Call open-loop function
        //

    else
        // Call closed-loop function
        // runClosedLoopControl();
}

void disableDutyCycles(void)
{
    setAllDuties(0);
}

int isOpenLoopControlSelected(void)
{
    return isOpenClosedLoopSelectionSwitchEnabled();
}
