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
#include "referenceHandler.h"


#define ANTI_WINDUP_ENABLED     1
#define ANTI_WINDUP_DISABLED    0

/*
 * PI controllers
 */
void initPIControllers(void);
void updatePIRatio(float PIRatio);
float PiCalculationIQ(float reference, float measuredValue);
float PiCalculationID(float reference, float measuredValue);
float PiCalculationSpeed(float reference, int16 measuredValue);
void resetIntegrators(void);
void resetIdIntegrator(void);
void resetIqIntegrator(void);
void resetSpeedIntegrator(void);

#endif /* APP_INCLUDE_CONTROLLER_H_ */
