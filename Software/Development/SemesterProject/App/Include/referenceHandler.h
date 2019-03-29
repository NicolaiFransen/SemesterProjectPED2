/*
 * referenceHandler.h
 *
 *  Created on: Mar 27, 2019
 *      Author: alumn
 */

#ifndef APP_INCLUDE_REFERENCEHANDLER_H_
#define APP_INCLUDE_REFERENCEHANDLER_H_

#include "communicationManager.h"
#include "analogAcquisitionManager.h"
#include "AnalogSignal.h"
//#include "pushButtonManager.h"            TO BE ADDED AFTER PUSHBUTTONmGR IS MERGED

#define MAX_TORQUE_REF_NM       30
#define MAXIMUM_SPEED_REF_RPM   1685
#define SPEED_STEP_FROM_BUTTON     50

enum referenceSourceTag
{
    interfacePCB,
    GUI,
    goKart,
    lastIndexRS
};

enum referenceTypeTag
{
    torqueControl,
    cruiseControl,
    lastIndexRT
};

void decideReferenceType(void);
int referenceTypeIsChanged(void);
void decideReferenceSource(void);
int referenceSourceIsChanged(void);
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


/*
 * External Interfaces
 */
float getTorqueReference(void);
float getSpeedReference(void);
float getOpenLoopReference(void);
int torqueControlIsEnabled(void);

#endif /* APP_INCLUDE_REFERENCEHANDLER_H_ */
