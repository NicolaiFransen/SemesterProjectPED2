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


//
// Quasi-global variables definition
//

/*
 * Two different structs are created for the signals. One with a high priority (The currents),
 * and one with a low priority (The rest). The reason for this is to keep the execution time for
 * reading the currents as low as possible, such that we are able to read the values within the
 * limits of our switching frequency.
 */
static struct
{
    AnalogSignal currentMeasA;
    AnalogSignal currentMeasB;
    AnalogSignal currentMeasC;
} CurrentSignalList;

static struct
{
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
 * Reads and filters the values of signals in the high priority struct.
 * This function will be called by the adc_isr() every time the timer1 trigger.
 */
void readHighPrioritySignals(void)
{
    readAnalogSignals(&CurrentSignalList, sizeof(CurrentSignalList));
    calculateFilteredValue(&CurrentSignalList, sizeof(CurrentSignalList));
}

/*
 * Reads and filters the values of signals in the low priority struct.
 * This function will be called by the scheduler when ever.
 */
void readLowPrioritySignals(void)
{
    readAnalogSignals(&AnalogSignalList, sizeof(AnalogSignalList));
    calculateFilteredValue(&AnalogSignalList, sizeof(AnalogSignalList));
    calculateInverseOfDcLinkMeas();
}

/*
 * This takes the address and the size of the struct of interest, and iterates through it to
 * read the ADC value from the register
 */
void readAnalogSignals(void *signal, int size)
{
    AnalogSignal *structPointer;
    AnalogSignal *initialMemoryPosition = signal;
    AnalogSignal *finalMemoryPosition = initialMemoryPosition + size / sizeof(AnalogSignal);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
        readADCValue(structPointer);
}

/*
 * This takes the address and the size of the struct of interest, and iterates through it to
 * calculate the filtered voltage measured
 */
void calculateFilteredValue(void *signal, int size)
{
    AnalogSignal *structPointer;
    AnalogSignal *initialMemoryPosition = signal;
    AnalogSignal *finalMemoryPosition = initialMemoryPosition + size / sizeof(AnalogSignal);

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
        filterADCValue(structPointer);
}

void calculateInverseOfDcLinkMeas(void)
{
    AnalogSignalList.voltageMeas36.dcLinkInverse = (float)1.0 / getDCLinkMeasurement();
}


/*
 * Returns the error status of the analog measurements.
 * The function returns a '0' in the position of the signal
 * if the measurement is outside the threshold values
 */
Uint16 getHighPriorityErrorStatus(void)
{
    AnalogSignal *structPointer;
    AnalogSignal *initialMemoryPosition = &CurrentSignalList.currentMeasA;
    AnalogSignal *finalMemoryPosition = initialMemoryPosition + sizeof(CurrentSignalList) / sizeof(AnalogSignal);

    Uint16 errorStatus = 0;
    int i = 0;

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
    {
        if (structPointer->filteredValue < structPointer->threshold[0] || structPointer->filteredValue > structPointer->threshold[1])
            errorStatus |= 1<<i;

        i++;
    }

    return errorStatus;
}

Uint16 getLowPriorityErrorStatus(void)
{
    AnalogSignal *structPointer;
    AnalogSignal *initialMemoryPosition = &AnalogSignalList.voltageMeas24;
    AnalogSignal *finalMemoryPosition = initialMemoryPosition + sizeof(AnalogSignalList) / sizeof(AnalogSignal);

    Uint16 errorStatus = 0;
    int i = 3;

    for (structPointer = initialMemoryPosition; structPointer < finalMemoryPosition; structPointer++)
    {
        if (structPointer->filteredValue < structPointer->threshold[0] || structPointer->filteredValue > structPointer->threshold[1])
            errorStatus |= 1<<i;

        i++;
    }

    return errorStatus;
}

/*
 * Function to set thresholds for the current measurements.
 * Absolute minimum and maximum is +/- 300A.
 */
void setCurrentThresholds(float *currentThresholdArray,
                          float maximumCurrent, float minimumCurrent)
{
    float opampVoltage, maximumCurrentThreshold, minimumCurrentThreshold;

    opampVoltage = maximumCurrent/CURRENT_SENSOR_GAIN * R_IN_CURRENT_MEAS;
    maximumCurrentThreshold = OPAMP_GAIN_CURRENT_MEAS * opampVoltage +
                              (1 - OPAMP_GAIN_CURRENT_MEAS) * BIAS_VOLTAGE_OPAMP;

    opampVoltage = minimumCurrent/CURRENT_SENSOR_GAIN * R_IN_CURRENT_MEAS;
    minimumCurrentThreshold = OPAMP_GAIN_CURRENT_MEAS * opampVoltage +
                              (1 - OPAMP_GAIN_CURRENT_MEAS) * BIAS_VOLTAGE_OPAMP;


    *currentThresholdArray = maximumCurrentThreshold;
    currentThresholdArray++;
    *currentThresholdArray = minimumCurrentThreshold;
}

/*
 * Function to set thresholds for the DC-Link voltage measurements.
 * Absolute maximum is 45V.
 */
void setDCLinkVoltageThresholds(float *DCLinkThresholdArray,
                                float maximumVoltage, float minimumVoltage)
{
    float voltageDividerGain, opampGain;
    float maximumVoltageThreshold, minimumVoltageThreshold;

    voltageDividerGain = R2_DCLINK_MEAS / (R1_DCLINK_MEAS + R2_DCLINK_MEAS);
    opampGain = R3_DCLINK_MEAS / R4_DCLINK_MEAS;

    maximumVoltageThreshold = maximumVoltage * voltageDividerGain * opampGain;
    minimumVoltageThreshold = minimumVoltage * voltageDividerGain * opampGain;

    *DCLinkThresholdArray = minimumVoltageThreshold;
    DCLinkThresholdArray++;
    *DCLinkThresholdArray = maximumVoltageThreshold;
}

/*
 * Function to set thresholds for the control supply voltage measurements.
 * Absolute maximum is 30V.
 */
void setControlSupplyVoltageThresholds(float *controlSupplyThresholdArray,
                                       float maximumVoltage, float minimumVoltage)
{
    float voltageDividerGain;
    float maximumVoltageThreshold, minimumVoltageThreshold;

    voltageDividerGain = R2_CONTROL_SUPPLY_MEAS / (R1_CONTROL_SUPPLY_MEAS + R2_CONTROL_SUPPLY_MEAS);

    maximumVoltageThreshold = maximumVoltage * voltageDividerGain;
    minimumVoltageThreshold = minimumVoltage * voltageDividerGain;

    *controlSupplyThresholdArray = minimumVoltageThreshold;
    controlSupplyThresholdArray++;
    *controlSupplyThresholdArray = maximumVoltageThreshold;
}

/*
 * Function to set thresholds for thermal measurements.
 * No realistic maximum, but 330 deg is equal to 3.3V input to DSP
 * Sensor is limited to 2-150 deg.
 */
void setThermometerThresholds(float *thermometerThresholdArray,
                              float maximumTemperature, float minimumTemperature)
{
    float maximumTemperatureThreshold, minimumTemperatureThreshold;

    maximumTemperatureThreshold = maximumTemperature * TEMP_SENSOR_GAIN;
    minimumTemperatureThreshold = minimumTemperature * TEMP_SENSOR_GAIN;

    *thermometerThresholdArray = minimumTemperatureThreshold;
    thermometerThresholdArray++;
    *thermometerThresholdArray = maximumTemperatureThreshold;
}

/*
 * Interface functions to return filtered measurements
 * It's used as followed:
 * float currents[3];
 * getCurrentMeasurements(&currents[0]); //if the first element [0] is not selected a warning is created
 *
 * Where 'currents' then will be an array of the currents as {IA, IB, IC}.
 */
void getCurrentMeasurements(float *currentMeasurement)
{
    *currentMeasurement =
            -(((CurrentSignalList.currentMeasA.filteredValue - OPAMP_OFFSET_CURRENT) * CURRENT_SENSOR_GAIN_INVERSE) - CURRENT_SENSOR_OFFSET_A);

    currentMeasurement++;
    *currentMeasurement =
            -(((CurrentSignalList.currentMeasB.filteredValue - OPAMP_OFFSET_CURRENT) * CURRENT_SENSOR_GAIN_INVERSE) - CURRENT_SENSOR_OFFSET_B);

    currentMeasurement++;
    *currentMeasurement =
            -(((CurrentSignalList.currentMeasC.filteredValue - OPAMP_OFFSET_CURRENT) * CURRENT_SENSOR_GAIN_INVERSE) - CURRENT_SENSOR_OFFSET_C);
}

float getDCLinkMeasurement(void)
{
    return (AnalogSignalList.voltageMeas36.filteredValue * DC_LINK_MEAS_TO_VOLTAGE) - DC_LINK_OFFSET;
}

float getControlsupplyMeasurement(void)
{
    return (AnalogSignalList.voltageMeas24.filteredValue * CONTROL_SUPPLY_MEAS_TO_VOLTAGE) - CONTROL_SUPPLY_OFFSET;
}

float getTorqueReferenceSliderMeasurement(void)
{
    return AnalogSignalList.sliderPotRight.filteredValue;
}

float getSpeedReferenceSliderMeasurement(void)
{
    return AnalogSignalList.sliderPotLeft.filteredValue;
}

float getTorqueReferencePedalMeasurement(void)
{
    return AnalogSignalList.connectorPot1.filteredValue;
}

float getBrakeReferencePedalMeasurement(void)
{
    return AnalogSignalList.connectorPot2.filteredValue;
}

float getThermometer1Measurement(void)
{
    return (AnalogSignalList.thermalMeas1.filteredValue * MEAS_TO_TEMP) - TEMP_SENSOR_OFFSET;
}

float getThermometer2Measurement(void)
{
    return (AnalogSignalList.thermalMeas2.filteredValue * MEAS_TO_TEMP) - TEMP_SENSOR_OFFSET;
}

float getRotaryPot1Measurement(void)
{
    return AnalogSignalList.rotaryPot1.filteredValue;
}

float getRotaryPot2Measurement(void)
{
    return AnalogSignalList.rotaryPot2.filteredValue;
}

float getRotaryPot3Measurement(void)
{
    return AnalogSignalList.rotaryPot3.filteredValue;
}


float getMaxReferenceADC(void)
{
    return MAX_VALUE_ADC;
}

float getInverseOfDcLinkMeasurement(void)
{
    return AnalogSignalList.voltageMeas36.dcLinkInverse;
}

/*
 * Calls all relevant methods to configure the analog signals and ADCs
 */
void initAnalogSignals(void)
{
    createAnalogSignals();
    configureADCRegisters();
}

/*
 * All the analog signals are created.
 * To see link to specific ADC channel se configureADCs()
 * and the defines in analogAcquisitionManager.h
 */
void createAnalogSignals(void)
{
    // Definition of filter parameters
    char filterType = 'L';
    int filterOrder = 1;
    int potFilterFreq = 100, currentFilterFreq = 1000, filterFreq = 1;

    // Definition of thresholds
    float currentThreshold[2], thermalThreshold[2];
    float DCLinkVoltageThreshold[2], controlVoltageThreshold[2];
    float sliderPotThreshold[2] = {0.0, 3.3};
    float rotaryPotThreshold[2] = {0.0, 3.3};
    float connectorPotThreshold[2] = {0.0, 3.3};

    /*
     * To call these functions you pass the address of the first position in the array
     * where you want to save the threshold values. So it is important to initialize the arrays
     * before using them.
     * Then pass the maximum and then the minimum value of the threshold you want to set.
     */
    setCurrentThresholds(&currentThreshold[0], 275, -275);
    setDCLinkVoltageThresholds(&DCLinkVoltageThreshold[0], 42, 10);
    setControlSupplyVoltageThresholds(&controlVoltageThreshold[0], 28, 20);
    setThermometerThresholds(&thermalThreshold[0], 200, 10);

    // Create signal for Current A measurement.
    Uint16 currentMeasAChannel = IA;
    Signal_Constructor(&CurrentSignalList.currentMeasA, filterType, filterOrder,
                       currentFilterFreq, currentMeasAChannel, currentThreshold, HIGH);


    // Create signal for Current B measurement.
    Uint16 currentMeasBChannel = IB;
    Signal_Constructor(&CurrentSignalList.currentMeasB, filterType, filterOrder,
                       currentFilterFreq, currentMeasBChannel, currentThreshold, HIGH);


    // Create signal for Current C measurement.
    Uint16 currentMeasCChannel = IC;
    Signal_Constructor(&CurrentSignalList.currentMeasC, filterType, filterOrder,
                       currentFilterFreq, currentMeasCChannel, currentThreshold, HIGH);


    // Create signal for 24V measurement
    Uint16 voltageMeas24Channel = AD24;
    Signal_Constructor(&AnalogSignalList.voltageMeas24, filterType, filterOrder,
                       filterFreq, voltageMeas24Channel, controlVoltageThreshold, LOW);



    // Create signal for 36V measurement
    Uint16 voltageMeas36Channel = AD36;
    Signal_Constructor(&AnalogSignalList.voltageMeas36, filterType, filterOrder,
                       filterFreq, voltageMeas36Channel, DCLinkVoltageThreshold, LOW);



    // Create signal for Thermal measurement 1
    Uint16 thermalMeas1Channel = J1;
    Signal_Constructor(&AnalogSignalList.thermalMeas1, filterType, filterOrder,
                       filterFreq, thermalMeas1Channel, thermalThreshold, LOW);


    // Create signal for Thermal measurement 2
    Uint16 thermalMeas2Channel = J2;
    Signal_Constructor(&AnalogSignalList.thermalMeas2, filterType, filterOrder,
                       filterFreq, thermalMeas2Channel, thermalThreshold, LOW);


    // Create signal for Left slider Potentiometer
    Uint16 leftSliderPotChannel = P1;
    Signal_Constructor(&AnalogSignalList.sliderPotLeft, filterType, filterOrder,
                       potFilterFreq, leftSliderPotChannel, sliderPotThreshold, LOW);


    // Create signal for Right slider potentiometer
    Uint16 rightSliderPotChannel = P2;
    Signal_Constructor(&AnalogSignalList.sliderPotRight, filterType, filterOrder,
                       potFilterFreq, rightSliderPotChannel, sliderPotThreshold, LOW);


    // Create signal for extra rotary potentiometer 1
    Uint16 rotaryPot1Channel = P3;
    Signal_Constructor(&AnalogSignalList.rotaryPot1, filterType, filterOrder,
                       filterFreq, rotaryPot1Channel, rotaryPotThreshold, LOW);


    // Create signal for extra rotary potentiometer 2
    Uint16 rotaryPot2Channel = P4;
    Signal_Constructor(&AnalogSignalList.rotaryPot2, filterType, filterOrder,
                       filterFreq, rotaryPot2Channel, rotaryPotThreshold, LOW);


    // Create signal for extra rotary potentiometer 3
    Uint16 rotaryPot3Channel = P5;
    Signal_Constructor(&AnalogSignalList.rotaryPot3, filterType, filterOrder,
                       filterFreq, rotaryPot3Channel, rotaryPotThreshold, LOW);


    // Create signal for connector potentiometer 1
    Uint16 connectorPot1Channel = J3;
    Signal_Constructor(&AnalogSignalList.connectorPot1, filterType, filterOrder,
                       filterFreq, connectorPot1Channel, connectorPotThreshold, LOW);


    // Create signal for connector potentiometer 2
    Uint16 connectorPot2Channel = J4;
    Signal_Constructor(&AnalogSignalList.connectorPot2, filterType, filterOrder,
                       filterFreq, connectorPot2Channel, connectorPotThreshold, LOW);
}


/*
 * Link analog signals to ADC channel by setting Channel, Trigger option and Acquisition period.
 * This also sets some initial registers for general setup of ADC.
 */
void configureADCRegisters(void)
{
    EALLOW;

    // Enable non-overlap mode
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP   = 1;

    // ADCINT1 trips after AdcResults latch
    AdcRegs.ADCCTL1.bit.INTPULSEPOS     = 1;
    AdcRegs.INTSEL1N2.bit.INT1E         = 1;
    AdcRegs.INTSEL1N2.bit.INT1CONT      = 0;
  
    EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event

    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;            // Enable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;  // To trigger interrupt at PWM high
//    EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;   // To trigger interrupt at PWM low
    EPwm1Regs.ETPS.bit.SOCAPRD  = 1;            // Generate pulse on 1st event

    // setup EOC1 to trigger ADCINT1 to fire
    AdcRegs.INTSEL1N2.bit.INT1SEL       = 1;

    // Configure ADC for phase A current measurement
    AdcRegs.ADCSOC3CTL.bit.CHSEL        = CurrentSignalList.currentMeasA.adcChannel;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL      = TRIGGER;
    AdcRegs.ADCSOC3CTL.bit.ACQPS        = SAMPLING_RATE;


    // Configure ADC for phase B current measurement
    AdcRegs.ADCSOC13CTL.bit.CHSEL       = CurrentSignalList.currentMeasB.adcChannel;
    AdcRegs.ADCSOC13CTL.bit.TRIGSEL     = TRIGGER;
    AdcRegs.ADCSOC13CTL.bit.ACQPS       = SAMPLING_RATE;

    // Configure ADC for phase C current measurement
    AdcRegs.ADCSOC5CTL.bit.CHSEL        = CurrentSignalList.currentMeasC.adcChannel;
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
