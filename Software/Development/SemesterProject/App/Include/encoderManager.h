/*
 * encoderManager.h
 *
 *  Created on: 1 abr. 2019
 *      Author: Aitor Teran
 */

#ifndef APP_ENCODERMANAGER_H_
#define APP_ENCODERMANAGER_H_

#include "DSP28x_Project.h"

typedef enum
{
    UP,
    DOWN,
    STATIC,
}motorDirection;


typedef struct
{
    int counterRaw;     // Variable: Raw encoder counter index. Counts the number of steps in the cycle
    int16 thetaRaw;     // Variable: Raw angle, accumulates raw counters
    int16 oldThetaRaw;  // Input: Last motor raw angle

    motorDirection dir; // Output: Motor rotation direction

    int16 thetaElec;    // Output: Motor Electrical angle, current electrical angle of the motor
    int16 thetaMech;    // Output: Motor Mechanical Angle, current mechanical angle of the motor

    float freqElec;     // Output: Motor Electrical speed [Hz]
    float freqMech;     // Output: Motor Mechanical speed [Hz]

    int16 rpmMech;      // Output: Motor revolutions per minute

} motorPosSpeed;



#endif /* APP_ENCODERMANAGER_H_ */
