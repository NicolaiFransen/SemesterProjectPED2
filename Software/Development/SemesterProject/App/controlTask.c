/*
 * controlTask.c
 *
 *  Created on: 22. mar. 2019
 *      Author: Nicolai Fransen
 */

#include "controlTask.h"
#include "errorManager.h"

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
             setDutyB(0);
             setDutyA(0);
             setDutyC(0);
            // Call closed-loop function
            // runClosedLoopControl();
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

