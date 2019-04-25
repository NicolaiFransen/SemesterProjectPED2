/*
 * closedLoopControlManager.c
 *
 *  Created on: 25. apr. 2019
 *      Author: Nicolai Fransen
 */

#include "closedLoopControlManager.h"

void runClosedLoopControl(void)
{
    float movementReference = 0;
    float iqReference = 0, idReference = 0;
    float abcCurrents[2];
    float theta = 0;
    volatile dqObject dqCurrents, dqVoltages;
    alphaBetaObject abVoltages;

    movementReference = getMovementReference();         // Reads torque or speed reference

    iqReference = getIqReference(movementReference);    // Calculate iq reference from movement reference
    idReference = calculateIdReference();               // Calculate id reference

    getCurrentMeasurements(&abcCurrents[0]);            // Reads current measurements
    theta = readRotorElecAngleRad();                    // reads electrical angle in radians

    dqCurrents = abc2dq(&abcCurrents[0], theta);        // Transform current measurements from abc->dq

    // Calculate voltage references from current PI-controllers
    dqVoltages.qComponent = PICalculationIQ(iqReference, dqCurrents.qComponent);
    dqVoltages.dComponent = PICalculationID(idReference, dqCurrents.dComponent);

    abVoltages = dq2alphabeta(&dqVoltages, theta);       // d/q->alpha/beta transformation

    runSVM(abVoltages);
}

float getMovementReference(void)
{
    float movementReference = 0;
    if (torqueControlIsEnabled())
        movementReference = getTorqueReference();
    else
        movementReference = getSpeedReference();

    return movementReference;
}

// get parameter types to match the used functions      TODO
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

    return iqReference;
}

