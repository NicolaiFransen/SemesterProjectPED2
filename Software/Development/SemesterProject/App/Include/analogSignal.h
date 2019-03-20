/*
 * signal.h
 *
 *  Created on: 6. mar. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_ANALOGSIGNAL_H_
#define APP_INCLUDE_ANALOGSIGNAL_H_


//
// Includes
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include "Constants.h"


//
// Object declaration
//

typedef struct AnalogSignalTag
{
    char filterType;                // Type of the filter HP of LP
    int filterOrder;                // Order of the filter
    int cutoffFreq;                 // Desired cut-off frequency of the filter
    float filterParamA;             // Filter parameter A, calculated from the filter specifications
    float filterParamB;             // Filter parameter B, calculated from the filter specifications
    float filteredValue;            // Filtered value corresponding to the measured voltage
    float previousValue;            // Filtered value corresponding to the previous measured voltage
    Uint16 ADCValue;                // Raw digital ADC reading
    Uint16 adcChannel;              // ADC channel for the signal
    int threshold[2];               // Maximum and minimum thresholds. Used for error handling.
} AnalogSignal;

//
// Method prototyping
//

void Signal_Constructor(AnalogSignal *analogSignal, char filterType, int filterOrder,
                       int cutoffFreq, Uint16 adcChannel, int threshold[2]);
void calculateFilterParameters(AnalogSignal *analogSignal, char filterType, int filterOrder, int cutoffFreq);
void setFilteredValue(AnalogSignal *analogSignal);
void readADCValue(AnalogSignal *analogSignal);
void filterADCValue(AnalogSignal *analogSignal);

#endif /* APP_INCLUDE_ANALOGSIGNAL_H_ */
