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
    dqObject dqCurrents, dqVoltages;
    alphaBetaObject abVoltages;

    movementReference = getMovementReference();         // Reads torque or speed reference

    iqReference = getIqReference(movementReference);    // Calculate iq reference from movement reference
    idReference = calculateIdReference();               // Calculate id reference

    getCurrentMeasurements(&abcCurrents[0]);            // Reads current measurements
    theta = readRotorElecAngleRad();                    // reads electrical angle in radians

    dqCurrents = abc2dq(&abcCurrents[0], theta);        // Transform current measurements from abc->dq

    // Calculate voltage references from current PI-controllers
    dqVoltages.qComponent = PiCalculationIQ(iqReference, dqCurrents.qComponent);
    dqVoltages.dComponent = PiCalculationID(idReference, dqCurrents.dComponent);

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

