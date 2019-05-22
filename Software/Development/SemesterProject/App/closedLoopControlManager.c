/*
 * closedLoopControlManager.c
 *
 *  Created on: 25. apr. 2019
 *      Author: Nicolai Fransen
 *
 *      This module contains the closed loop control algorithm of the system
 *
 *      It collects all the different parts of the control system and calls
 *      them in the correct order.
 *
 *      The flow is:
 *          - Obtain references
 *          - Obtain currents
 *          - Obtain Rotor flux position angle in radians
 *          - Transform currents from ABC -> dq
 *          - Calculate dq voltage references from current PI-controllers
 *          - Transform voltages from dq -> alpha/beta
 *          - Run SVM with alpha/beta voltages as references.
 */

#include "closedLoopControlManager.h"

static int systemIsInStartup = 1;
static int16 maxDuty = 10;


void runClosedLoopControl(void)
{
    float movementReference = 0;
    float abcCurrents[3];
    float theta = 0;
    dqObject dqCurrents, currentReferences, dqVoltages;
    alphaBetaObject abVoltages;

    handleControlParameters();
    movementReference = getMovementReference();
    currentReferences = getCurrentReferences(movementReference);

    getCurrentMeasurements(&abcCurrents[0]);                    // Reads current measurements
//    if (getUartCounter() == 1)    UARTIntPrint("a ", (int)(abcCurrents[0]));

    theta = readRotorFluxAngleRad();                            // Reads flux position angle in radians

//    if (getUartCounter() == 2)    UARTIntPrint("t ", (int)(theta*100));

    dqCurrents = abc2dq(&abcCurrents[0], theta);                // Transform current measurements from abc->dq

    dqVoltages = calculateVoltageReferences(currentReferences, dqCurrents);

    abVoltages = dq2alphabeta(&dqVoltages, theta);              // dq->alpha/beta transformation

    runSVM(abVoltages);                 //  Self developed SVM
    //runSVM_DMC(abVoltages);           //SVM from TI's Digital Motor Control
}

dqObject getCurrentReferences(float movementReference)
{
    dqObject currentReferences;

    //    currentReferences.qComponent = 50;
    //    currentReferences.dComponent = 50;
    currentReferences.qComponent = getIqReferenceTorqueControl();
    currentReferences.dComponent = getIdReference();
    //    if (getUartCounter() == 3) UARTIntPrint("dr ", (int)(currentReferences.dComponent));
    //        if (getUartCounter() == 3) UARTIntPrint("qr ", (int)(currentReferences.qComponent));
    //    if (getUartCounter() == 3) UARTIntPrint("tr ", (int)(movementReference * 10));

    return currentReferences;
}


void runStartUpControl(void)
{
    if (!1)
        systemIsInStartup = 0;

    if (systemIsInStartup)
    {
        openLoopVFControl();
        setLED19(OFF);
    }
    else
    {
        runClosedLoopControl();
        setLED19(ON);
    }
}

/*
 * Function to determine what kind of control is wanted,
 * and returns the proper reference
 * Checks if the system is in cruise or torque control, and returns
 * the reference corresponding to that control type.
 */
float getMovementReference(void)
{
    float movementReference = 0;
    if (torqueControlIsEnabled())
        movementReference = getTorqueReference();
    else
        movementReference = getSpeedReference();

    return movementReference;
}

/*
 * Function to calculate the iq reference according to
 * the selected reference type.
 */
float getIqReference(float movementReference)
{
    float iqReference = 0;

    if (torqueControlIsEnabled())
        iqReference = getIqReferenceTorqueControl();

    else
    {
        // get measured speed
        int16 speedMeasurement = readRotorRPM();

        // Calculate iq reference from speed controller
        iqReference = PiCalculationSpeed(movementReference, speedMeasurement);
    }

    // If the wanted output is outside saturation limits, then limit the output
    if (isOutputSaturatedPositive(iqReference))
    {
        iqReference = CURRENT_LIMIT;
    }
    else if (isOutputSaturatedNegative(iqReference))
    {
        iqReference = -(CURRENT_LIMIT);
    }

    return iqReference;
}

/*
 * Function to calculate the voltage references for the
 * SVM in dq reference frame.
 */
dqObject calculateVoltageReferences(dqObject currentReferences, dqObject dqCurrents)
{
    dqObject dqVoltages;

    // Calculate voltage references from current PI-controllers
    dqVoltages.qComponent = PiCalculationIQ(currentReferences.qComponent, dqCurrents.qComponent);
    dqVoltages.dComponent = PiCalculationID(currentReferences.dComponent, dqCurrents.dComponent);



    return dqVoltages;
}

/*
 * This function performs a controlled increase of the control parameters
 * in order to have a smooth startup. The parameters are:
 *  +   PI_Ratio
 *  +   MAX_DUTY_CYCLE
 *  The increase is proportional to the rotor speed: when the speed is 0
 *  the parameters will provide the most dampened response.
 */
void handleControlParameters(void)
{
    float rotorSpeedRatio = 0;
    int16 rotorSpeed = abs(readRotorRPM());

    maxDuty = getDutyRatio(rotorSpeed) * MAX_DUTY_CYCLE;
    updatePIRatio(getPIRatio(rotorSpeed));
}


float getDutyRatio(int16 rotorSpeed)
{
    float dutyRatio = 0;
    dutyRatio = (float)(rotorSpeed - SPEED_DUTY_MIN_DUTY) * FITTING_FUNCTION_SLOPE_DUTY + MIN_DUTY;

    if (dutyRatio > MAX_DUTY)   dutyRatio = MAX_DUTY;
    if (dutyRatio < MIN_DUTY) dutyRatio = MIN_DUTY;

    return dutyRatio;
}

float getPIRatio(int16 rotorSpeed)
{
    float PIRatio = 0;
    PIRatio = (float)(rotorSpeed - SPEED_DUTY_MIN_PI) * FITTING_FUNCTION_SLOPE_PI + MIN_DUTY;
    if (PIRatio > MAX_DUTY)   PIRatio = MAX_DUTY;
    if (PIRatio < MIN_DUTY) PIRatio = MIN_DUTY;

    return PIRatio;
}

//float getDutyRatio(int16 rotorSpeed)
//{
//    float dutyRatio = 0;
//    if (rotorSpeed > STARTUP_SPEED_THRESHOLD_DUTY)   dutyRatio = 1;
//    else    dutyRatio = (float)rotorSpeed * STARTUP_SPEED_THRESHOLD_INV_DUTY + 0.1;
//    if (dutyRatio < MINIMUM_ROTOR_SPEED_RATIO) dutyRatio = MINIMUM_ROTOR_SPEED_RATIO;
//
//    return dutyRatio;
//}
//
//float getPIRatio(int16 rotorSpeed)
//{
//    float PIRatio = 0;
//    if (rotorSpeed > STARTUP_SPEED_THRESHOLD_PI)   PIRatio = 1;
//    else    PIRatio = (float)rotorSpeed * STARTUP_SPEED_THRESHOLD_INV_PI + 0.125;
//    if (PIRatio < MINIMUM_ROTOR_SPEED_RATIO) PIRatio = MINIMUM_ROTOR_SPEED_RATIO;
//
//    return PIRatio;
//}

int16 getMaxDuty(void)
{
//    if (getUartCounter() == 25)
//    UARTIntPrint("D ", (int)(maxDuty));
    return maxDuty;
}
