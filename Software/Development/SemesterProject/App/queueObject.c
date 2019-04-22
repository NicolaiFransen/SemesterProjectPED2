/*
 * queueObject.c
 *
 *  Created on: Apr 12, 2019
 *      Author: Nicolas
 *
 *      This code provides a way for creating Queue data structures.
 *
 *      Obtained from geeksforgeeks.org.
 *
 */

#include "queueObject.h"

/*
 * Quasi-global variable definition
 */
static struct Queue* queue;

// function to create a queue of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;  // This is important, see the enqueue. 'rear' points to the last element, which accounting index '0', it's placed in n -1.
    queue->array = (char*) malloc(queue->capacity * sizeof(char));
    return queue;
}

// Queue is full when size becomes equal to the capacity
int isFull(struct Queue* queue)
{  return (queue->size == queue->capacity);  }

// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{  return (queue->size == 0); }

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, char item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)%queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Function to remove an item from queue.
// It changes front and size
char dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return CHAR_MIN;
    char item = queue->array[queue->front];
    queue->front = (queue->front + 1)%queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
char front(struct Queue* queue)
{
    if (isEmpty(queue))
        return CHAR_MIN;
    return queue->array[queue->front];
}

// Function to get rear of queue
char rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return CHAR_MIN;
    return queue->array[queue->rear];
}

/*
 * Integer to string conversion.
 *
 * As the input is an integer, the value ranges +-32768,
 * otherwise the value will be corrupted.
 */
char* intToAscii(int i, char b[])
{
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

/*
 * External interface
 */
void constructUARTBuffer(void)
{
    queue = createQueue(1000);
}

/*
 * variableName is a pointer to a string ended in \0. This is a MUST.
 * Use example:         UARTIntPrint("iref \0", 30211);
 * Signed int are used, then the maximum value is 32768.
 * Procedure:
 *  -Conversion from int to string              (intToAscii)
 *  -use string print function to add to buffer
 */
void UARTIntPrint(char *variableName, int value)
{
    char str[10];
    char *strASCII;
    strASCII = intToAscii(value, str);
    UARTStringPrint(variableName);
    UARTStringPrint(strASCII);
    UARTStringPrint(",\n\r");
}

void UARTStringPrint(char *stringToPrint)
{
    Uint32 stringIndex;
    for (stringIndex = 0; stringIndex < strlen(stringToPrint); stringIndex++)
        {
            enqueue(queue, stringToPrint[stringIndex]);
        }
    //Send signal to SCI to send the data
    SciaRegs.SCIFFTX.bit.TXFFINTCLR = 1;
}

char getNextBufferValue(void)
{
    return dequeue(queue);
}

int isUARTBufferEmpty(void)
{
    return isEmpty(queue);
}


