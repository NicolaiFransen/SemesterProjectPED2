/*
 * digitalInputManager.h
 *
 *  Created on: Mar 4, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_DIGITALINPUTMANAGER_H_
#define APP_INCLUDE_DIGITALINPUTMANAGER_H_

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Function prototyping
//
void initDigitalInputs(void);
void readDigitalInputs(void);

int isOpenClosedLoopSelectionSwitchEnabled(void);
int isPowerSwitchEnabled(void);

int isSpeedIncreasePushbuttonEnabled(void);
int isSpeedDecreasePushbuttonEnabled(void);
int isReferenceSourcePushbuttonEnabled(void);
int isReferenceTypePushbuttonEnabled(void);


#endif /* APP_INCLUDE_DIGITALINPUTMANAGER_H_ */
