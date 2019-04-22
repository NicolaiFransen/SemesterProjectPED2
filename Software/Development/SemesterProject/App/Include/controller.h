/*
 * controller.h
 *
 *  Created on: 15. apr. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_CONTROLLER_H_
#define APP_INCLUDE_CONTROLLER_H_

//
// Includes
//
#include "Constants.h"
#include "PIController.h"

float calculateIdReference(void);
float calculateIqReference(float torqueReference);

/*
 * PI controllers
 */
void initPIControllers(void);
float PiCalculationIQ(float reference, float measuredValue);
float PiCalculationID(float reference, float measuredValue);
float PiCalcualtionSpeed(float reference, float measuredValue);



#endif /* APP_INCLUDE_CONTROLLER_H_ */
