/*
 * analogAcquisitionManager.h
 *
 *  Created on: 12. mar. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_ANALOGACQUISITIONMANAGER_H_
#define APP_INCLUDE_ANALOGACQUISITIONMANAGER_H_

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "analogSignal.h"

//
// ADC Channel definitions
//
#define P4              0       // ADCINA0
#define P2              1       // ADCINA1
#define J4              2       // ADCINA2
#define IA              3       // ADCINA3
// #define              4       // ADCINA4   -- FREE PIN
#define IC              5       // ADCINA5
#define J1              6       // ADCINA6
#define J2              7       // ADCINA7
#define P5              8       // ADCINB0
#define J3              9       // ADCINB1
#define P3              10      // ADCINB2
// #define              11      // ADCINB3   -- FREE PIN
#define AD36            12      // ADCINB4
#define IB              13      // ADCINB5
#define AD24            14      // ADCINB6
#define P1              15      // ADCINB7

#define TRIGGER         2    // TRIGGER SELECT
#define SAMPLING_RATE   6       // ACQPS SELECT

//
// Function prototyping
//
__interrupt void adc_isr(void);

void readAnalogSignals(void);
void calculateFilteredValue(void);
void initAnalogSignals(void);
void configureAnalogSignals(void);
void configureADCs(void);



#endif /* APP_INCLUDE_ANALOGACQUISITIONMANAGER_H_ */
