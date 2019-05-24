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

static int16 maxDuty = 10;


void runClosedLoopControl(void)
{
    float abcCurrents[3];
    float theta = 0;
    dqObject dqCurrents, currentReferences, dqVoltages;
    alphaBetaObject abVoltages;

    handleControlParameters();
    calcIqReference();
    currentReferences = getCurrentReferences();

    getCurrentMeasurements(&abcCurrents[0]);                    // Reads current measurements
//    if (getUartCounter() == 1)    UARTIntPrint("a ", (int)(abcCurrents[0]));

    theta = readRotorFluxAngleRad();                            // Reads flux position angle in radians

//    if (getUartCounter() == 2)    UARTIntPrint("t ", (int)(theta*100));

    dqCurrents = abc2dq(&abcCurrents[0], theta);                // Transform current measurements from abc->dq
    sendCurrentMeasurementsToGUI(dqCurrents.dComponent, dqCurrents.qComponent);

    dqVoltages = calculateVoltageReferences(currentReferences, dqCurrents);

    abVoltages = dq2alphabeta(&dqVoltages, theta);              // dq->alpha/beta transformation

    runSVM(abVoltages);                 //  Self developed SVM
    //runSVM_DMC(abVoltages);           //SVM from TI's Digital Motor Control
}

dqObject getCurrentReferences(void)
{
    dqObject currentReferences;

    currentReferences.qComponent = getIqReference();
    currentReferences.dComponent = D_CURRENT_REFERENCE_MAX;
    if (getUartCounter() == 3) UARTIntPrint("dr ", (int)(currentReferences.dComponent));
    if (getUartCounter() == 4) UARTIntPrint("qr ", (int)(currentReferences.qComponent));
    //    if (getUartCounter() == 3) UARTIntPrint("tr ", (int)(movementReference * 10));

    return currentReferences;
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
    PIRatio = (float)(rotorSpeed - SPEED_DUTY_MIN_PI) * FITTING_FUNCTION_SLOPE_PI + MIN_PI;
    if (PIRatio > MAX_PI)   PIRatio = MAX_PI;
    if (PIRatio < MIN_PI) PIRatio = MIN_PI;

    return PIRatio;
}

int16 getMaxDuty(void)
{
//    if (getUartCounter() == 25)
//    UARTIntPrint("D ", (int)(maxDuty));
    return maxDuty;
}
