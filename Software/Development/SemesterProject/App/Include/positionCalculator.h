/*
 * PositionCalculator.h
 *
 *  Created on: 17 abr. 2019
 *      Author: Aitor Teran
 */

#ifndef APP_INCLUDE_POSITIONCALCULATOR_H_
#define APP_INCLUDE_POSITIONCALCULATOR_H_

#include "DSP28x_Project.h"
#include "Constants.h"
#include "referenceHandler.h"


typedef struct
{
    //ROTOR RELATED PARAMETERS
    int32 rotorThetaRaw;      // Raw angle, counter of steps in cycle (steps).
    int32 rotorSpeedTempCount;  // Defines how often the values will be updated.

    int dir;             // rotor direction: 0=CCW/reverse, 1=CW/forward

    float rotorThetaElecOld;  // Last rotor raw angle (rad).
    float rotorThetaElec;     // rotor Electrical angle (rad).
    float rotorThetaMech;     // rotor Mechanical Angle (rad).

    float rotorSpeedRadS;     // rotor Electrical speed [rad/s]

    //SLIP RELATED PARAMETERS
    float slipAngleRad;
    float rotorFluxPosRad;
    float slipSpeedRadS;
    float rotorFluxSpeedRadS;

} motorPosSpeed;


//Functions related to positionCalculator.c
void posSpeedFromEncoder();
void rotorFluxPosSpeed();

void getRotorPosSpeedParameters();

void rotorPosSpeedConstructor(void);

float readRotorElecAngleRad(void);
float readRotorElecFreqHz(void);
float readRotorSpeedRadS(void);
float readRotorMechAngleRad(void);
float readRotorMechFreqHz(void);
int16 readRotorRPM(void);
int readRotorThetaRaw(void);

//Functions related to encoderManager.c
void initEncoder(void);
void clearInterruptFlag(void);
void rotorPosCalc(motorPosSpeed *);
void rotorSpeedCalc(motorPosSpeed *);

//Functions related to positionCalculator.c
float readRotorFluxAngleRad(void);
float readRotorFluxSpeedRadS(void);
void calcSlipSpeed(motorPosSpeed *);
void calcSlipAngle(motorPosSpeed *);

#endif /* APP_INCLUDE_POSITIONCALCULATOR_H_ */
