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
    ADC_ERROR,
    NO_ADC_ERROR,
    IDLE
} error;
//
// Function prototyping
//
error areAdcMeasurementsWithinThresholds(void);
error areBatteryMeasurementsWithinThresholds(void);
error areCurrentMeasurementsWithinThresholds(void);

#endif /* APP_INCLUDE_ADCMONITOR_H_ */
