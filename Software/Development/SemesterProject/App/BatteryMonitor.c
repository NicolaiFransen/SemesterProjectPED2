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
 *      The voltages are read by the analogAcquisitionManager and the output is controlled
 *      using the digital output manager.
 *
 *      As the AnalogAcquisitionManager is  not desired to be modified, an already created signal
 *      will be used. Those are:
 *         Top Cell -getDCLinkMeasurement(), mapped to ADC channel B4 (Launchpad J7, pin 64)
 *         Bottom Cell -getControlsupplyMeasurement(), mapped to ADC channel B6 (Launchpad J1, pin6)
 *
 *      The reaction uses the DigitalOutputManager and is mapped to GPIO16, (Launchpad J2, pin 15).
 *
 *      In order to reset the safety, a pushbutton must be added to the system. To manage that
 *      input, userACKHasBeenPressed() function from pushbuttonManager is used. That
 *      function analyses the pushbutton connected to GPIO25, (Launchpad J6, pin 54).
 */


#include "BatteryMonitor.h"

static CellsObject Supply8V;

void initBMS(void)
{
    Supply8V.BottomCell.status = NO_ERROR_BMS;
    Supply8V.TopCell.status = NO_ERROR_BMS;
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
    Supply8V.BottomCell.voltage = getControlsupplyMeasurement() * GAIN_BOTTOM_CELL ;
    Supply8V.TopCell.voltage = (getDCLinkMeasurement() * GAIN_TOP_CELL) - Supply8V.BottomCell.voltage;
}

void analyseCellVoltages(void)
{
    if (Supply8V.BottomCell.voltage > OVERVOLTAGE_THRESHOLD) Supply8V.BottomCell.status = OVERVOLTAGE;
    if (Supply8V.BottomCell.voltage < UNDERVOLTAGE_THRESHOLD) Supply8V.BottomCell.status = UNDERVOLTAGE;
    if (Supply8V.TopCell.voltage > OVERVOLTAGE_THRESHOLD) Supply8V.TopCell.status = OVERVOLTAGE;
    if (Supply8V.TopCell.voltage < UNDERVOLTAGE_THRESHOLD) Supply8V.TopCell.status = UNDERVOLTAGE;
}

void reactOnCellVoltages(void)
{
    if ((Supply8V.BottomCell.status != NO_ERROR_BMS) || (Supply8V.TopCell.status != NO_ERROR_BMS)) safetyReaction();
}

void safetyReaction(void)
{
    setLED10(ON);
}

void checkForResetAndEnableMainSwitch(void)
{
    if (userACKHasBeenPressed()) setLED10(OFF);
}
