/*
 * SVModulator.c
 *
 *  Created on: Apr 16, 2019
 *      Author: Nicolas
 *
 *      This file performs Space Vector modulation for calculating
 *      duty cycles from voltage references.
 *
 *      A voltage reference structured as alphaBetaObject is input and
 *      the module sets the appropriate duty cycles using dutyCycle.c interface.
 *
 *
 */

#include "SVModulator.h"

static t1t2Object (*t1t2Calculation[6]) (alphaBetaObject voltageRef);

void SVMInit(void)
{
    t1t2Calculation[0] = sector0Calculation;
    t1t2Calculation[1] = sector1Calculation;
    t1t2Calculation[2] = sector2Calculation;
    t1t2Calculation[3] = sector3Calculation;
    t1t2Calculation[4] = sector4Calculation;
    t1t2Calculation[5] = sector5Calculation;
}

/*
 * Highest level of abstraction function.
 * This function must be called from closedLoopControlMgr,
 * as an argument, the voltage reference must be of alphaBetaObject
 * data type.
 */
void runSVM(alphaBetaObject voltageRef)
{
    float Vdc;
    int sector;
    t1t2Object t1t2Struct;

    Vdc = getDCLinkMeasurement();
    voltageRef = limitVoltages(voltageRef, Vdc);
    sector = findSector(voltageRef);
    t1t2Struct = t1t2Calculation[sector](voltageRef);
    calculateAndSetDutyCycles(t1t2Struct);
}

alphaBetaObject limitVoltages(alphaBetaObject voltageRef, float Vdc)
{
    float weight = Vdc * ONE_DIV_SQRT3 * isqrt(voltageRef.alphaComponent * voltageRef.alphaComponent +
                                               voltageRef.betaComponent * voltageRef.betaComponent);
    float dlimit = fabs(voltageRef.alphaComponent * weight);

    float qlimit = fabs(voltageRef.betaComponent * weight);

    if (fabs(voltageRef.alphaComponent) > dlimit)  voltageRef.alphaComponent = 1.5 * signumf(voltageRef.alphaComponent) * dlimit / Vdc;
    else    voltageRef.alphaComponent = 1.5 * voltageRef.alphaComponent /Vdc;

    if (fabs(voltageRef.betaComponent) > qlimit)  voltageRef.betaComponent = 1.5 * signumf(voltageRef.betaComponent) * qlimit / Vdc;
    else    voltageRef.betaComponent = 1.5 * voltageRef.betaComponent /Vdc;

    return voltageRef;
}

void calculateAndSetDutyCycles(t1t2Object t1t2Struct)
{
    float temp = 0.5 - t1t2Struct.t1 - t1t2Struct.t2;
    float dutyA = 1 - temp;
    float dutyB = 1 - (temp + 2 * t1t2Struct.t1);
    float dutyC = temp;

    setDutyA(dutyA);
    setDutyB(dutyB);
    setDutyC(dutyC);
}

int findSector(alphaBetaObject voltageRef)
{
    // Sectors 0 and 1
    if (voltageRef.alphaComponent >= 0 && voltageRef.betaComponent >= 0)
    {
        if (voltageRef.betaComponent < SQRT3 * voltageRef.alphaComponent) return 0;
        else return 1;
    }

    // Sectors 2 and 1
    if (voltageRef.alphaComponent < 0 && voltageRef.betaComponent > 0)
    {
        if (voltageRef.betaComponent < SQRT3 * fabs(voltageRef.alphaComponent)) return 2;
        else return 1;
    }

    // Sectors 3 and 4
    if (voltageRef.alphaComponent < 0 && voltageRef.betaComponent <= 0)
    {
        if (fabs(voltageRef.betaComponent) <= SQRT3 * fabs(voltageRef.alphaComponent)) return 3;
        else return 4;
    }

    // Sectors 5 and 4
    if (voltageRef.alphaComponent >= 0 && voltageRef.betaComponent < 0)
    {
        if (fabs(voltageRef.betaComponent) <= SQRT3 * voltageRef.alphaComponent) return 5;
        else return 4;
    }
    return 0;
}

t1t2Object sector0Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;
    t1t2Struct.t1 = 0.5 * (voltageRef.alphaComponent - voltageRef.betaComponent * ONE_DIV_SQRT3);
    t1t2Struct.t2 = voltageRef.betaComponent * ONE_DIV_SQRT3;
    return t1t2Struct;
}

t1t2Object sector1Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;
    t1t2Struct.t1 = 0.5 * (-voltageRef.alphaComponent + voltageRef.betaComponent * ONE_DIV_SQRT3);
    t1t2Struct.t2 = 0.5 * (voltageRef.alphaComponent + voltageRef.betaComponent * ONE_DIV_SQRT3);
    return t1t2Struct;
}

t1t2Object sector2Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;
    t1t2Struct.t1 = 0.5 * (voltageRef.alphaComponent - voltageRef.betaComponent * ONE_DIV_SQRT3);
    t1t2Struct.t2 = voltageRef.betaComponent * ONE_DIV_SQRT3;
    return t1t2Struct;
}

t1t2Object sector3Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;
    t1t2Struct.t1 = 0.5 * (voltageRef.alphaComponent - voltageRef.betaComponent * ONE_DIV_SQRT3);
    t1t2Struct.t2 = voltageRef.betaComponent * ONE_DIV_SQRT3;
    return t1t2Struct;
}

t1t2Object sector4Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;
    t1t2Struct.t1 = 0.5 * (voltageRef.alphaComponent - voltageRef.betaComponent * ONE_DIV_SQRT3);
    t1t2Struct.t2 = voltageRef.betaComponent * ONE_DIV_SQRT3;
    return t1t2Struct;
}

t1t2Object sector5Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;
    t1t2Struct.t1 = 0.5 * (voltageRef.alphaComponent - voltageRef.betaComponent * ONE_DIV_SQRT3);
    t1t2Struct.t2 = voltageRef.betaComponent * ONE_DIV_SQRT3;
    return t1t2Struct;
}

/*
 * Return the sign of the variable
 */
int signumf(float variable)
{
    if      (variable > 0)  return 1;
    else if (variable < 0)  return -1;
    else                    return 0;
}

