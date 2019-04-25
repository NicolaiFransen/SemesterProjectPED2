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
    sensor1Temp = getThermometer1Measurement();
    sensor2Temp = getThermometer2Measurement();
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


