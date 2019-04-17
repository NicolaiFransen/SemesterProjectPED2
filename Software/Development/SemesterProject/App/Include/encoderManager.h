/*
 * encoderManager.h
 *
 *  Created on: 1 abr. 2019
 *      Author: Aitor Teran
 */

#ifndef APP_ENCODERMANAGER_H_
#define APP_ENCODERMANAGER_H_

#include "DSP28x_Project.h"
#include "Constants.h"


typedef struct
{
    int32 thetaRaw;      // Raw angle, counter of steps in cycle (steps).
    int32 speedTempCount;  // Defines how often the values will be updated.

    int dir;             // rotor direction: 0=CCW/reverse, 1=CW/forward

    float thetaElecOld;  // Last rotor raw angle (rad).
    float thetaElec;     // rotor Electrical angle (rad).
    float thetaMech;     // rotor Mechanical Angle (rad).

    float freqElec;      // rotor Electrical freq [Hz]
    float freqMech;      // rotor Mechanical freq [Hz]

    int16 rpmMech;       // rotor revolutions per minute

} rotorPosSpeed;


void initEncoder(void);
void rotorPosSpeedConstructor(void);
void rotorPosCalc(void);
void rotorSpeedCalc(void);
float readRotorElecAngleRad(void);
float readRotorElecFreqHz(void);
float readRotorMechAngleRad(void);
float readRotorMechFreqHz(void);
int16 readRotorRPM(void);
void posSpeedFromEncoder(void);



#endif /* APP_ENCODERMANAGER_H_ */
