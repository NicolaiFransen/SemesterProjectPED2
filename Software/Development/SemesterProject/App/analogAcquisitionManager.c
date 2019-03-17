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
    AnalogSignal voltageMeas24;
    AnalogSignal voltageMeas36;
    AnalogSignal thermalMeas1;
    AnalogSignal thermalMeas2;
    AnalogSignal sliderPotLeft;
    AnalogSignal sliderPotRight;
    AnalogSignal rotaryPot1;
    AnalogSignal rotaryPot2;
    AnalogSignal rotaryPot3;
    AnalogSignal connectorPot1;
    AnalogSignal connectorPot2;
} AnalogSignalList;

/*
 * Calls all relevant methods to configure the analog signals and ADCs
 */
void initADC(void)
{
    InitAdc();
    AdcOffsetSelfCal();

    configureAnalogSignals();
    configureADCs();

    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
    IER |= M_INT1;                     // Enable CPU Interrupt 1

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
 * All the analog signals are created.
 * To see link to specific ADC channel se configureADCs()
 * and the defines in analogAcquisitionManager.h
 */
void configureAnalogSignals(void)
{
    // Definition of filter parameters
    char filterType = 'L';
    int filterOrder = 1, filterFreq = 580;

    // Definition of thresholds
    int currentThreshold[2] = {300, 3000};
    int voltageThreshold[2] = {300, 3000};
    int thermalThreshold[2] = {300, 3000};
    int sliderPotThreshold[2] = {300, 3000};
    int rotaryPotThreshold[2] = {300, 3000};
    int connectorPotThreshold[2] = {300, 3000};

    // Create signal for Current A measurement.
    Uint16 currentMeasAChannel = IA;
    Signal_Constructor(&AnalogSignalList.currentMeasA, filterType, filterOrder,
                       filterFreq, currentMeasAChannel, currentThreshold);


    // Create signal for Current B measurement.
    Uint16 currentMeasBChannel = IB;
    Signal_Constructor(&AnalogSignalList.currentMeasB, filterType, filterOrder,
                       filterFreq, currentMeasBChannel, currentThreshold);


    // Create signal for Current C measurement.
    Uint16 currentMeasCChannel = IC;
    Signal_Constructor(&AnalogSignalList.currentMeasC, filterType, filterOrder,
                       filterFreq, currentMeasCChannel, currentThreshold);


    // Create signal for 24V measurement
    Uint16 voltageMeas24Channel = AD24;
    Signal_Constructor(&AnalogSignalList.voltageMeas24, filterType, filterOrder,
                       filterFreq, voltageMeas24Channel, voltageThreshold);


    // Create signal for 36V measurement
    Uint16 voltageMeas36Channel = AD36;
    Signal_Constructor(&AnalogSignalList.voltageMeas36, filterType, filterOrder,
                       filterFreq, voltageMeas36Channel, voltageThreshold);


    // Create signal for Thermal measurement 1
    Uint16 thermalMeas1Channel = J1;
    Signal_Constructor(&AnalogSignalList.thermalMeas1, filterType, filterOrder,
                       filterFreq, thermalMeas1Channel, thermalThreshold);


    // Create signal for Thermal measurement 2
    Uint16 thermalMeas2Channel = J2;
    Signal_Constructor(&AnalogSignalList.thermalMeas2, filterType, filterOrder,
                       filterFreq, thermalMeas2Channel, thermalThreshold);


    // Create signal for Left slider Potentiometer
    Uint16 leftSliderPotChannel = P2;
    Signal_Constructor(&AnalogSignalList.sliderPotLeft, filterType, filterOrder,
                       filterFreq, leftSliderPotChannel, sliderPotThreshold);


    // Create signal for Right slider potentiometer
    Uint16 rightSliderPotChannel = P1;
    Signal_Constructor(&AnalogSignalList.sliderPotRight, filterType, filterOrder,
                       filterFreq, rightSliderPotChannel, sliderPotThreshold);


    // Create signal for extra rotary potentiometer 1
    Uint16 rotaryPot1Channel = P3;
    Signal_Constructor(&AnalogSignalList.rotaryPot1, filterType, filterOrder,
                       filterFreq, rotaryPot1Channel, rotaryPotThreshold);


    // Create signal for extra rotary potentiometer 2
    Uint16 rotaryPot2Channel = P4;
    Signal_Constructor(&AnalogSignalList.rotaryPot2, filterType, filterOrder,
                       filterFreq, rotaryPot2Channel, rotaryPotThreshold);


    // Create signal for extra rotary potentiometer 3
    Uint16 rotaryPot3Channel = P5;
    Signal_Constructor(&AnalogSignalList.rotaryPot3, filterType, filterOrder,
                       filterFreq, rotaryPot3Channel, rotaryPotThreshold);


    // Create signal for connector potentiometer 1
    Uint16 connectorPot1Channel = J3;
    Signal_Constructor(&AnalogSignalList.connectorPot1, filterType, filterOrder,
                       filterFreq, connectorPot1Channel, connectorPotThreshold);


    // Create signal for connector potentiometer 2
    Uint16 connectorPot2Channel = J4;
    Signal_Constructor(&AnalogSignalList.connectorPot2, filterType, filterOrder,
                       filterFreq, connectorPot2Channel, connectorPotThreshold);
}


/*
 * Link analog signals to ADC channel by setting Channel, Trigger option and Acquisition period.
 * This also sets some initial registers for general setup of ADC.
 */
void configureADCs(void)
{
    EALLOW;
    // Enable non-overlap mode
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP   = 1;

    // ADCINT1 trips after AdcResults latch
    AdcRegs.ADCCTL1.bit.INTPULSEPOS     = 1;
    AdcRegs.INTSEL1N2.bit.INT1E         = 1;
    AdcRegs.INTSEL1N2.bit.INT1CONT      = 0;

    // setup EOC1 to trigger ADCINT1 to fire
    AdcRegs.INTSEL1N2.bit.INT1SEL       = 1;

    // Setting all ADCs to sequential sampling
    //AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0  = 0;
    AdcRegs.ADCSAMPLEMODE.all           = 0;


    // Configure ADC for phase A current measurement
    AdcRegs.ADCSOC3CTL.bit.CHSEL        = AnalogSignalList.currentMeasA.adcChannel;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL      = TRIGGER;
    AdcRegs.ADCSOC3CTL.bit.ACQPS        = SAMPLING_RATE;


    // Configure ADC for phase B current measurement
    AdcRegs.ADCSOC13CTL.bit.CHSEL       = AnalogSignalList.currentMeasB.adcChannel;
    AdcRegs.ADCSOC13CTL.bit.TRIGSEL     = TRIGGER;
    AdcRegs.ADCSOC13CTL.bit.ACQPS       = SAMPLING_RATE;

    // Configure ADC for phase C current measurement
    AdcRegs.ADCSOC5CTL.bit.CHSEL        = AnalogSignalList.currentMeasC.adcChannel;
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL      = TRIGGER;
    AdcRegs.ADCSOC5CTL.bit.ACQPS        = SAMPLING_RATE;

    // Configure ADC for 24V measurement
    AdcRegs.ADCSOC14CTL.bit.CHSEL       = AnalogSignalList.voltageMeas24.adcChannel;
    AdcRegs.ADCSOC14CTL.bit.TRIGSEL     = TRIGGER;
    AdcRegs.ADCSOC14CTL.bit.ACQPS       = SAMPLING_RATE;

    // Configure ADC for 36V measurement
    AdcRegs.ADCSOC12CTL.bit.CHSEL       = AnalogSignalList.voltageMeas36.adcChannel;
    AdcRegs.ADCSOC12CTL.bit.TRIGSEL     = TRIGGER;
    AdcRegs.ADCSOC12CTL.bit.ACQPS       = SAMPLING_RATE;

    // Configure ADC for Thermal measurement 1
    AdcRegs.ADCSOC6CTL.bit.CHSEL        = AnalogSignalList.thermalMeas1.adcChannel;
    AdcRegs.ADCSOC6CTL.bit.TRIGSEL      = TRIGGER;
    AdcRegs.ADCSOC6CTL.bit.ACQPS        = SAMPLING_RATE;

    // Configure ADC for thermal measurement 2
    AdcRegs.ADCSOC7CTL.bit.CHSEL        = AnalogSignalList.thermalMeas2.adcChannel;
    AdcRegs.ADCSOC7CTL.bit.TRIGSEL      = TRIGGER;
    AdcRegs.ADCSOC7CTL.bit.ACQPS        = SAMPLING_RATE;

    // Configure ADC for Left slider potentiometer
    AdcRegs.ADCSOC1CTL.bit.CHSEL        = AnalogSignalList.sliderPotLeft.adcChannel;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL      = TRIGGER;
    AdcRegs.ADCSOC1CTL.bit.ACQPS        = SAMPLING_RATE;

    // Configure ADC for Right slider potentiometer
    AdcRegs.ADCSOC15CTL.bit.CHSEL       = AnalogSignalList.sliderPotRight.adcChannel;
    AdcRegs.ADCSOC15CTL.bit.TRIGSEL     = TRIGGER;
    AdcRegs.ADCSOC15CTL.bit.ACQPS       = SAMPLING_RATE;

    // Configure ADC for extra rotary potentiometer 1
    AdcRegs.ADCSOC10CTL.bit.CHSEL       = AnalogSignalList.rotaryPot1.adcChannel;
    AdcRegs.ADCSOC10CTL.bit.TRIGSEL     = TRIGGER;
    AdcRegs.ADCSOC10CTL.bit.ACQPS       = SAMPLING_RATE;

    // Configure ADC for extra rotary potentiometer 2
    AdcRegs.ADCSOC0CTL.bit.CHSEL        = AnalogSignalList.rotaryPot2.adcChannel;
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL      = TRIGGER;
    AdcRegs.ADCSOC0CTL.bit.ACQPS        = SAMPLING_RATE;

    // Configure ADC for extra rotary potentiometer 3
    AdcRegs.ADCSOC8CTL.bit.CHSEL        = AnalogSignalList.rotaryPot3.adcChannel;
    AdcRegs.ADCSOC8CTL.bit.TRIGSEL      = TRIGGER;
    AdcRegs.ADCSOC8CTL.bit.ACQPS        = SAMPLING_RATE;

    // Configure ADC for connector potentiometer 1
    AdcRegs.ADCSOC9CTL.bit.CHSEL        = AnalogSignalList.connectorPot1.adcChannel;
    AdcRegs.ADCSOC9CTL.bit.TRIGSEL      = TRIGGER;
    AdcRegs.ADCSOC9CTL.bit.ACQPS        = SAMPLING_RATE;

    // Configure ADC for connector potentiometer 2
    AdcRegs.ADCSOC2CTL.bit.CHSEL        = AnalogSignalList.connectorPot2.adcChannel;
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL      = TRIGGER;
    AdcRegs.ADCSOC2CTL.bit.ACQPS        = SAMPLING_RATE;
    EDIS;
}

void readAnalogSignals(void)
{
    AnalogSignal *structPointer;
    AnalogSignal *initialMemoryPosition = &AnalogSignalList.currentMeasA;
    AnalogSignal *finalMemoryPosition = initialMemoryPosition + sizeof(AnalogSignalList)/sizeof(AnalogSignal);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
        readADCValue(structPointer);
}

void calculateFilteredValue(void)
{
    AnalogSignal *structPointer;
    AnalogSignal *initialMemoryPosition = &AnalogSignalList.currentMeasA;
    AnalogSignal *finalMemoryPosition = initialMemoryPosition + sizeof(AnalogSignalList)/sizeof(AnalogSignal);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
        filterADCValue(structPointer);
}

//
// End of File
//

