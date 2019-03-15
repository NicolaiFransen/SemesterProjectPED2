/*
 * scheduler.c
 *
 *  Created on: Mar 12, 2019
 *      Author: Nicolas
 *
 *      Scheduler implementation. This module will call every task when necessary.
 *      The tasks will have two possible states:
 *          -READY: the task is ready to run and waiting for the scheduler to call it
 *          -INACTIVE: the task has run and has been set to inactive. At some
 *          point another part of the code might change its state to ready again, for example a timer.
 *      The main object of the scheduler is the taskList, which is an array of TaskCOntrolBlock(TCB)
 *      including all the tasks that the system runs. In further development, different priorities
 *      or more advanced functions might be added.
 *      The scheduler will loop around taskList and whenever a READY task is found, that function
 *      will be called. Otherwise it will loop infinitely.
 */
#include "Include/scheduler.h"

/*
 * Quasi-global variable definition
 */

taskControlBlock taskList[maxNumberTasks];

void taskListInitialization(void)
{
    Uint16 taskListIndex = 0;

    taskList[taskListIndex].functionPointer = task20ms;
    taskList[taskListIndex].taskState = READY;
    taskList[taskListIndex].cyclicity = 20000;      // Time in us
    taskList[taskListIndex].timeLeft = 20000;       // Initialize to cyclicity
    taskListIndex++;

    taskList[taskListIndex].functionPointer = task50us;
    taskList[taskListIndex].taskState = INACTIVE;
    taskList[taskListIndex].cyclicity = 50;
    taskList[taskListIndex].timeLeft = 50;
    taskListIndex++;

    taskList[taskListIndex].functionPointer = NULL; // End of list
}

void scheduleTasks(void)
{
    Uint16 taskListIndex = 0;
    for(;;)
    {
        for (taskListIndex = 0; taskListIndex < maxNumberTasks; taskListIndex++)
        {
            if (endOfTaskListIsReached(taskListIndex))    break;

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
// cpu_timer0_isr - The time was measured to be 2.3 us
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
    Uint16 taskListIndex = 0;
    for (taskListIndex = 0; taskListIndex < maxNumberTasks; taskListIndex++)
    {
        if (endOfTaskListIsReached(taskListIndex))    break;

        if (taskList[taskListIndex].timeLeft <= timerPeriodUs)
        {
            taskList[taskListIndex].taskState = READY;
            taskList[taskListIndex].timeLeft = taskList[taskListIndex].cyclicity;
        }
        else    taskList[taskListIndex].timeLeft -= timerPeriodUs;
    }
}

int endOfTaskListIsReached(int taskListIndex)
{
    return taskList[taskListIndex].functionPointer == NULL;
}
