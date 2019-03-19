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
#include <math.h>


//
// Quasi-global variables definition
//
#define ANALOG_EXECUTION_FREQ 20000

/*
 * The analog signal constructor initialize all defined variables to the selected analog signal struct.
 * Furthermore it calls the method filterParameters() to calculate the necessary parameters for the filter.
 */
void Signal_Constructor(AnalogSignal *analogSignal, char filterType, int filterOrder,
                       int cutoffFreq, Uint16 adcChannel, int threshold[2])
{
    analogSignal->filterType = filterType;
    analogSignal->filterOrder = filterOrder;
    analogSignal->cutoffFreq = cutoffFreq;

    analogSignal->adcChannel = adcChannel;

    analogSignal->threshold[0] = threshold[0];
    analogSignal->threshold[1] = threshold[1];

    analogSignal->oldValue = 0;

    calculateFilterParameters(analogSignal, filterType, filterOrder, cutoffFreq);
}

/*
 * The filter parameters are calculated from the specified filter type, order and cut-off frequency.
 * The B parameter is calculated by using the execution frequency, so this should be confirmed with a clever person.
 *
 * The parameters A and B are calculated as in the previous project (Ask Nicolas for the reference)
 * For now its only able to calculated the parameters for a first order low-pass filter, if it is found
 * necessary to use a higher order filter this should be implemented.
 */
void calculateFilterParameters(AnalogSignal *analogSignal, char filterType, int filterOrder, int cutoffFreq)
{
    float parameterA, pi = 3.14;
    float parameterB, tau;

    tau = 1/(2*pi*cutoffFreq);

    parameterB = exp(-1/(ANALOG_EXECUTION_FREQ*tau));

    parameterA = 1 - parameterB;

    analogSignal->filterParamA = parameterA;
    analogSignal->filterParamB = parameterB;
}


/*
 * Reads the discrete value of the specified analog signal.
 * This is done by setting a pointer at the first ADC channel, and then move it to what ever channel is specified.
 */
void readADCValue(AnalogSignal *analogSignal)
{
    volatile Uint16 *ADCResultPosition = &AdcResult.ADCRESULT0 + analogSignal->adcChannel;

    analogSignal->lastObtainedValue = *ADCResultPosition;
}

void filterADCValue(AnalogSignal *analogSignal)
{
    float ADCReading = analogSignal->lastObtainedValue / (4095.0) * 3.3;

    // Applying the filter (y_n = x_n*a_0 + y_n-1*b_1)
    float ADCReadingFiltered = ADCReading*analogSignal->filterParamA + analogSignal->oldValue*analogSignal->filterParamB;
    analogSignal->oldValue = analogSignal->filteredValue;
    analogSignal->filteredValue = ADCReadingFiltered;
}





