/*
 * digitalOutputManager.c
 *
 *  Created on: 27. mar. 2019
 *      Author: Nicolai Fransen
 */

#include "digitalInputManager.h"
#include "digitalOutput.h"
#include "../System/Include/GPIOConfig.h"
#include "digitalOutputManager.h"

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
    DigitalOutput errorLED;
    DigitalOutput extraLED1;
    DigitalOutput extraLED2;
    DigitalOutput extraLED3;
    DigitalOutput extraLED4;
    DigitalOutput extraLED5;
    DigitalOutput extraLED6;
    DigitalOutput extraLED7;
    DigitalOutput extraLED8;

    DigitalOutput enablePWM;
    DigitalOutput extraConnectorJ20;
    DigitalOutput extraConnectorJ21;
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
    digitalOutput_Constructor(&digitalOutputList.errorLED, DS17);
    digitalOutput_Constructor(&digitalOutputList.LED18, DS18);
    digitalOutput_Constructor(&digitalOutputList.LED19, DS19);
    digitalOutput_Constructor(&digitalOutputList.LED20, DS20);
    digitalOutput_Constructor(&digitalOutputList.extraLED1, J5);
    digitalOutput_Constructor(&digitalOutputList.extraLED2, J6);
    digitalOutput_Constructor(&digitalOutputList.extraLED3, J7);
    digitalOutput_Constructor(&digitalOutputList.extraLED4, J8);
    digitalOutput_Constructor(&digitalOutputList.extraLED5, J9);
    digitalOutput_Constructor(&digitalOutputList.extraLED6, J10);
    digitalOutput_Constructor(&digitalOutputList.extraLED7, J11);
    digitalOutput_Constructor(&digitalOutputList.extraLED8, J12);

    digitalOutput_Constructor(&digitalOutputList.enablePWM, J17);
    digitalOutput_Constructor(&digitalOutputList.extraConnectorJ20, J20);
    digitalOutput_Constructor(&digitalOutputList.extraConnectorJ21, J21);
}

/*
 * These are the interface function to be used to set the specific output
 */
void setAntiSlipLED(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.antiSlipLED, state);
}

void setCruiseControlLED(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.cruiseControlLED, state);
}

void setRegenerativeBrakingLED(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.regenerativeBrakingLED, state);
}

void setTorqueReferenceSliderLED(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.torqueReferenceSliderLED, state);
}

void setTorqueReferencePedalLED(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.torqueReferencePedalLED, state);
}

void setTorqueReferenceUARTLED(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.torqueReferenceUARTLED, state);
}

void setLED9(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.LED9, state);
}

void setLED10(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.LED10, state);
}

void setErrorLED(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.errorLED, state);
}

void setLED18(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.LED18, state);
}

void setLED19(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.LED19, state);
}

void setLED20(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.LED20, state);
}

void setExtraLED1(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.extraLED1, state);
}

void setExtraLED2(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.extraLED2, state);
}

void setExtraLED3(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.extraLED3, state);
}

void setExtraLED4(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.extraLED4, state);
}

void setExtraLED5(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.extraLED5, state);
}

void setExtraLED6(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.extraLED6, state);
}

void setExtraLED7(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.extraLED7, state);
}

void setExtraLED8(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.extraLED8, state);
}

void setEnablePWM(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.enablePWM, state);
}

void setExtraConnectorJ20(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.extraConnectorJ20, state);
}

void setExtraConnectorJ21(digitalOutputStatus state)
{
    setDigitalOutput(&digitalOutputList.extraConnectorJ21, state);
}


/*
 * These are the interface function to be used to get the state of
 * the specific output
 */
int getAntiSlipLEDState(void)
{
    return digitalOutputList.antiSlipLED.state;
}

int getCruiseControlLEDState(void)
{
    return digitalOutputList.cruiseControlLED.state;
}

int getRegenerativeBrakingLEDState(void)
{
    return digitalOutputList.regenerativeBrakingLED.state;
}

int getTorqueReferenceSliderLEDState(void)
{
    return digitalOutputList.torqueReferenceSliderLED.state;
}

int getTorqueReferencePedalLEDState(void)
{
    return digitalOutputList.torqueReferencePedalLED.state;
}

int getTorqueReferenceUARTLEDState(void)
{
    return digitalOutputList.torqueReferenceUARTLED.state;
}

int getLED9State(void)
{
    return digitalOutputList.LED9.state;
}

int getLED10State(void)
{
    return digitalOutputList.LED10.state;
}

int getErrorLEDState(void)
{
    return digitalOutputList.errorLED.state;
}

int getLED18State(void)
{
    return digitalOutputList.LED18.state;
}

int getLED19State(void)
{
    return digitalOutputList.LED19.state;
}

int getLED20State(void)
{
    return digitalOutputList.LED20.state;
}



int getEnablePWMState(void)
{
    return digitalOutputList.enablePWM.state;
}

int getExtraConnectorJ20State(void)
{
    return digitalOutputList.extraConnectorJ20.state;
}

int getExtraConnectorJ21State(void)
{
    return digitalOutputList.extraConnectorJ21.state;
}
