//###########################################################################
//FILE: analogAcquisitionManager.c
//
//Project: Electric Go-kart
//
//Author: Nicolai, 12/3/19
//
//Notes:    Analog signal manager. This will loop through the analog signal array reading its value.
//          It uses analogSignal object as input.
//
//
//###########################################################################

//###########################################################################

//
// Includes
//
#include "analogAcquisitionManager.h"
#include "DSP28x_Project.h"


//
// Quasi-global variables definition
//
// Initialize all Analog signals
static struct
{
    AnalogSignal sig1;
    AnalogSignal sig2;
} AnalogSignalList;

void initADC(void)
{
    char type = 'L';
    int order = 1, filterFreq = 50;
    Uint16 sig1Channel = 0, sig2Channel = 1;
    int threshold[2] = {300, 3000};
    Signal_Constructor(&AnalogSignalList.sig1, type, order, filterFreq, sig1Channel, threshold);
    Signal_Constructor(&AnalogSignalList.sig2, type, order, filterFreq, sig2Channel, threshold);

    InitAdc();
    // AdcOffsetSelfCal();

    EALLOW;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    // Setting all ADCs to sequential sampling
    AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0 = 0;

    AdcRegs.ADCSOC0CTL.bit.CHSEL = AnalogSignalList.sig1.adcChannel;
    AdcRegs.ADCSOC1CTL.bit.CHSEL = AnalogSignalList.sig2.adcChannel;

    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 1;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 1;

    AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC1CTL.bit.ACQPS = 25;

    AdcRegs.INTSEL1N2.bit.INT1SEL = 1;
    AdcRegs.INTSEL1N2.bit.INT1E = 1;
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0;

    EDIS;



}

void readAnalogSignals(void)
{
    Uint16 valueSig1 = readADCValue(&AnalogSignalList.sig1);
    Uint16 valueSig2 = readADCValue(&AnalogSignalList.sig2);
}

/*
// initialization of all digital inputs {pin, state}
static struct
{
    DigitalInput switch_1;
    DigitalInput switch_2;

}DigitalInputList;

void initInputs(void)
{
    DigitalInput_Constructor(&DigitalInputList.switch_1, 4); // the second argument is the pin,
}

void readDigitalInputs(void)//
{
    DigitalInput_ReadState(&DigitalInputList.switch_1);
}*/


//
// End of File
//

