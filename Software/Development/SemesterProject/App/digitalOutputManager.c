/*
 * digitalOutputManager.c
 *
 *  Created on: 27. mar. 2019
 *      Author: Nicolai Fransen
 */

#include "digitalInputManager.h"
#include "digitalOutput.h"
#include "../System/Include/GPIOConfig.h"


/*
 * Struct containing all digital output signals
 */
static struct digitalOutputListTag
{
    DigitalOutput antiSlipLED;
    DigitalOutput cruiseControlLED;
    DigitalOutput regenerativeBrakingLED;
    DigitalOutput torqueReferenceSliderLED;
    DigitalOutput LED19;
    DigitalOutput LED20;
    DigitalOutput torqueReferencePedalLED;
    DigitalOutput torqueReferenceUARTLED;
    DigitalOutput LED10;
    DigitalOutput LED9;
    DigitalOutput LED18;
    DigitalOutput LED17;
    DigitalOutput enablePWM;
} digitalOutputList;


/*
 * This function initializes all digital outputs defined in the struct above.
 * The pin number is defined as the name of the LED/connector.
 */
void initDigitalOutputs(void)
{
    digitalOutput_Constructor(&digitalOutputList.antiSlipLED, DS16);
    digitalOutput_Constructor(&digitalOutputList.cruiseControlLED, DS15);
    digitalOutput_Constructor(&digitalOutputList.regenerativeBrakingLED, DS14);
    digitalOutput_Constructor(&digitalOutputList.torqueReferenceSliderLED, DS13);
    digitalOutput_Constructor(&digitalOutputList.torqueReferencePedalLED, DS12);
    digitalOutput_Constructor(&digitalOutputList.torqueReferenceUARTLED, DS11);
    digitalOutput_Constructor(&digitalOutputList.LED9, DS9);
    digitalOutput_Constructor(&digitalOutputList.LED10, DS10);
    digitalOutput_Constructor(&digitalOutputList.LED17, DS17);
    digitalOutput_Constructor(&digitalOutputList.LED18, DS18);
    digitalOutput_Constructor(&digitalOutputList.LED19, DS19);
    digitalOutput_Constructor(&digitalOutputList.LED20, DS20);
    digitalOutput_Constructor(&digitalOutputList.enablePWM, J17);
}

/*
 * These are the interface function to be used to set the specific output
 */
void setAntiSlipLED(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.antiSlipLED, state);
}

void setCruiseControlLED(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.cruiseControlLED, state);
}

void setRegenerativeBrakingLED(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.regenerativeBrakingLED, state);
}

void setTorqueReferenceSliderLED(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.torqueReferenceSliderLED, state);
}

void setTorqueReferencePedalLED(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.torqueReferencePedalLED, state);
}

void setTorqueReferenceUARTLED(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.torqueReferenceUARTLED, state);
}

void setLed9(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.LED9, state);
}

void setLED10(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.LED10, state);
}

void setLED17(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.LED17, state);
}

void setLED18(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.LED18, state);
}

void setLED19(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.LED19, state);
}

void setLED20(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.LED20, state);
}

void setEnablePWM(LEDStatus state)
{
    setDigitalOutput(&digitalOutputList.enablePWM, state);
}
