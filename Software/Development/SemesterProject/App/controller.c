/*
 * controller.c
 *
 *  Created on: 15. apr. 2019
 *      Author: Nicolai Fransen
 */

//
// Includes
//
#include "controller.h"

// Quasi-global variables definition
//
static struct
{
    PIobject IqController;
    PIobject IdController;
    PIobject SpeedController;
} PIControllerList;

void initPIControllers(void)
{
    PIObject_Constructor(&PIControllerList.IdController, KP_ID, KI_ID, CURRENT_LIMIT, 0);
    PIObject_Constructor(&PIControllerList.IqController, KP_IQ, KI_IQ, CURRENT_LIMIT, 0);
    PIObject_Constructor(&PIControllerList.SpeedController, KP_SPEED, KI_SPEED, SPEED_LIMIT, 1);
}

/*
 * Interface functions to use PI controllers
 */
float PiCalculationIQ(float reference, float measuredValue)
{
    return PiCalculation(&PIControllerList.IqController, reference, measuredValue);
}

float PiCalculationID(float reference, float measuredValue)
{
    return PiCalculation(&PIControllerList.IdController, reference, measuredValue);
}

float PiCalculationSpeed(float reference, int16 measuredValue)
{
    return PiCalculation(&PIControllerList.SpeedController, reference, (float)measuredValue);
}


float getIdReference(void)
{
    return D_CURRENT_REFERENCE;
}

float calculateIqReference(float torqueReference)
{
    return torqueReference * TORQUE_TO_Q_CURRENT;
}

/*
 * Function used to reset the integrators of the controllers.
 * Must be called every time the software leaves RUNNING state.
 */
void resetIntegrators(void)
{
    resetIdIntegrator();
    resetIqIntegrator();
    resetSpeedIntegrator();
}

void resetIdIntegrator(void)
{
    PIControllerList.IdController.integrationOfError = 0;
}

void resetIqIntegrator(void)
{
    PIControllerList.IqController.integrationOfError = 0;
}

void resetSpeedIntegrator(void)
{
    PIControllerList.SpeedController.integrationOfError = 0;
}
