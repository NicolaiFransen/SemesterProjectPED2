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

#define ENCODER_STEPS 2048
#define ENCODER_STEPS_INVERSE ((float)(1.0 / ENCODER_STEPS))
#define BASE_FREQ 50        //us


typedef struct
{
    int32 thetaRaw;      // Raw angle, counter of steps in cycle (steps).
    int poles;           // Number of poles of the motor.
    int32 speedTempCount;  // Defines how often the values will be updated.

    int dir;             // Motor direction: 0=CCW/reverse, 1=CW/forward

    float thetaElecOld;  // Last motor raw angle (rad).
    float thetaElec;     // Motor Electrical angle (rad).
    float thetaMech;     // Motor Mechanical Angle (rad).

    float freqElec;      // Motor Electrical freq [Hz]
    float freqMech;      // Motor Mechanical freq [Hz]

    int16 rpmMech;       // Motor revolutions per minute

} motorPosSpeed;


void initEncoder(void);
void motorPosSpeedConstructor(void);
void motorPosCalc(void);
void motorSpeedCalc(void);
int16 readRotorElecAngle(void);
float readRotorElecFreq(void);
int16 readRotorMechAngle(void);
float readRotorMechFreq(void);
int16 readRotorRPM(void);
void posSpeedFromEncoder(void);



#endif /* APP_ENCODERMANAGER_H_ */
