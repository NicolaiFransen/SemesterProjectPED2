/*
 * pushbutttonManager.c
 *
 *  Created on: Mar 27, 2019
 *      Author: Nicolas
 *      This module is an abstraction layer higher than digitalInputMgr.
 *      Its goal is to qualify whether a pushbutton is on or not.
 *      It is based on a FSM which will qualify a 'pressed' event
 *      whenever a pushbutton is pushed AND released. The pressed event
 *      will hold a '1' value until an external software component
 *      reads it. At that moment, the value will be reset to 0.
 *      This implies risks in case that two software components use the same
 *      button, but that will never be allowed.
 *
 */

#include "pushButtonManager.h"

static struct pushButtonListTag
{
    PushButton regenerativeBraking;
    PushButton torqueReference;
    PushButton cruiseControl;
    PushButton antiSlip;
}pushButtonList;

void initPushbuttons()
{
    PushButton *structPointer;
    PushButton *initialMemoryPosition = &pushButtonList.regenerativeBraking;
    PushButton *finalMemoryPosition = initialMemoryPosition + sizeof(pushButtonList)/sizeof(PushButton);

    pushButtonList.regenerativeBraking.functionPointer = isRegenBrakingPushbuttonEnabled;
    pushButtonList.antiSlip.functionPointer = isAntiSlipPushbuttonEnabled;
    pushButtonList.cruiseControl.functionPointer = isCruiseControlPushbuttonEnabled;
    pushButtonList.torqueReference.functionPointer = isTorqueReferencePushButtonEnabled;

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
    {
        structPointer->FSMState = waitingForRisingEdge; // First State of FSM
        structPointer->ButtonState = 0;
    }
}

void handlePushbuttons(void)
{
    PushButton *structPointer;
    PushButton *initialMemoryPosition = &pushButtonList.regenerativeBraking;
    PushButton *finalMemoryPosition = initialMemoryPosition + sizeof(pushButtonList)/sizeof(PushButton);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
    {
        pushEventQualificationFSM(structPointer);
    }
}

void pushEventQualificationFSM(PushButton *pushbutton)
{
    switch(pushbutton->FSMState)
    {
        case waitingForRisingEdge:
        {
            if (pinIsHigh(pushbutton))  pushbutton->FSMState = waitingForFallingEdge;
        }
        case waitingForFallingEdge:
        {
            if (pinIsLow(pushbutton))   pushbutton->FSMState = qualifyState;
        }
        case qualifyState:
        {
            pushbutton->ButtonState = 1;
            pushbutton->FSMState = waitingForRisingEdge;
        }
    }
}

int pinIsHigh(PushButton *pushbutton)
{
    return pushbutton->functionPointer();
}

int pinIsLow(PushButton *pushbutton)
{
    return !(pushbutton->functionPointer());
}

int regenerativeBrakingHasBeenPressed(void)
{
    int buttonStateValue = pushButtonList.regenerativeBraking.ButtonState;
    pushButtonList.regenerativeBraking.ButtonState = 0;
    return buttonStateValue;
}

int cruiseControlHasBeenPressed(void)
{
    int buttonStateValue = pushButtonList.cruiseControl.ButtonState;
    pushButtonList.cruiseControl.ButtonState = 0;
    return buttonStateValue;
}

int torqueReferenceHasBeenPressed(void)
{
    int buttonStateValue = pushButtonList.torqueReference.ButtonState;
    pushButtonList.torqueReference.ButtonState = 0;
    return buttonStateValue;
}

int antiSlipHasBeenPressed(void)
{
    int buttonStateValue = pushButtonList.antiSlip.ButtonState;
    pushButtonList.antiSlip.ButtonState = 0;
    return buttonStateValue;
}

