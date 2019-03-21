/*
 * openLoopControlManager.h
 *
 *  Created on: 21 mar. 2019
 *      Author: Aitor Teran
 */

#ifndef APP_OPENLOOPCONTROLMANAGER_H_
#define APP_OPENLOOPCONTROLMANAGER_H_

//
// Includes
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
//#include "analogSignal.h"
#include "dutyCycle.h"
#include "../../System/Include/PWMConfig.h"


//
//Defines
//
#define MAX_STATOR_FREQ 54 //Hz
#define PI  3.14159265
#define SINE_LUT_LENGTH  100
#define MA  1


//
// Function prototyping
//
void setConstantDutyFromPot(void);
void setFrequencyFromPot(void);


#endif /* APP_OPENLOOPCONTROLMANAGER_H_ */
