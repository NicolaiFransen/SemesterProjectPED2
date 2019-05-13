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

void runClosedLoopControl(void)
{
    float movementReference = 0;
    float abcCurrents[3];
    float theta = 0;

    dqObject dqCurrents, currentReferences, dqVoltages;
    alphaBetaObject abVoltages;

    // Checks if the system is in cruise or torque control, and returns
    // the reference corresponding to that control type.
    // Then calculates the current references from that.
    movementReference = getMovementReference();
    currentReferences = getCurrentReferences(movementReference);

    getCurrentMeasurements(&abcCurrents[0]);                    // Reads current measurements
    theta = readRotorFluxAngleRad();                            // Reads flux position angle in radians


    dqCurrents = abc2dq(&abcCurrents[0], theta);                // Transform current measurements from abc->dq

    dqVoltages = calculateVoltageReferences(currentReferences, dqCurrents);

    abVoltages = dq2alphabeta(&dqVoltages, theta);              // dq->alpha/beta transformation

    runSVM(abVoltages);
}

dqObject getCurrentReferences(float movementReference)
{
    dqObject currentReferences;

    currentReferences.qComponent = getIqReference(movementReference);
    currentReferences.dComponent = getIdReference();

    return currentReferences;
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


//        UARTIntPrint("qr ", (int)(dqVoltages.qComponent));
//        UARTIntPrint("dr ", (int)(dqVoltages.dComponent));

    return dqVoltages;
}


