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
 * Quasi Global variable definition
 */
static float sensor1Temp = 0, sensor2Temp = 0;

void calculateTemperature(void) //To be called from scheduler when reference handler is merged
{
    float voltageSensor1;
    float voltageSensor2;

    voltageSensor1 = getThermometer1Measurement();
    sensor1Temp = voltageSensor1 * TEMP_SENSOR_DEG_PER_VOLT;

    voltageSensor2 = getThermometer2Measurement();
    sensor2Temp = voltageSensor2 * TEMP_SENSOR_DEG_PER_VOLT;
}

/*
 * External Interfaces
 */

float getSensor1Temperature(void)
{
    return sensor1Temp;
}

float getSensor2Temperature(void)
{
    return sensor2Temp;
}


