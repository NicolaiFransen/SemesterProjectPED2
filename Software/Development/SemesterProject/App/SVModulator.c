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
 *      This module is to be used by the closed loop control module. Its goal
 *      is to calculate the appropriate duty cycle depending upon the voltage
 *      reference calculated by the controller and the DC link voltage provided
 *      by the analogAcquisitionMgr.
 *
 *      The procedure is as follows:
 *          + Calculation of limited voltage
 *          + Determine space vector's sector
 *          + Calculate t1 and t2
 *          + Calculate duty cycles from t1 and t2
 *          + Set duty cycles
 */

#include "SVModulator.h"

static void (*t1t2Calculation[6]) (alphaBetaObject voltageRef);

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
    float Vdc, VdcInverse;
    int sector;

    Vdc = 100;   //getDCLinkMeasurement();
    VdcInverse = 0.01;  //getInverseOfDcLinkMeasurement();
    voltageRef = limitVoltages(voltageRef, Vdc, VdcInverse);
    sector = findSector(voltageRef);
    t1t2Calculation[sector](voltageRef);
}

/*
 * isqrt() is a function provided by fastRTS and approximates the inverse of the square root
 */
alphaBetaObject limitVoltages(alphaBetaObject voltageRef, float Vdc, float VdcInverse)
{
    float weight = Vdc * ONE_DIV_SQRT3 * isqrt(voltageRef.alphaComponent * voltageRef.alphaComponent +
                                               voltageRef.betaComponent * voltageRef.betaComponent);
    float dlimit = fabs(voltageRef.alphaComponent * weight);

    float qlimit = fabs(voltageRef.betaComponent * weight);

    if (fabs(voltageRef.alphaComponent) > dlimit)  voltageRef.alphaComponent = 1.5 * signumf(voltageRef.alphaComponent) * dlimit * VdcInverse;
    else    voltageRef.alphaComponent = 1.5 * voltageRef.alphaComponent * VdcInverse;

    if (fabs(voltageRef.betaComponent) > qlimit)  voltageRef.betaComponent = 1.5 * signumf(voltageRef.betaComponent) * qlimit * VdcInverse;
    else    voltageRef.betaComponent = 1.5 * voltageRef.betaComponent * VdcInverse;

    return voltageRef;
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

void sector0Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;
    t1t2Struct.t1 = 0.5 * (voltageRef.alphaComponent - voltageRef.betaComponent * ONE_DIV_SQRT3);
    t1t2Struct.t2 = voltageRef.betaComponent * ONE_DIV_SQRT3;

    float temp = 0.5 - t1t2Struct.t1 - t1t2Struct.t2;
    float dutyA = 1 - temp;
    float dutyB = 1 - (temp + 2 * t1t2Struct.t1);
    float dutyC = temp;

    setDutyA(dutyA * 100);
    setDutyB(dutyB * 100);
    setDutyC(dutyC * 100);
}

void sector1Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;

    t1t2Struct.t1 = 0.5 * (-voltageRef.alphaComponent + voltageRef.betaComponent * ONE_DIV_SQRT3);
    t1t2Struct.t2 = 0.5 * (voltageRef.alphaComponent + voltageRef.betaComponent * ONE_DIV_SQRT3);

    float temp = 0.5 - t1t2Struct.t1 - t1t2Struct.t2;
    float dutyB = 1 - temp;
    float dutyA = 1 - (temp + 2 * t1t2Struct.t1);
    float dutyC = temp;

    setDutyA(dutyA * 100);
    setDutyB(dutyB * 100);
    setDutyC(dutyC * 100);
}

void sector2Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;

    t1t2Struct.t1 = voltageRef.betaComponent * ONE_DIV_SQRT3;
    t1t2Struct.t2 = 0.5 * (fabs(voltageRef.alphaComponent) - voltageRef.betaComponent * ONE_DIV_SQRT3);

    float temp = 0.5 - t1t2Struct.t1 - t1t2Struct.t2;
    float dutyB = 1 - temp;
    float dutyC = 1 - (temp + 2 * t1t2Struct.t1);
    float dutyA = temp;

    setDutyA(dutyA * 100);
    setDutyB(dutyB * 100);
    setDutyC(dutyC * 100);
}

void sector3Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;

    t1t2Struct.t1 = fabs(voltageRef.betaComponent * ONE_DIV_SQRT3);
    t1t2Struct.t2 = 0.5 * (fabs(voltageRef.alphaComponent) - fabs(voltageRef.betaComponent) * ONE_DIV_SQRT3);

    float temp = 0.5 - t1t2Struct.t1 - t1t2Struct.t2;
    float dutyC = 1 - temp;
    float dutyB = 1 - (temp + 2 * t1t2Struct.t1);
    float dutyA = temp;

    setDutyA(dutyA * 100);
    setDutyB(dutyB * 100);
    setDutyC(dutyC * 100);
}

void sector4Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;

    t1t2Struct.t1 = 0.5 * (- voltageRef.alphaComponent + fabs(voltageRef.betaComponent) * ONE_DIV_SQRT3);
    t1t2Struct.t2 = 0.5 * (voltageRef.alphaComponent + fabs(voltageRef.betaComponent) * ONE_DIV_SQRT3);

    float temp = 0.5 - t1t2Struct.t1 - t1t2Struct.t2;
    float dutyC = 1 - temp;
    float dutyA = 1 - (temp + 2 * t1t2Struct.t1);
    float dutyB = temp;

    setDutyA(dutyA * 100);
    setDutyB(dutyB * 100);
    setDutyC(dutyC * 100);
}

void sector5Calculation(alphaBetaObject voltageRef)
{
    t1t2Object t1t2Struct;

    t1t2Struct.t1 = 0.5 * (voltageRef.alphaComponent - fabs(voltageRef.betaComponent) * ONE_DIV_SQRT3);
    t1t2Struct.t2 = fabs(voltageRef.betaComponent * ONE_DIV_SQRT3);

    float temp = 0.5 - t1t2Struct.t1 - t1t2Struct.t2;
    float dutyA = 1 - temp;
    float dutyC = 1 - (temp + 2 * t1t2Struct.t1);
    float dutyB = temp;

    setDutyA(dutyA * 100);
    setDutyB(dutyB * 100);
    setDutyC(dutyC * 100);
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

