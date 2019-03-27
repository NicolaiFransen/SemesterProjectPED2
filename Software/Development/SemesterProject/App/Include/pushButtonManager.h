/*
 * pushButtonManager.h
 *
 *  Created on: Mar 27, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_PUSHBUTTONMANAGER_H_
#define APP_INCLUDE_PUSHBUTTONMANAGER_H_

#include "digitalInputManager.h"

typedef enum
{
    waitingForRisingEdge,
    waitingForFallingEdge,
    qualifyState
} buttonFSMState;

typedef struct PushButtonTag
{
    buttonFSMState FSMState;
    unsigned char ButtonState:1;
    int (*functionPointer)();
} PushButton;

void initPushbuttons();
void handlePushbuttons(void);
void pushEventQualificationFSM(PushButton *pushbutton);
int pinIsHigh(PushButton *pushbutton);
int pinIsLow(PushButton *pushbutton);
int regenerativeBrakingHasBeenPressed(void);
int cruiseControlHasBeenPressed(void);
int torqueReferenceHasBeenPressed(void);
int antiSlipHasBeenPressed(void);



#endif /* APP_INCLUDE_PUSHBUTTONMANAGER_H_ */
