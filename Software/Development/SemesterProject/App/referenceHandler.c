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
 *      allowed reference derivative is calculated. This is calculated by setting
 *      a maximum deltaTorque and deltaSpeed.
 *
 *      For example, if the reference is changed from 10 Nm to 20 Nm, it will
 *      increase deltaTorque every time the referenceHandler is run.
 *      If deltaTorque is 0.1 and the referenceHandler is run every 20 ms.
 *      The new reference will be reached in (20 - 10)/(0.1/20e-3) = 2 s. The
 *      key parameter is deltaTorque and the user can select the desired value.
 *
 *      Then, in order to avoid references over the technical limits of the system,
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
static float deltaSpeed = 0.05, deltaTorque = 0.01; //This values are set for execution at 1 kHz, original values were 1 and 0.1
static int undampedSpeedReference = 0;
static int referenceSourceChanged = 0;


static referenceSourceTag referenceSource = interfacePCB;
static enum referenceTypeTag referenceType = torqueControl;
const int SPEED_STEP_FROM_BUTTON_RPM = 60 * SPEED_STEP_FROM_BUTTON_KPH / 3.6 * GEAR_RATIO / RADIUS_WHEELS;


void handleReferences(void)
{
    GUISignals = getGUISignals();
    decideReferenceSource();
    if (readSystemState() == RUNNING)
    {
        calculateReference();
        decideReferenceType();
    }
    else    restartReferences();
}

/*
 * This FSM decides what reference is going to be used for setting a torque
 * reference. The options are Interface PCB, Pedal or Graphical user interface.
 */
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
        default:    referenceSource = interfacePCB;
        }
}

/*
 * This FSM decides what type of control is used for controlling the motor: Torque
 * control or cruise control. If the system is being torque controlled and the user
 * requests cruise control, the instantaneous rotor speed will be acquired and will
 * be used as the reference for the control algorithm.
 */
void decideReferenceType(void)
{
    setCruiseControlLED(OFF);
    switch (referenceType)
    {
    case torqueControl:
    {
        if (referenceTypeIsChanged())
        {
            undampedSpeedReference = abs(readRotorRPM());
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
    default:    referenceType = torqueControl;
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
        restartReferences();
        referenceType = torqueControl;
        if ((readSystemState() == RUNNING)) referenceSourceChanged = 1; //If the referenceSOurce is changed while in running, qualify the change so the system know it must go back to STANDBY
        return 1;
    }
    else    return 0;
}

int referenceTypeIsChanged(void)
{
    return (GUISignals.ReferenceTypePushbutton || referenceTypeHasBeenPressed());
}

/*
 * This FSM analyses what is the reference source selected and then acquires
 * the torque reference from Analog read or graphical user interface.
 */
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
    if (speedMustBeIncreased())     undampedSpeedReference += SPEED_STEP_FROM_BUTTON_RPM;
    if (speedMustBeDecreased())     undampedSpeedReference -= SPEED_STEP_FROM_BUTTON_RPM;

    return undampedSpeedReference;
}

/*
 * The current speed reference input by the user is compared to the speed
 * reference used by the control algorithm. If there's a big difference
 * between them, speedReferenceBeforeLimit is increased by deltaSpeed,
 * which is a user selectable value. If there's no difference, the same
 * value is returned.
 */
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
    return (speedRefIncreaseHasBeenPressed() || GUISignals.SpeedIncreasePushbutton);
}

int speedMustBeDecreased(void)
{
    return (speedRefDecreaseHasBeenPressed() || GUISignals.SpeedDecreasePushbutton);
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

void restartReferences(void)
{
    torqueReference = 0;
    speedReference = 0;
}

/*
 * External software components interface
 */

float getTorqueReference(void)
{
    return torqueReference;
}

float getIqReferenceTorqueControl(void)
{
    return torqueReference * TORQUE_TO_Q_CURRENT;
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

void setSpeedRamp(int rampRPMperSec)
{
    deltaSpeed = referenceHandlerPeriodicity * rampRPMperSec;
}

void setTorqueRamp(int rampNmperSec)
{
    deltaTorque = referenceHandlerPeriodicity * rampNmperSec;
}

