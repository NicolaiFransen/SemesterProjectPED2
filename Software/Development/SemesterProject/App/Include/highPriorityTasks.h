/*
 * highPriorityTasks.h
 *
 *  Created on: 29. apr. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_HIGHPRIORITYTASKS_H_
#define APP_INCLUDE_HIGHPRIORITYTASKS_H_

// Includes
#include "analogAcquisitionManager.h"
#include "controlTask.h"
#include "positionCalculator.h"
#include "errorManager.h"
#include "DSP28x_Project.h"


__interrupt void adc_isr(void);

void executeHighPriorityTasks(void);
void acknowledgeAdcInterrupt(void);


#endif /* APP_INCLUDE_HIGHPRIORITYTASKS_H_ */
