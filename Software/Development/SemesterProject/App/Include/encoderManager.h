/*
 * encoderManager.h
 *
 *  Created on: 1 abr. 2019
 *      Author: Aitor Teran
 */

#ifndef APP_ENCODERMANAGER_H_
#define APP_ENCODERMANAGER_H_

#include "DSP28x_Project.h"

#define ENCODER_STEPS 100
#define ENCODER_INT_FREQ 200 //5ms period for reading encoder (200Hz).
typedef struct
{
    int32 thetaRaw;     // Raw angle, counter of steps in cycle
    int32 offsetTheta;  // Offset between index and phase

    int16 stepsPerCycle;

    int dir;            // Motor direction: 0=CCW/reverse, 1=CW/forward

    int32 thetaElecOld;  // Last motor raw angle, not necessary because Xdelta is saved inside the module (QPOSLAT).
    int16 thetaElec;    // Motor Electrical angle, current electrical angle of the motor
    int16 thetaMech;    // Motor Mechanical Angle, current mechanical angle of the motor

    float freqElec;     // Motor Electrical freq [Hz]
    int poles;          // Number of poles of the motor.
    float freqMech;     // Motor Mechanical freq [Hz]

    int16 rpmMech;      // Motor revolutions per minute

} motorPosSpeed;


int16 readRotorElecAngle(void);
float readRotorElecFreq(void);
int16 readRotorMechAngle(void);
float readRotorMechFreq(void);
int16 readRotorRPM(void);
void posSpeedFromEncoder(void);



#endif /* APP_ENCODERMANAGER_H_ */
