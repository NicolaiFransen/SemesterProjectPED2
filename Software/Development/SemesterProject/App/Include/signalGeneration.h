/*
 * signalGeneration.h
 *
 *  Created on: Apr 17, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_SIGNALGENERATION_H_
#define APP_INCLUDE_SIGNALGENERATION_H_

#include "queueObject.h"
#include "Constants.h"

void getSineInstantValuesArray(int index, float *sineArray);
float getSineAngleInRads(int index);
int indexPlus2PiThirds(int index);
int indexPlus4PiThirds(int index);

#endif /* APP_INCLUDE_SIGNALGENERATION_H_ */
