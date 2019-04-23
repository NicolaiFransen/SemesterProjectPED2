/*
 * systemInit.h
 *
 *  Created on: Mar 7, 2019
 *      Author: Nicolas
 */

#ifndef SYSTEM_INCLUDE_SYSTEMINIT_H_
#define SYSTEM_INCLUDE_SYSTEMINIT_H_

//
//Includes
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "../../App/Include/dutyCycle.h"
#include "../../App/Include/openLoopControlManager.h"
#include "string.h"
#include "digitalInputManager.h"
#include "errorManager.h"
#include "pushButtonManager.h"
#include "digitalOutputManager.h"
#include "analogAcquisitionManager.h"
#include "communicationManager.h"
#include "UARTInterface.h"
#include "../../App/Include/encoderManager.h"
#include "SVModulator.h"



//
// Function Prototypes statements for functions found within this file.
//
void systemInit(void);
int startupSequenceFinished(void);
__interrupt void cpu_timer0_isr(void);
void configureGPIO(void);
void configurePWM(void);

#endif /* SYSTEM_INCLUDE_SYSTEMINIT_H_ */
