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
float idReference = 0;
static struct
{
    PIobject IqController;
    PIobject IdController;
    PIobject SpeedController;
} PIControllerList;

void initPIControllers(void)
{
    PIObject_Constructor(&PIControllerList.IdController, KP_ID, KI_ID, 0, INCLUDE_SATURATION);
    PIObject_Constructor(&PIControllerList.IqController, KP_IQ, KI_IQ, 0, INCLUDE_SATURATION);
    PIObject_Constructor(&PIControllerList.SpeedController, KP_SPEED, KI_SPEED, 1, 0);
}

/*
 * Update PI parameters with updated PIRatio
 */
void updatePIRatio(float PIRatio)
{
    PIObjectUdatePIRatio(&PIControllerList.IdController, KP_ID, KI_ID, PIRatio);
    PIObjectUdatePIRatio(&PIControllerList.IqController, KP_IQ, KI_IQ, PIRatio);
    PIObjectUdatePIRatio(&PIControllerList.SpeedController, KP_SPEED, KI_SPEED, PIRatio);
}

/*
 * Interface functions to use PI controllers
 */
float PiCalculationIQ(float reference, float measuredValue)
{
    return PiCalculation(&PIControllerList.IqController, reference, measuredValue, PRINT_PI_DATA);
}

float PiCalculationID(float reference, float measuredValue)
{
    return PiCalculation(&PIControllerList.IdController, reference, measuredValue, DO_NOT_PRINT_PI_DATA);
}

float PiCalculationSpeed(float reference, int16 measuredValue)
{
    return PiCalculation(&PIControllerList.SpeedController, reference, (float)measuredValue, DO_NOT_PRINT_PI_DATA);
}


float getIdReference(void)
{
    if (idReference < D_CURRENT_REFERENCE_MAX)
    {
        idReference += deltaIdReference;
        return idReference;
    }
    else
        return D_CURRENT_REFERENCE_MAX;
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
    PIControllerList.IdController.previousOutput = 0;
    PIControllerList.IdController.previousLimitedOutput = 0;
}

void resetIqIntegrator(void)
{
    PIControllerList.IqController.integrationOfError = 0;
    PIControllerList.IqController.previousOutput = 0;
    PIControllerList.IqController.previousLimitedOutput = 0;
}

void resetSpeedIntegrator(void)
{
    PIControllerList.SpeedController.integrationOfError = 0;
    PIControllerList.SpeedController.previousOutput = 0;
    PIControllerList.SpeedController.previousLimitedOutput = 0;
}

float readIdReference(void)
{
    return idReference;
}
