/*
 * signal.h
 *
 *  Created on: 6. mar. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_ANALOGSIGNAL_H_
#define APP_INCLUDE_ANALOGSIGNAL_H_


//
// Object declaration
//

typedef struct AnalogSignalTag
{
    char filterType;                // Type of the filter HP of LP
    int filterOrder;
    float filterParamA;
    float filterParamB;
    float filteredValue;
    float oldValue;
    int cutoffFreq;
    Uint16 lastObtainedValue;
    Uint16 adcChannel;
    int threshold[2];
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
