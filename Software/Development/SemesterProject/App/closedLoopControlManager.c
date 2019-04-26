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
 *          - Obtain Rotor position angle in radians
 *          - Transform currents from ABC -> dq
 *          - Calculate dq voltage references from current PI-controllers
 *          - Transform voltages from dq -> alpha/beta
 *          - Run SVM with alpha/beta voltages as references.
 */

#include "closedLoopControlManager.h"

void runClosedLoopControl(void)
{
    float movementReference = 0;
    float currentReferences[1];
    float abcCurrents[2];
    float theta = 0;
    dqObject dqCurrents, dqVoltages;
    alphaBetaObject abVoltages;

    // Checks if the system is in cruise or torque control, and returns
    // the reference corresponding to that control type.
    movementReference = getMovementReference();

    currentReferences[0] = getIqReference(movementReference);   // Calculate iq reference from movement the reference.
    currentReferences[1] = calculateIdReference();              // Calculate id reference

    getCurrentMeasurements(&abcCurrents[0]);                    // Reads current measurements
    theta = readRotorElecAngleRad();                            // reads electrical angle in radians

    dqCurrents = abc2dq(&abcCurrents[0], theta);                // Transform current measurements from abc->dq

    dqVoltages = calculateVoltageReferences(currentReferences, dqCurrents);

    abVoltages = dq2alphabeta(&dqVoltages, theta);              // dq->alpha/beta transformation

    runSVM(abVoltages);
}

/*
 * Function to determine what kind of control is wanted,
 * and returns the proper reference
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
        iqReference = calculateIqReference(movementReference);

    else
    {
        // get measured speed
        int16 speedMeasurement = readRotorRPM();

        // Calculate iq reference from speed controller
        iqReference = PiCalcualtionSpeed(movementReference, speedMeasurement);
    }

    return iqReference;
}

/*
 * Function to calculate the voltage references for the
 * SVM in dq reference frame.
 */
dqObject calculateVoltageReferences(float currentReferences[], dqObject dqCurrents)
{
    dqObject dqVoltages;
    // Calculate voltage references from current PI-controllers
    dqVoltages.qComponent = PiCalculationIQ(currentReferences[0], dqCurrents.qComponent);
    dqVoltages.dComponent = PiCalculationID(currentReferences[1], dqCurrents.dComponent);

    return dqVoltages;
}


