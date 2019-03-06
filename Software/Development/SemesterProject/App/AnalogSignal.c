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

//
// Quasi-global variables definition
//


void Signal_Constructor(AnalogSignal *analogSignal, char filterType, int filterOrder,
                       int cutoffFreq, int adcChannel, int threshold[2])
{
    // Setting filter type to HP-filter if that is selected, otherwise setting it as LP.
    if (filterType == "HP")
        analogSignal->filterType = filterType;
    else
        analogSignal->filterType = "LP";

    // Setting the wanted filter order, with a maximum of maxFilterOrder
    int maxFilterOrder = 3;

    if (filterOrder >= maxFilterOrder)
        analogSignal->filterOrder = maxFilterOrder;
    else
        analogSignal->filterOrder = filterOrder;

    // Setting the wanted cut-off frequency of the filter
    // if its inside the maximum and minimum boundaries
    int maxCutoffFreq = 10000;
    int minCutoffFreq = 1;
    if (cutoffFreq >= maxCutoffFreq)
        analogSignal->cutoffFreq = maxCutoffFreq;
    else if (cutoffFreq <= minCutoffFreq)
        analogSignal->cutoffFreq = minCutoffFreq;
    else
        analogSignal->cutoffFreq = cutoffFreq;


    analogSignal->adcChannel = adcChannel;
    analogSignal->threshold[0] = threshold[0];
    analogSignal->threshold[1] = threshold[1];
}




