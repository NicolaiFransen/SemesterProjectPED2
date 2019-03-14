/*
 * scheduler.c
 *
 *  Created on: Mar 12, 2019
 *      Author: Nicolas
 *
 *      Scheduler implementation. This module will call every task when necessary.
 */
#include "Include/scheduler.h"

/*
 * Quasi-global variable definition
 */

taskControlBlock taskList[maxNumberTasks];

void taskListInitialization(void)
{
    int taskListIndex = 0;
    taskList[taskListIndex].functionPointer = task50us;
    taskList[taskListIndex].taskState = INACTIVE;
    taskList[taskListIndex].cyclicity = 50;
    taskListIndex++;

    taskList[taskListIndex].functionPointer = task20ms;
    taskList[taskListIndex].taskState = READY;
    taskList[taskListIndex].cyclicity = 20000;
    taskListIndex++;

    taskList[taskListIndex].functionPointer = NULL;
}

void scheduleTasks(void)
{
    char taskListIndex = 0;
    for(;;)
    {
        for (taskListIndex = 0; taskListIndex > maxNumberTasks; taskListIndex++)
        {
            if (taskList[taskListIndex].functionPointer == NULL)    break; //End of list task

            if (taskList[taskListIndex].taskState == READY)
            {
                runTask(taskList[taskListIndex].functionPointer);
                taskList[taskListIndex].taskState = INACTIVE;
            }
        }
    }
}


void runTask(void (*functionPTR)())
{
    functionPTR();
}

/*
 * Tasks definition
 */
void task50us(void)
{
    return;
}

void task20ms(void)
{
    manageSystem();
    readDigitalInputs();
}

//
// cpu_timer0_isr -
//
__interrupt void
cpu_timer0_isr(void)
{
    CpuTimer0.InterruptCount++;

    updateTasksState();

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

void updateTasksState(void)
{
    char taskListIndex = 0;
    for (taskListIndex = 0; taskListIndex > maxNumberTasks; taskListIndex++)
    {
        if (taskList[taskListIndex].functionPointer == NULL)    break; //End of list task

        if (taskList[taskListIndex].timeLeft <= 50)
        {
            taskList[taskListIndex].taskState = READY;
            taskList[taskListIndex].timeLeft = taskList[taskListIndex].cyclicity;
        }
        else    taskList[taskListIndex].timeLeft -= 50;
    }
}

