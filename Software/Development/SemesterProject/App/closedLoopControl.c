/*
 * closedLoopControl.c
 *
 *  Created on: Apr 22, 2019
 *      Author:
 *
 *      testing Closed loop control file to avoid include lop during testing
 */



/*
 * temporary
 */
#include "signalGeneration.h"
#include "SVModulator.h"
#include "closedLoopControl.h"
#include "referenceFrameConversion.h"

void runClosedLoopControl(void)
{
    float ABCCurrent[3] = {0, 0, 0};
    static int sineIndex = 0;
    dqObject DQCurrent;
    alphaBetaObject abVoltage;

    getSineInstantValuesArray(sineIndex, &ABCCurrent[0], 19.6*1.41);
//    UARTIntPrint("s ", (int)(ABCCurrent[0]));

    DQCurrent = abc2dq(&ABCCurrent[0], getSineAngleInRads(sineIndex));
//    UARTIntPrint("D ", (int)(DQCurrent.dComponent*100));
//    UARTIntPrint("Q ", (int)(DQCurrent.qComponent*100));

//    voltageQRef = PICalculationIq(DQCurrent.QComponent);
    abVoltage = dq2alphabeta(&DQCurrent, getSineAngleInRads(sineIndex));
    sineIndex++;
    if (sineIndex > 1002) sineIndex = 0;
//    UARTIntPrint("af ", (int)(abVoltage.alphaComponent*100));
//    UARTIntPrint("be ", (int)(abVoltage.betaComponent*100));

//    GpioDataRegs.GPADAT.bit.GPIO18 = 0;
//    GpioDataRegs.GPADAT.bit.GPIO18 = 1;
//
//    abVoltage.alphaComponent = abVoltage.alphaComponent * 10;
//    abVoltage.betaComponent = abVoltage.betaComponent * 10;
    runSVM(abVoltage);
}
/*
 * end of temporary
 */
