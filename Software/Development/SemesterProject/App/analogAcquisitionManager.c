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
#include "analogSignal.h"



//
// Quasi-global variables definition
//
// Initialize all Analog signals
static struct
{
    AnalogSignal sig1;
    AnalogSignal sig2;
} AnalogSignlaList;

void initADC(void)
{
    InitAdc();

    // Setting all ADCs to sequential sampling
    AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0 = 0;
    AdcRegs.ADCSAMPLEMODE.bit.SIMULEN2 = 0;
    AdcRegs.ADCSAMPLEMODE.bit.SIMULEN4 = 0;
    AdcRegs.ADCSAMPLEMODE.bit.SIMULEN6 = 0;
    AdcRegs.ADCSAMPLEMODE.bit.SIMULEN8 = 0;
    AdcRegs.ADCSAMPLEMODE.bit.SIMULEN10 = 0;
    AdcRegs.ADCSAMPLEMODE.bit.SIMULEN12 = 0;
    AdcRegs.ADCSAMPLEMODE.bit.SIMULEN14 = 0;

    AdcRegs.ADCSOC0CTL.bit.CHSEL = AnalogSignlaList.sig1.adcChannel;
    AdcRegs.ADCSOC1CTL.bit.CHSEL = AnalogSignlaList.sig2.adcChannel;
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
}

*/
//
// End of File
//

