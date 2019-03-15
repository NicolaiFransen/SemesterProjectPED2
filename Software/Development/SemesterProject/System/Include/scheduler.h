/*
 * scheduler.h
 *
 *  Created on: Mar 13, 2019
 *      Author: Nicolas
 */

#ifndef SYSTEM_INCLUDE_SCHEDULER_H_
#define SYSTEM_INCLUDE_SCHEDULER_H_

#include "systemManager.h"
#include <stddef.h>

#define maxNumberTasks      10
#define largestCyclicity    20000
#define timerPeriodUs       50

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
void task20ms(void);
void updateTasksState(void);
int endOfTaskListIsReached(int taskListIndex);

#endif /* SYSTEM_INCLUDE_SCHEDULER_H_ */
