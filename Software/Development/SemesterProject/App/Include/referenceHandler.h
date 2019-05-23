/*
 * referenceHandler.h
 *
 *  Created on: Mar 27, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_REFERENCEHANDLER_H_
#define APP_INCLUDE_REFERENCEHANDLER_H_

#include "communicationManager.h"
#include "analogAcquisitionManager.h"
#include "AnalogSignal.h"
#include "pushButtonManager.h"
#include "systemManager.h"
#include "positionCalculator.h"
#include "controller.h"

#define MAX_TORQUE_REF_NM           30
#define MAXIMUM_SPEED_REF_RPM       1685
#define SPEED_STEP_FROM_BUTTON_KPH  5
#define GEAR_RATIO                  1.66
#define RADIUS_WHEELS               0.137
#define referenceHandlerPeriodicity 0.001    //seconds




typedef enum
{
    interfacePCB,
    goKart,
    GUI,
    lastIndexRS
} referenceSourceTag;

enum referenceTypeTag
{
    torqueControl,
    cruiseControl,
    lastIndexRT
};

void handleReferences(void);
void decideReferenceType(void);
int referenceTypeIsChanged(void);
void decideReferenceSource(void);
int referenceSourceIsChanged(void);
void calculateReference(void);
void calculateTorqueReference(void);
    float getReferenceValue(void);
    float CalculateTorqueRefFromAnalog(float analogRead);
    float calculateLimitedTorqueReference(float torqueReferenceBeforeLimit);
    int referenceIncreased(float torqueReferenceBeforeLimit);
    int referenceDecreased(float torqueReferenceBeforeLimit);
    float calculateSaturatedTorque(float torqueBeforeSaturation);
void calculateSpeedReference(void);
    int speedMustBeIncreased(void);
    int speedMustBeDecreased(void);
    int getSpeedReferenceValue(void);
    int calculateLimitedSpeedReference(int speedReferenceBeforeLimit);
    int speedRefIncreased(int speedReferenceBeforeLimit);
    int speedRefDecreased(int speedReferenceBeforeLimit);
    int calculateSaturatedSpeed(int speedReferenceBeforeSaturation);
    void restartSpeedReference(void);
void restartReferences(void);


/*
 * External Interfaces
 */
float getTorqueReference(void);
float getIqReferenceTorqueControl(void);
float getSpeedReference(void);
float getOpenLoopReference(void);
int torqueControlIsEnabled(void);
referenceSourceTag getReferenceSource(void);
int referenceSourceHasChanged(void);
void setSpeedRamp(int rampRPMperSec);
void setTorqueRamp(int rampNmperSec);


#endif /* APP_INCLUDE_REFERENCEHANDLER_H_ */
