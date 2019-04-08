/*
 * scheduler.h
 *
 *  Created on: Mar 13, 2019
 *      Author: Nicolas
 */

#ifndef SYSTEM_INCLUDE_SCHEDULER_H_
#define SYSTEM_INCLUDE_SCHEDULER_H_

#include "systemManager.h"
#include "communicationManager.h"
#include "openLoopControlManager.h"
#include "controlTask.h"
#include <stddef.h>
#include "pushButtonManager.h"


#define TIMER_PERIOD_US       50

typedef enum
{
    READY,
    INACTIVE,
}taskState;

typedef struct TCBstruct
{
    void (*functionPointer)();
    taskState taskState;
    Uint16 cyclicity;
    Uint16 timeLeft;
    unsigned int sleepTime;
    char priority;
}taskControlBlock;

/*
 * Function prototyping
 */
void taskListInitialization(void);
void scheduleTasks(void);
void runTask(void (*functionPTR)());

void task50us(void);
void task100us(void);
void task10ms(void);
void task20ms(void);
void task200ms(void);


void updateTasksState(void);
int endOfTaskListIsReached(int taskListIndex);
int taskMustBeScheduled(int taskListIndex);
void scheduleTask(int taskListIndex);
void restartTaskCountdown(int taskListIndex);
void decreaseCountdown(int taskListIndex);
int taskIsReady(int taskListIndex);
void deactivateTask(int taskListIndex);



#endif /* SYSTEM_INCLUDE_SCHEDULER_H_ */
