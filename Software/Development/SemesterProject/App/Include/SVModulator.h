
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


typedef struct
{
    float t1;
    float t2;
} t1t2Object;

/*
 * Temporary stuff to bee removed
 */
typedef struct
{
    float alphaComponent;
    float betaComponent;
}alphaBetaObject;
/*
 * end of temporary stuff
 */

void SVMInit(void);
void runSVM(alphaBetaObject voltageRef);
alphaBetaObject limitVoltages(alphaBetaObject voltageRef, float Vdc);
void calculateAndSetDutyCycles(t1t2Object t1t2Struct);
int findSector(alphaBetaObject voltageRef);
t1t2Object sector0Calculation(alphaBetaObject voltageRef);
t1t2Object sector1Calculation(alphaBetaObject voltageRef);
t1t2Object sector2Calculation(alphaBetaObject voltageRef);
t1t2Object sector3Calculation(alphaBetaObject voltageRef);
t1t2Object sector4Calculation(alphaBetaObject voltageRef);
t1t2Object sector5Calculation(alphaBetaObject voltageRef);
int signumf(float variable);


#endif /* APP_INCLUDE_SVMODULATOR_H_ */
