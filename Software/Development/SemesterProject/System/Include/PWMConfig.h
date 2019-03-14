/*
 * PWMConfig.h
 *
 *  Created on: 13 mar. 2019
 *      Author: Aitor Teran
 */

#ifndef SYSTEM_PWMCONFIG_H_
#define SYSTEM_PWMCONFIG_H_


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2806x_EPwm.h"    //EPWM register bits definitions


//
// Function declaration
//
void configurePWM(void);


/*
 * Parameters related to PWM constants are defined here.
 */
#define SW_FREQ      10000  //Switching frequency [10kHz].

//
//INTERNAL FREQUENCY is configured in InitSysCtrl(), located in F2806x_SysCtrl.c
//The internal clk INTOSC1 is used, with a maximum frequency of 10MHz.
//PLL are configured to increase the frequency by 9 (10MHz * 18 / 2).
//The values 18 and 2 are configured in F2806x_Examples.h (defines DSP28_PLLCR and DSP28_DIVSEL).
//
#define INTERNAL_FREQ   90000000    //Internal frequency of the device [90MHz]. Configured in InitSysCtrl().


#endif /* SYSTEM_PWMCONFIG_H_ */
