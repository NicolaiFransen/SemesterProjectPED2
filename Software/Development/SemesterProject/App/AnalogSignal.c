//###########################################################################
//FILE: signal.c
//
//Project: Electric Go-kart
//
//Author: Nicolai, 6/3/19
//
//Notes:    Signal. This will create the signals for each ADC.
//
//
//###########################################################################

//###########################################################################

//
// Includes
//

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "AnalogSignal.h"
#include "math.h"


//
// Quasi-global variables definition
//
#define ANALOG_EXECUTION_FREQ 20000

void Signal_Constructor(AnalogSignal *analogSignal, char filterType, int filterOrder,
                       int cutoffFreq, Uint16 adcChannel, int threshold[2])
{

    analogSignal->filterType = filterType;

    analogSignal->filterOrder = filterOrder;

    analogSignal->cutoffFreq = cutoffFreq;

    analogSignal->adcChannel = adcChannel;
    analogSignal->threshold[0] = threshold[0];
    analogSignal->threshold[1] = threshold[1];

    filterParameters(analogSignal, filterType, filterOrder, cutoffFreq);
}

void filterParameters(AnalogSignal *analogSignal, char filterType, int filterOrder, int cutoffFreq)
{
    float parameterA, pi = 3.14;
    float parameterB, tau;

    tau = 1/(2*pi*cutoffFreq);

    parameterB = exp(-1/(ANALOG_EXECUTION_FREQ*tau));

    parameterA = 1 - parameterB;

    analogSignal->filterParamA = parameterA;
    analogSignal->filterParamB = parameterB;
}

float readFilteredValue(AnalogSignal *analogSignal)
{
    Uint16 *initialADCMemoryPosition = &AdcResult.ADC_RESULT_REGS;
    Uint16 ADCvalue = initialADCMemoryPosition + analogSignal->adcChannel*sizeof(Uint16);


}





