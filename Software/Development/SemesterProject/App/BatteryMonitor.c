/*
 * BatteryMonitor.c
 *
 *  Created on: Dec 2, 2019
 *      Author: Nicolas
 *
 *      The goal of this module is to monitor  that the voltage of n battery cells is within safe
 *      margins. For that, both the undervoltage and the overvoltage margins are considered. When
 *      the voltages are appropriate, a power switch is enabled to allow current flow.
 *
 *      The voltages are read by the analogAcquisitionManager and the output is controlled by
 *      using the digital output manager.
 *
 *      As the AnalogAcquisitionManager is  not desired to be modified, an already created signal
 *      will be used. Those are:
 *          -getDCLinkMeasurement(), mapped to ADC channel B4
 *          -getControlsupplyMeasurement(), mapped to ADC channel B6
 *
 *      The reaction uses the DigitalOutputManager and is mapped to J20 or pin 10.
 *
 *      In order to reset the safety, a pushbutton must be added to the system. To manage that
 *      input, userACKHasBeenPressed() function from pushbuttonManager is used. That
 *      function analyses the pushbutton connected to J12 or pin 25.
 */


#include "BatteryMonitor.h"

static CellsObject Supply8V;

void initBMS(void)
{
    Supply8V.Cell1.status = NO_ERROR_BMS;
    Supply8V.Cell2.status = NO_ERROR_BMS;
}

void MonitorBattery(void)
{
    getCellVoltages();
    analyseCellVoltages();
    reactOnCellVoltages();
    checkForResetAndEnableMainSwitch();
}

void getCellVoltages(void)
{
    Supply8V.Cell1.voltage = getDCLinkMeasurement();
    Supply8V.Cell2.voltage = getDCLinkMeasurement();
}

void analyseCellVoltages(void)
{
    if (Supply8V.Cell1.voltage > OVERVOLTAGE_THRESHOLD) Supply8V.Cell1.status = OVERVOLTAGE;
    if (Supply8V.Cell1.voltage < UNDERVOLTAGE_THRESHOLD) Supply8V.Cell1.status = UNDERVOLTAGE;
    if (Supply8V.Cell2.voltage > OVERVOLTAGE_THRESHOLD) Supply8V.Cell1.status = OVERVOLTAGE;
    if (Supply8V.Cell2.voltage < UNDERVOLTAGE_THRESHOLD) Supply8V.Cell1.status = UNDERVOLTAGE;
}

void reactOnCellVoltages(void)
{
    if ((Supply8V.Cell1.status != NO_ERROR_BMS) || (Supply8V.Cell2.status != NO_ERROR_BMS)) safetyReaction();
}

void safetyReaction(void)
{
    setExtraConnectorJ20(OFF);
}

void checkForResetAndEnableMainSwitch(void)
{
    if (userACKHasBeenPressed()) setExtraConnectorJ20(ON);
}
