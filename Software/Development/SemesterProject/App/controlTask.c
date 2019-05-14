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
        {
            // Call open-loop function
            openLoopVFControl();
        }

         else
         {
            // Call closed-loop function
             runStartUpControl();
         }
    }
}

/*
 * This function will return the state of the open-loop/closed-loop switch.
 */
int isOpenLoopControlSelected(void)
{
    return isOpenClosedLoopSelectionSwitchEnabled();
}

