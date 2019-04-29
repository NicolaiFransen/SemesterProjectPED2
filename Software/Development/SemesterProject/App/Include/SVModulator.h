
/*
 * SVModulator.h
 *
 *  Created on: Apr 16, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_SVMODULATOR_H_
#define APP_INCLUDE_SVMODULATOR_H_

#include "dutyCycle.h"
#include "Constants.h"
#include "C28x_FPU_FastRTS.h"
#include "analogAcquisitionManager.h"
#include "referenceFrameConversion.h"


typedef struct
{
    float t1;
    float t2;
} t1t2Object;

void SVMInit(void);
void runSVM(alphaBetaObject voltageRef);
alphaBetaObject limitVoltages(alphaBetaObject voltageRef, float Vdc);
int findSector(alphaBetaObject voltageRef);
void sector0Calculation(alphaBetaObject voltageRef);
void sector1Calculation(alphaBetaObject voltageRef);
void sector2Calculation(alphaBetaObject voltageRef);
void sector3Calculation(alphaBetaObject voltageRef);
void sector4Calculation(alphaBetaObject voltageRef);
void sector5Calculation(alphaBetaObject voltageRef);
int signumf(float variable);


#endif /* APP_INCLUDE_SVMODULATOR_H_ */
