/*
 * pushbutttonManager.c
 *
 *  Created on: Mar 27, 2019
 *      Author: Nicolas
 *      This module is an abstraction layer higher than digitalInputMgr.
 *      Its goal is to qualify whether a pushbutton has been pressed or not.
 *      It is based on a FSM which will qualify a 'pressed' event
 *      whenever a pushbutton is pushed and released. The pressed event
 *      will hold a '1' value until an external software component
 *      uses thhe interface to check it. At that moment, the value will be reset to 0.
 *      This implies risks in case that two software components use the same
 *      button, but that will never be allowed.
 *
 */

#include "pushButtonManager.h"

static struct pushButtonListTag
{
    PushButton referenceSource;
    PushButton referenceType;
    PushButton speedIncrease;
    PushButton speedDecrease;
}pushButtonList;

void initPushbuttons()
{
    PushButton *structPointer;
    PushButton *initialMemoryPosition = &pushButtonList.referenceSource;
    PushButton *finalMemoryPosition = initialMemoryPosition + sizeof(pushButtonList)/sizeof(PushButton);

    //Tracing the function pointers to DigitalInputManager Interfaces
    pushButtonList.referenceSource.functionPointer = isReferenceSourcePushbuttonEnabled;
    pushButtonList.referenceType.functionPointer = isReferenceTypePushbuttonEnabled;
    pushButtonList.speedDecrease.functionPointer = isSpeedDecreasePushbuttonEnabled;
    pushButtonList.speedIncrease.functionPointer = isSpeedIncreasePushbuttonEnabled;

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
    {
        structPointer->FSMState = waitingForRisingEdge; // First State of FSM
        structPointer->ButtonState = 0;
    }
}

/*
 * Pushbutton Manager. This function performs analysis of whether
 * a pushbutton has been pressed and provides an interface for
 * external use.
 */
void handlePushbuttons(void)
{
    PushButton *structPointer;
    PushButton *initialMemoryPosition = &pushButtonList.referenceSource;
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
        }break;
        case waitingForFallingEdge:
        {
            if (pinIsLow(pushbutton))   pushbutton->FSMState = qualifyState;
        }break;
        case qualifyState:
        {
            pushbutton->ButtonState = 1;
            pushbutton->FSMState = waitingForRisingEdge;
        }break;
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

int referenceSourceHasBeenPressed(void)
{
    int buttonStateValue = pushButtonList.referenceSource.ButtonState;
    pushButtonList.referenceSource.ButtonState = 0;
    return buttonStateValue;
}

int referenceTypeHasBeenPressed(void)
{
    int buttonStateValue = pushButtonList.referenceType.ButtonState;
    pushButtonList.referenceType.ButtonState = 0;
    return buttonStateValue;
}

int speedRefDecreaseHasBeenPressed(void)
{
    int buttonStateValue = pushButtonList.speedDecrease.ButtonState;
    pushButtonList.speedDecrease.ButtonState = 0;
    return buttonStateValue;
}

int speedRefIncreaseHasBeenPressed(void)
{
    int buttonStateValue = pushButtonList.speedIncrease.ButtonState;
    pushButtonList.speedIncrease.ButtonState = 0;
    return buttonStateValue;
}


