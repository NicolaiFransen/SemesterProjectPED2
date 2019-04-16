/*
 * controller.h
 *
 *  Created on: 15. apr. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_CONTROLLER_H_
#define APP_INCLUDE_CONTROLLER_H_

//
// Includes
//
#include "Constants.h"

float calculateIdReference(void);
float calculateIqReference(float torqueReference);

#endif /* APP_INCLUDE_CONTROLLER_H_ */
