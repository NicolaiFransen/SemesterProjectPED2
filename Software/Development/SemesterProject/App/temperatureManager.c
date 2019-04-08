/*
 * temperatureManager.c
 *
 *  Created on: Apr 8, 2019
 *      Author: Nicolas
 *
 *      The temperature manager is a module that obtains the voltage measurement
 *      from the analogAcquisitionManager  and calculates the temperature of the sensor.
 *      It also provides an interface for external access to the temperature.
 *
 *      calculateTemperature is called every second from the scheduler.
 *
 *      The temperature sensors were not unified in a higher level of abstraction
 *      structure because the number of sensors is two and it not likely to change.
 */

#include "temperatureManager.h"

/*
 * Temperature sensor gain in Volts/degC
 */
#define TEMPERATURE_SENSOR_GAIN 0.01

/*
 * Quasi Global variable definition
 */
static float S1Temperature = 0, S2Temperature = 0;

void calculateTemperature(void) //To be called from scheduler when reference handler is merged
{
    float voltageSensor1;
    voltageSensor1 = getThermometer1Measurement();
    S1Temperature = voltageSensor1 / TEMPERATURE_SENSOR_GAIN;

    float voltageSensor2;
    voltageSensor2 = getThermometer2Measurement();
    S2Temperature = voltageSensor2 / TEMPERATURE_SENSOR_GAIN;
}

/*
 * External Interfaces
 */

float getSensor1Temperature(void)
{
    return S1Temperature;
}

float getSensor2Temperature(void)
{
    return S2Temperature;
}


