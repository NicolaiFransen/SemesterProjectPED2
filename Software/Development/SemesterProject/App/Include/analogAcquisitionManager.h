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
#include "controlTask.h"



//
// ADC Channel definitions
//
#define P4              0       // ADCINA0      Extra rotary potentiometer 2
#define P2              1       // ADCINA1      Brake reference (Left slider)
#define J4              2       // ADCINA2      Brake reference (External connector)
#define IA              3       // ADCINA3      Current phase A
// #define              4       // ADCINA4   -- FREE PIN
#define IC              5       // ADCINA5      Current phase C
#define J1              6       // ADCINA6      Thermometer 1
#define J2              7       // ADCINA7      Thermometer 2
#define P5              8       // ADCINB0      Extra rotary potentiometer 3
#define J3              9       // ADCINB1      Torque reference (External connector)
#define P3              10      // ADCINB2      Extra rotary potentiometer 1
// #define              11      // ADCINB3   -- FREE PIN
#define AD36            12      // ADCINB4      DC-link voltage
#define IB              13      // ADCINB5      Current phase B
#define AD24            14      // ADCINB6      Control supply voltage
#define P1              15      // ADCINB7      Torque reference (Right slider)

#define TRIGGER         5       // TRIGGER SELECT
#define SAMPLING_RATE   6       // ACQPS SELECT

//
// Function prototyping
//

/*
 * Interrupts for updating measurements
 */
__interrupt void adc_isr(void);

/*
 * Initialization functions for setup
 */
void initAnalogSignals(void);
void createAnalogSignals(void);
void configureADCRegisters(void);

/*
 * Read and filter functions to update measurements
 */
void readHighPrioritySignals(void);
void readLowPrioritySignals(void);
void readAnalogSignals(void *signal, int signalSize);
void calculateFilteredValue(void *signal, int signalSize);

/*
 * function to check for faulty reading
 */
Uint16 getAnalogErrorStatus(void);

/*
 * Interface functions to get measurements
 */
void getCurrentMeasurements(float *array);
float getDCLinkMeasurement(void);
float getControlsupplyMeasurement(void);
float getTorqueReferenceSliderMeasurement(void);
float getBrakeReferenceSliderMeasurent(void);
float getTorqueReferencePedalMeasurement(void);
float getBrakeReferencePedalMeasurement(void);
float getThermometer1Measurement(void);
float getThermometer2Measurement(void);
float getRotaryPot1Measurement(void);
float getRotaryPot2Measurement(void);
float getRotaryPot3Measurement(void);

float getMaxReferenceADC(void);


#endif /* APP_INCLUDE_ANALOGACQUISITIONMANAGER_H_ */
