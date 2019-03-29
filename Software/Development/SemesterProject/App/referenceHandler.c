/*
 * referenceHandler.c
 *
 *  Created on: Mar 27, 2019
 *      Author: Nicolas
 *
 *      The goal of this module is to check what reference source is selected
 *      by the user. When the source is known, the value of that reference must
 *      be obtained. When the value is obtained and with the goal of limiting
 *      large reference differences a new reference considering the maximum
 *      allowed reference derivative is provided by means of an interface.
 *
 */

#include "referenceHandler.h"

/*
 * Quasi-global definition
 */
static GUISignalsTag GUISignals;
static float speedReference, torqueReference;
static float deltaSpeed, deltaTorque;
static int undampedSpeedReference = 0;


static enum referenceSourceTag referenceSource = interfacePCB;
static enum referenceTypeTag referenceType = torqueControl;


void decideReferenceType(void)
{
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
        if (referenceTypeIsChanged())   referenceType = torqueControl;
    }break;
    }
}

void calculateReference(void)
{
    GUISignals = getGUISignals();
    calculateTorqueReference();
    calculateSpeedReference();
}

void calculateTorqueReference(void)
{
    float torqueReferenceBeforeLimit, torqueReferenceBeforeSaturation;

    decideReferenceSource();
    torqueReferenceBeforeLimit = getReferenceValue();
    torqueReferenceBeforeSaturation = calculateLimitedTorqueReference(torqueReferenceBeforeLimit);
    torqueReference = calculateSaturatedTorque(torqueReferenceBeforeSaturation);
}

void decideReferenceSource(void)
{
    if (referenceSourceIsChanged())
    {
        referenceSource++;
        if (referenceSource == lastIndexRS) referenceSource = interfacePCB;
    }
}

int referenceSourceIsChanged(void)
{
    return (GUISignals.ReferenceSourcePushbutton);// || torqueReferenceHasBeenPressed()) DO NOT FORGET TO ADD THIS FUNCTION WHEN PUSHBUTTON HANDLER IS MERGED
}

int referenceTypeIsChanged(void)
{
    return (GUISignals.ReferenceTypePushbutton); // || cruiseControlHasBeenPressed()DO NOT FORGET TO ADD THIS FUNCTION WHEN PUSHBUTTON HANDLER IS MERGED
}

float getReferenceValue(void)
{
    float analogValueTorque, torqueReferenceBeforeLimit;
    switch (referenceSource)
    {
    case interfacePCB:
    {
        analogValueTorque = getTorqueReferenceSliderMeasurement();
        torqueReferenceBeforeLimit = CalculateTorqueRefFromAnalog(analogValueTorque);
    }break;
    case GUI:
    {
        torqueReferenceBeforeLimit = GUISignals.TorqueReference;
    }break;
    case goKart:
    {
        analogValueTorque = getTorqueReferencePedalMeasurement();
        torqueReferenceBeforeLimit = CalculateTorqueRefFromAnalog(analogValueTorque);
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
    int speedReferenceBeforeLimit, speedReferenceBeforeSaturation;
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
    return speedReferenceBeforeLimit - speedReference - deltaSpeed;
}

int speedMustBeIncreased(void)
{
    return 0;//speedRefIncreaseHasBeenPressed(); add after pushbuttton MGR
}

int speedMustBeDecreased(void)
{
    return 0; // speedRefDecreaseHasBeenPressed(); add after pushbuttton MGR
}

int calculateSaturatedSpeed(int speedReferenceBeforeSaturation)
{
    if (speedReferenceBeforeSaturation > MAXIMUM_SPEED_REF_RPM) return MAXIMUM_SPEED_REF_RPM;
    else return speedReferenceBeforeSaturation;
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
