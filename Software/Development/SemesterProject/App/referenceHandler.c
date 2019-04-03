/*
 * referenceHandler.c
 *
 *  Created on: Mar 27, 2019
 *      Author: Nicolas
 *
 *      >>Looking at the system description diagram found in the class design
 *      is highly recommended<<
 *
 *      The goal of this module is to check what reference source is selected
 *      by the user. When the source is known, the value of that reference must
 *      be obtained. When the value is obtained and with the goal of limiting
 *      large reference differences a new reference considering the maximum
 *      allowed reference derivative is provided by means of an interface. Then,
 *      in order to avoid references over the technical limits of the system,
 *      like a 100 Nm torque reference, the references are limited to a preset
 *      value MAX_TORQUE_REF_NM and MAXIMUM_SPEED_REF_RPM.
 *
 *      The interfaces provided are:
 *          *Torque reference
 *          *Speed reference
 *          *Open-loop reference (which collects the reference from torque inputs)
 *          *Cruise control or Torque control
 *          *Reference source
 *          *Reference source change
 *
 *      The scheduled function is handleReferences().
 *      In this module there are two tasks performed:
 *      ** Reference calculation    calculateReference()
 *      ** Reference type (torque/cruise control) decision  decideReferenceType()
 *
 *
 */

#include "referenceHandler.h"

/*
 * Quasi-global definition
 */
static GUISignalsTag GUISignals;
static float speedReference, torqueReference;
static float deltaSpeed = 5, deltaTorque = 0.1;
static int undampedSpeedReference = 0;
static int referenceSourceChanged = 0;


static referenceSourceTag referenceSource = interfacePCB;
static enum referenceTypeTag referenceType = torqueControl;


void handleReferences(void)
{
    GUISignals = getGUISignals();
    decideReferenceSource();
    if (readSystemState() == RUNNING)
    {
        calculateReference();
        decideReferenceType();
    }
}

void decideReferenceSource(void)
{
    switch (referenceSource)
        {
        case interfacePCB:
        {
            setTorqueReferenceSliderLED(ON); // Necessary for system startup
            if (referenceSourceIsChanged())
            {
                setTorqueReferenceSliderLED(OFF);
                referenceSource = goKart;
                setTorqueReferencePedalLED(ON);
            }
        }break;
        case goKart:
        {
            if (referenceSourceIsChanged())
            {
                setTorqueReferencePedalLED(OFF);
                referenceSource = GUI;
                setTorqueReferenceUARTLED(ON);
            }
        }break;
        case GUI:
        {
            if (referenceSourceIsChanged())
            {
                setTorqueReferenceUARTLED(OFF);
                referenceSource = interfacePCB;
                setTorqueReferenceSliderLED(ON);
            }
        }break;
        }
}

void decideReferenceType(void)
{
    setCruiseControlLED(OFF);
    switch (referenceType)
    {
    case torqueControl:
    {
        if (referenceTypeIsChanged())
        {
            undampedSpeedReference = 1000;// THIS MUST BE ADDED WHEN THE INTERFACE FROM CONTROL IS CREATED getCurrentRotorSpeed();
            referenceType = cruiseControl;
        }
    }break;
    case cruiseControl:
    {
        if (referenceTypeIsChanged())
        {
            referenceType = torqueControl;
            restartSpeedReference();
        }
        setCruiseControlLED(ON);
    }break;
    }
}

void calculateReference(void)
{
    calculateTorqueReference();
    calculateSpeedReference();
}

void calculateTorqueReference(void)
{
    float torqueReferenceBeforeLimit = 0, torqueReferenceBeforeSaturation = 0;

    torqueReferenceBeforeLimit = getReferenceValue();
    torqueReferenceBeforeSaturation = calculateLimitedTorqueReference(torqueReferenceBeforeLimit);
    torqueReference = calculateSaturatedTorque(torqueReferenceBeforeSaturation);
}

int referenceSourceIsChanged(void)
{
    if (GUISignals.ReferenceSourcePushbutton || referenceSourceHasBeenPressed())
    {
        torqueReference = 0;
        speedReference = 0;
        if ((readSystemState() == RUNNING)) referenceSourceChanged = 1; //If the referenceSOurce is changed while in running, qualify the change so the system know it must go back to STANDBY
        return 1;
    }
    else    return 0;
}

int referenceTypeIsChanged(void)
{
    return (GUISignals.ReferenceTypePushbutton || referenceTypeHasBeenPressed());
}

float getReferenceValue(void)
{
    float analogValueTorque = 0, torqueReferenceBeforeLimit = 0;
    switch (referenceSource)
    {
    case interfacePCB:
    {
        analogValueTorque = getTorqueReferenceSliderMeasurement();
        torqueReferenceBeforeLimit = CalculateTorqueRefFromAnalog(analogValueTorque);
    }break;
    case goKart:
    {
        analogValueTorque = getTorqueReferencePedalMeasurement();
        torqueReferenceBeforeLimit = CalculateTorqueRefFromAnalog(analogValueTorque);
    }break;
    case GUI:
    {
        torqueReferenceBeforeLimit = GUISignals.TorqueReference;
    }break;
    }
    return torqueReferenceBeforeLimit;
}

float CalculateTorqueRefFromAnalog(float analogRead)
{
    return analogRead/MAX_VALUE_ADC*MAX_TORQUE_REF_NM;
}

float calculateLimitedTorqueReference(float torqueReferenceBeforeLimit)
{
    if (referenceIncreased(torqueReferenceBeforeLimit)) return torqueReference + deltaTorque;
    if (referenceDecreased(torqueReferenceBeforeLimit)) return torqueReference - deltaTorque;
    else    return torqueReference;
}

int referenceIncreased(float torqueReferenceBeforeLimit)
{
    return torqueReferenceBeforeLimit > torqueReference + deltaTorque;
}

int referenceDecreased(float torqueReferenceBeforeLimit)
{
    return torqueReferenceBeforeLimit < torqueReference - deltaTorque;
}

float calculateSaturatedTorque(float torqueBeforeSaturation)
{
    if (torqueBeforeSaturation > MAX_TORQUE_REF_NM) return MAX_TORQUE_REF_NM;
    else return torqueBeforeSaturation;
}

void calculateSpeedReference(void)
{
    int speedReferenceBeforeLimit = 0, speedReferenceBeforeSaturation = 0;
    speedReferenceBeforeLimit = getSpeedReferenceValue();
    speedReferenceBeforeSaturation = calculateLimitedSpeedReference(speedReferenceBeforeLimit);
    speedReference = calculateSaturatedSpeed(speedReferenceBeforeSaturation);
}
int getSpeedReferenceValue(void)
{
    if (speedMustBeIncreased())     undampedSpeedReference += SPEED_STEP_FROM_BUTTON;
    if (speedMustBeDecreased())     undampedSpeedReference -= SPEED_STEP_FROM_BUTTON;

    return undampedSpeedReference;
}

int calculateLimitedSpeedReference(int speedReferenceBeforeLimit)
{
    if (speedRefIncreased(speedReferenceBeforeLimit)) return speedReferenceBeforeLimit + deltaSpeed;
    if (speedRefDecreased(speedReferenceBeforeLimit)) return speedReferenceBeforeLimit - deltaSpeed;
    else return speedReferenceBeforeLimit;
}

int speedRefIncreased(int speedReferenceBeforeLimit)
{
    return speedReferenceBeforeLimit > speedReference + deltaSpeed;
}

int speedRefDecreased(int speedReferenceBeforeLimit)
{
    return speedReferenceBeforeLimit < speedReference - deltaSpeed;
}

int speedMustBeIncreased(void)
{
    return speedRefIncreaseHasBeenPressed();
}

int speedMustBeDecreased(void)
{
    return speedRefDecreaseHasBeenPressed();
    }

int calculateSaturatedSpeed(int speedReferenceBeforeSaturation)
{
    if (speedReferenceBeforeSaturation > MAXIMUM_SPEED_REF_RPM) return MAXIMUM_SPEED_REF_RPM;
    else return speedReferenceBeforeSaturation;
}

void restartSpeedReference(void)
{
    undampedSpeedReference = 0;
}

/*
 * External software components interface
 */

float getTorqueReference(void)
{
    return torqueReference;
}

float getSpeedReference(void)
{
    return speedReference;
}

float getOpenLoopReference(void) //Provide a value between 0 and 100
{
    return torqueReference / MAX_TORQUE_REF_NM * 100;
}

int torqueControlIsEnabled(void)
{
    return referenceType == torqueControl;
}

referenceSourceTag getReferenceSource(void)
{
    return referenceSource;
}

int referenceSourceHasChanged(void)
{
    int tempValue;
    tempValue = referenceSourceChanged;
    referenceSourceChanged = 0;
    return tempValue;
}

