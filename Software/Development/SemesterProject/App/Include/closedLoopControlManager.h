/*
 * closedLoopControlManager.h
 *
 *  Created on: 25. apr. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_CLOSEDLOOPCONTROLMANAGER_H_
#define APP_INCLUDE_CLOSEDLOOPCONTROLMANAGER_H_

// Includes
//#include "controller.h"
//#include "SVModulator.h
#include "referenceFrameConversion.h"
#include "referenceHandler.h"
#include "positionCalculator.h"
#include "analogAcquisitionManager.h"


// Functions
void runClosedLoopControl(void);

float getMovementReference(void);
float getIqReference(float movementReference);
int torqueControlIsSelected(void);

void resetControlVariables(void);

#endif /* APP_INCLUDE_CLOSEDLOOPCONTROLMANAGER_H_ */
