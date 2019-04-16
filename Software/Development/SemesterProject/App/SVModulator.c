/*
 * SVModulator.c
 *
 *  Created on: Apr 16, 2019
 *      Author: Nicolas
 *
 *      This file performs Space Vector modulation for calculating
 *      duty cycles from voltage references.
 */

#include "SVModulator.h"
#include "Constants.h"
#include "C28x_FPU_FastRTS.h"

void calculateDutyCycles(dqObject voltageReference)
{
    float Vdc = getDCLinkMeasurement();
    setVoltageLimits(voltageReference, Vdc);
}
void voltageLimits(dqObbject voltageReference, float Vdc)
{
    float weight = Vdc / SQRT3 * isqrt()
}

