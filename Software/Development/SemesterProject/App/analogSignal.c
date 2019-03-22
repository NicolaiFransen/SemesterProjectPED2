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
#include "AnalogSignal.h"

/*
 * The analog signal constructor initialize all defined variables to the selected analog signal struct.
 * Furthermore it calls the method filterParameters() to calculate the necessary parameters for the filter.
 */
void Signal_Constructor(AnalogSignal *analogSignal, char filterType, int filterOrder,
                       int cutoffFreq, Uint16 adcChannel, float threshold[2])
{
    analogSignal->filterType = filterType;
    analogSignal->filterOrder = filterOrder;
    analogSignal->cutoffFreq = cutoffFreq;

    analogSignal->adcChannel = adcChannel;

    analogSignal->threshold[0] = threshold[0];
    analogSignal->threshold[1] = threshold[1];

    analogSignal->previousValue = 0;
    analogSignal->filteredValue = 0;
    analogSignal->maxValue = MAX_VALUE_REFERENCE;

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
    float parameterA, parameterB, tau;

    tau = 1/(2*PI*cutoffFreq);

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

    analogSignal->ADCValue = *ADCResultPosition;
}

void filterADCValue(AnalogSignal *analogSignal)
{
    float ADCVoltage = analogSignal->ADCValue / (4095.0) * 3.3;

    // Applying the filter (y_n = x_n*a_0 + y_n-1*b_1)
    float ADCReadingFiltered = ADCVoltage*analogSignal->filterParamA + analogSignal->previousValue*analogSignal->filterParamB;
    analogSignal->previousValue = analogSignal->filteredValue;
    analogSignal->filteredValue = ADCReadingFiltered;
}





