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
#include "DSP28x_Project.h"

float getIdReference(void);
float calculateIqReference(float torqueReference);

/*
 * PI controllers
 */
void initPIControllers(void);
float PiCalculationIQ(float reference, float measuredValue);
float PiCalculationID(float reference, float measuredValue);
float PiCalcualtionSpeed(float reference, int16 measuredValue);
void resetIntegrators(void);
void resetIdIntegrator(void);
void resetIqIntegrator(void);
void resetSpeedIntegrator(void);



#endif /* APP_INCLUDE_CONTROLLER_H_ */
