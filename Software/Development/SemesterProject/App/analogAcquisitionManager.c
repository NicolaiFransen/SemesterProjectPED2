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
static struct
{
    AnalogSignal currentMeasA;
    AnalogSignal currentMeasB;
    AnalogSignal currentMeasC;
//    AnalogSignal voltageMeas24;
//    AnalogSignal voltageMeas36;
//    AnalogSignal thermalMeas1;
//    AnalogSignal thermalMeas2;
//    AnalogSignal sliderPotLeft;
//    AnalogSignal sliderPotRight;
//    AnalogSignal rottaryPot1;
//    AnalogSignal rottaryPot2;
//    AnalogSignal rottaryPot3;
//    AnalogSignal connectorPot1;
//    AnalogSignal connectorPot2;
} AnalogSignalList;
// Initialize all Analog signals


void initADC(void)
{
    InitAdc();
    AdcOffsetSelfCal();

    configureAnalogSignals();

    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
    IER |= M_INT1;                     // Enable CPU Interrupt 1

    EALLOW;
    // Enable non-overlap mode
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;

    // ADCINT1 trips after AdcResults latch
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcRegs.INTSEL1N2.bit.INT1E = 1;
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0;

    // setup EOC1 to trigger ADCINT1 to fire
    AdcRegs.INTSEL1N2.bit.INT1SEL = 1;

    // Setting all ADCs to sequential sampling
    AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0 = 0;

    EDIS;

    //
    // Assumes ePWM1 clock is already enabled in InitSysCtrl();
    //
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;        // Enable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = 4;        // Select SOC from CMPA on upcount
    EPwm1Regs.ETPS.bit.SOCAPRD  = 1;        // Generate pulse on 1st event
    EPwm1Regs.CMPA.half.CMPA    = 0x0080;   // Set compare A value
    EPwm1Regs.TBPRD             = 0xFFFF;   // Set period for ePWM1
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;        // count up and start
}

/*
 * All the analog signals are created and linked to the ADC channels here.
 */
void configureAnalogSignals(void)
{
    char filterType = 'L';
    int filterOrder = 1, filterFreq = 580;

    // Configure of Channel ADCINA3. Current A measurement.
    Uint16 currentMeasAChannel = IA;
    int currentThreshold[2] = {300, 3000};
    Signal_Constructor(&AnalogSignalList.currentMeasA, filterType, filterOrder,
                       filterFreq, currentMeasAChannel, currentThreshold);

    AdcRegs.ADCSOC3CTL.bit.CHSEL = AnalogSignalList.currentMeasA.adcChannel;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC3CTL.bit.ACQPS = 26;

    // Configure of Channel ADCINB5. Current B measurement.
    Uint16 currentMeasBChannel = IB;
    Signal_Constructor(&AnalogSignalList.currentMeasB, filterType, filterOrder,
                       filterFreq, currentMeasBChannel, currentThreshold);

    AdcRegs.ADCSOC13CTL.bit.CHSEL = AnalogSignalList.currentMeasB.adcChannel;
    AdcRegs.ADCSOC13CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC13CTL.bit.ACQPS = 26;

    // Configure of Channel ADCINA5. Current C measurement.
    Uint16 currentMeasCChannel = IC;
    Signal_Constructor(&AnalogSignalList.currentMeasC, filterType, filterOrder,
                       filterFreq, currentMeasCChannel, currentThreshold);

    AdcRegs.ADCSOC5CTL.bit.CHSEL = AnalogSignalList.currentMeasC.adcChannel;
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC5CTL.bit.ACQPS = 26;
}

void readAnalogSignals(void)
{
    AnalogSignal *structPointer;
    AnalogSignal *initialMemoryPosition = &AnalogSignalList.currentMeasA;
    AnalogSignal *finalMemoryPosition = initialMemoryPosition + sizeof(AnalogSignalList);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
        readADCValue(structPointer);

    //    AnalogSignalList.currentMeasA.lastObtainedValue = readADCValue(&AnalogSignalList.currentMeasA);
//    AnalogSignalList.currentMeasB.lastObtainedValue = readADCValue(&AnalogSignalList.currentMeasB);
//    AnalogSignalList.currentMeasC.lastObtainedValue = readADCValue(&AnalogSignalList.currentMeasC);
}

void calculateFilteredValue(void)
{
    AnalogSignal *structPointer;
    AnalogSignal *initialMemoryPosition = &AnalogSignalList.currentMeasA;
    AnalogSignal *finalMemoryPosition = initialMemoryPosition + sizeof(AnalogSignalList);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
        filterADCValue(structPointer);
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

