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
void readDigitalInputs(void);
int isRegenBrakingPushbuttonEnabled(void);
int isTorqueReferencePushButtonEnabled(void);
int isOpenClosedLoopSelectionSwitchEnabled(void);
int isPowerSwitchEnabled(void);
int isCruiseControlPushbuttonEnabled(void);
int isAntiSlipPushbuttonEnabled(void);
void initDigitalInputs(void);

#endif /* APP_INCLUDE_DIGITALINPUTMANAGER_H_ */
