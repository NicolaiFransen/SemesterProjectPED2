/*
 * highPriorityTasks.c
 *
 *  Created on: 29. apr. 2019
 *      Author: Nicolai Fransen
 *
 *      This file execute all the high priority functions, after the interrupt
 *      from the ADCs has been triggered
 */

#include "highPriorityTasks.h"

void executeHighPriorityTasks(void)
{
    getRotorPosSpeedParameters();       // Update speed measurement
    executeControl();                   // Executes the selected control type
    performErrorMonitoring();           // Monitors the system for errors
}



/*
 * This interrupt is called every time the ADC registers have been updated.
 */
__interrupt void adc_isr(void)
{
    readHighPrioritySignals();

    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

    executeHighPriorityTasks();

    return;
}
