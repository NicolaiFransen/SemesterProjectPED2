/*
 * BatteryMonitor.h
 *
 *  Created on: Dec 2, 2019
 *      Author: Nicolas
 */

#ifndef APP_BATTERYMONITOR_H_
#define APP_BATTERYMONITOR_H_

//Includes
#include "digitalOutputManager.h"
#include "analogAcquisitionManager.h"
#include "pushButtonManager.h"


//Prototypes
void MonitorBattery(void);
void initBMS(void);
void MonitorBattery(void);
void getCellVoltages(void);
void analyseCellVoltages(void);
void reactOnCellVoltages(void);
void safetyReaction(void);
void checkForResetAndEnableMainSwitch(void);

//Defines and type definition
#define OVERVOLTAGE_THRESHOLD 4.08
#define UNDERVOLTAGE_THRESHOLD 2.9
#define GAIN_BOTTOM_CELL 2
#define GAIN_TOP_CELL 2.65

typedef enum VoltageErrorTag
{
    NO_ERROR_BMS,
    UNDERVOLTAGE,
    OVERVOLTAGE
}VoltageError;

typedef struct CellTag
{
    float voltage;
    VoltageError status;
} Cell;

typedef struct CellsObjectTag
{
    Cell TopCell;
    Cell BottomCell;
} CellsObject;


#endif /* APP_BATTERYMONITOR_H_ */
