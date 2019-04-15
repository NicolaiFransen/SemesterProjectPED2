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
#include "errorManager.h"

/*
 * Quasi-global variable definition
 */
static enum taskListTag
{
    task50usItem,
    task100usItem,
    task10msItem,
    task20msItem,
    task200msItem,
    task1sItem,
    numberOfTasks
}taskListItems;

taskControlBlock taskList[numberOfTasks + 1];

static Uint32 sysClock = 0;

void taskListInitialization(void)
{
    taskList[task50usItem].functionPointer = task50us;
    taskList[task50usItem].taskState = INACTIVE;
    taskList[task50usItem].cyclicity = 50;
    taskList[task50usItem].timeLeft = 50;

    taskList[task100usItem].functionPointer = task100us;
    taskList[task100usItem].taskState = INACTIVE;
    taskList[task100usItem].cyclicity = 100;
    taskList[task100usItem].timeLeft = 100;

    taskList[task10msItem].functionPointer = task10ms;
    taskList[task10msItem].taskState = INACTIVE;
    taskList[task10msItem].cyclicity = 10000;
    taskList[task10msItem].timeLeft = 10000;

    taskList[task20msItem].functionPointer = task20ms;
    taskList[task20msItem].taskState = READY;
    taskList[task20msItem].cyclicity = 20000;      // Time in us
    taskList[task20msItem].timeLeft = 20000;       // Initialize to cyclicity

    taskList[task200msItem].functionPointer = task200ms;
    taskList[task200msItem].taskState = INACTIVE;
    taskList[task200msItem].cyclicity = 200000;
    taskList[task200msItem].timeLeft = 200000;

    taskList[task1sItem].functionPointer = task1s;
    taskList[task1sItem].taskState = INACTIVE;
    taskList[task1sItem].cyclicity = 1000000;
    taskList[task1sItem].timeLeft = 1000000;

    taskList[numberOfTasks].functionPointer = NULL; // End of list
}

void scheduleTasks(void)
{
    Uint16 taskListIndex = 0;
    for(;;)
    {
        for (taskListIndex = 0; endOfTaskListIsReached(taskListIndex); taskListIndex++)
        {
            if (taskIsReady(taskListIndex))
            {
                runTask(taskList[taskListIndex].functionPointer);
                deactivateTask(taskListIndex);
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
void task100us(void)
{//running at switching 10kHz (update with switching frequency);
}

void task50us(void)
{
    executeControl();
    monitorErrorSources();
}

void task10ms(void)
{
    ServiceDog();
}

void task20ms(void)
{
    manageSystem();
    readDigitalInputs();
    readLowPrioritySignals();
    handlePushbuttons();
    handleReferences();
}

void task200ms(void)
{
    manageCommunications();
    handleSystemClock();
}

void task1s(void)
{
    restartPushbuttonsState();
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
    for (taskListIndex = 0; endOfTaskListIsReached(taskListIndex); taskListIndex++)
    {
        if (taskMustBeScheduled(taskListIndex))
        {
            scheduleTask(taskListIndex);
            restartTaskCountdown(taskListIndex);
        }
        else    decreaseCountdown(taskListIndex);
    }
}

int endOfTaskListIsReached(int taskListIndex)
{
    return taskList[taskListIndex].functionPointer != NULL;
}

int taskMustBeScheduled(int taskListIndex)
{
    return taskList[taskListIndex].timeLeft <= TIMER_PERIOD_US;
}

void scheduleTask(int taskListIndex)
{
    taskList[taskListIndex].taskState = READY;
}

void restartTaskCountdown(int taskListIndex)
{
    taskList[taskListIndex].timeLeft = taskList[taskListIndex].cyclicity;
}

void decreaseCountdown(int taskListIndex)
{
    taskList[taskListIndex].timeLeft -= TIMER_PERIOD_US;
}

int taskIsReady(int taskListIndex)
{
    return taskList[taskListIndex].taskState == READY;
}

void deactivateTask(int taskListIndex)
{
    taskList[taskListIndex].taskState = INACTIVE;
}

void handleSystemClock(void)
{
    sysClock++;
    if (sysClock >= INT_MAX)    sysClock = 0;
    UARTIntPrint("TimeStamp ", (int)sysClock);
}

Uint32 getSystemClock(void)
{
    return sysClock;
}
