/*
 * queueObject.h
 *
 *  Created on: Apr 12, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_QUEUEOBJECT_H_
#define APP_INCLUDE_QUEUEOBJECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "DSP28x_Project.h"



#define getName(var)  #var

//structure to represent a queue
struct Queue
{
    int front, rear, size;
    unsigned capacity;
    char* array;
};


struct Queue* createQueue(unsigned capacity);
int isFull(struct Queue* queue);
int isEmpty(struct Queue* queue);
void enqueue(struct Queue* queue, char item);
char dequeue(struct Queue* queue);
char front(struct Queue* queue);
char rear(struct Queue* queue);
void addIntToQueue(char *variableName, int value);
char* intToAscii(int i, char b[]);

/*
 * External interface
 */
void constructUARTBuffer(void);
void UARTIntPrint(char *variableName, int value);
void UARTStringPrint(char *stringToPrint);
char getNextBufferValue(void);
int isUARTBufferEmpty(void);

#endif /* APP_INCLUDE_QUEUEOBJECT_H_ */
