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
#define ANALOG_EXECUTION_FREQ 20000;

void Signal_Constructor(AnalogSignal *analogSignal, char filterType, int filterOrder,
                       int cutoffFreq, int adcChannel, int threshold[2])
{

    analogSignal->filterType = filterType;

    analogSignal->filterOrder = filterOrder;

    analogSignal->cutoffFreq = cutoffFreq;

    analogSignal->adcChannel = adcChannel;
    analogSignal->threshold[0] = threshold[0];
    analogSignal->threshold[1] = threshold[1];

    filterParameters(&analogSignal, filterType, filterOrder, cutoffFreq);
}

void filterParameters(AnalogSignal *analogSignal, char filterType, int filterOrder, int cutoffFreq)
{
    float parameterA, pi = 3.14;
    float parameterB, tau;

    tau = 1/(2*pi*cutoffFreq);
//    printf("Tau: %f \n", tau);

    parameterB = exp(-1/(20000*tau));
//    printf("Parameter B: %f \n", parameterB);
//    printf("Parameter : %f \n", 20000*tau);

    parameterA = 1 - parameterB;

    analogSignal->filterParamA = parameterA;
    analogSignal->filterParamB = parameterB;
}





