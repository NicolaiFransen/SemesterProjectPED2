/*
 * adcMonitor.h
 *
 *  Created on: 28. mar. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_ADCMONITOR_H_
#define APP_INCLUDE_ADCMONITOR_H_

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "analogAcquisitionManager.h"

typedef enum
{
    NO_ERROR,
    ERROR_HAS_HAPPENED,
    IDLE
} errorStatus;
//
// Function prototyping
//
errorStatus areAdcMeasurementsWithinThresholds(void);
errorStatus areBatteryMeasurementsWithinThresholds(void);
errorStatus areCurrentMeasurementsWithinThresholds(void);

#endif /* APP_INCLUDE_ADCMONITOR_H_ */
