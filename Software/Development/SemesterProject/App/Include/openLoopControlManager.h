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
#include "analogAcquisitionManager.h"
#include "referenceHandler.h"
#include "Constants.h"


//
//Defines
//
#define SINE_LUT_LENGTH  1002 //So it's divisible by 3 and phases are accurately shifted.


//
// Function prototyping
//
void setConstantDutyFromReference(void);
void openLoopVFControl(void);


#endif /* APP_OPENLOOPCONTROLMANAGER_H_ */
