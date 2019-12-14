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
static enum taskListTag
{
    task1msItem,
    task5msItem,
    task20msItem,
    task200msItem,
    task1sItem,
    task10msItem,
    numberOfTasks
}taskListItems;

taskControlBlock taskList[numberOfTasks + 1];

static Uint32 sysClock = 0;

void taskListInitialization(void)
{
    taskList[task1msItem].functionPointer = task1ms;
    taskList[task1msItem].taskState = INACTIVE;
    taskList[task1msItem].cyclicity = 1000;
    taskList[task1msItem].timeLeft = 1000;

    taskList[task5msItem].functionPointer = task5ms;
    taskList[task5msItem].taskState = INACTIVE;
    taskList[task5msItem].cyclicity = 5000;
    taskList[task5msItem].timeLeft = 5000;

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
void task1ms(void)
{
    //readLowPrioritySignals();
    //performLowPriorityErrorMonitoring();
    //handleReferences();
}

void task5ms(void)
{
}

void task10ms(void)
{
    printCurrentsUART();
    ServiceDog();
}

void task20ms(void)
{
    manageSystem();
    readDigitalInputs();
    handlePushbuttons();
//    handleReferences(); moved to high priority

}

void task200ms(void)
{
    manageCommunications();
    handleSystemClock();
}

void task1s(void)
{
    restartPushbuttonsState();
    //calculateTemperature();
    //printUART();

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
    if (sysClock >= UINT_MAX)    sysClock = 0;

//    UARTIntPrint("TS ", (int)sysClock);
}

Uint32 getSystemClock(void)
{
    return sysClock;
}

void printUART(void)
{
//    Print stuff with UART here�!
    //UARTIntPrint("Vc ", (int)getControlsupplyMeasurement() * 100);
//    UARTIntPrint("DC ", (int)(getDCLinkMeasurement() * 100));
    //    UARTIntPrint("T ", (int)getThermometer1Measurement());
//        UARTIntPrint("vs ", (int)(getTorqueReferenceSliderMeasurement()*10));
//    UARTIntPrint("RPM ", (int)readRotorRPM());
//    UARTIntPrint("es ", (int)readRotorElecSpeedRadS());

//    UARTIntPrint("K ", (int)(TORQUE_TO_Q_CURRENT*10));

//    UARTIntPrint("Pos ", (int)(readRotorFluxAngleRad() * RAD_TO_DEG));
//    UARTIntPrint("Te ", (int)getTorqueReference());
//    UARTIntPrint("Iq ", (int)getIqReference(getMovementReference()));
//    UARTIntPrint("Id ", (int)getIdReference());
//    UARTIntPrint("R ", (int)(readRotorElecSpeedRadS() * RAD_TO_DEG));
}

void printCurrentsUART(void)
{
    SciaRegs.SCIFFTX.bit.TXFFINTCLR = 1;

//    float currentsToPrint[3];
//    dqObject dqCurrents;
//    getCurrentMeasurements(&currentsToPrint[0]);
//    float theta = readRotorFluxAngleRad();
//    dqCurrents = abc2dq(&currentsToPrint[0], theta);
////
    //UARTIntPrint("Id ", (int)(readIdReference() * 1000));
//    UARTIntPrint("Iq ", (int)dqCurrents.qComponent);
//    UARTIntPrint("Id ", (int)dqCurrents.dComponent);
//    UARTIntPrint("a ", (int)currentsToPrint[0]);
//    UARTIntPrint("b ", (int)currentsToPrint[1]);
//    UARTIntPrint("c ", (int)currentsToPrint[2]);
//    UARTIntPrint("S ", (int)(readRotorFluxAngleRad() * RAD_TO_DEG));

}
