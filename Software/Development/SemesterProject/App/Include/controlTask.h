/*
 * controlTask.h
 *
 *  Created on: 22. mar. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_CONTROLTASK_H_
#define APP_INCLUDE_CONTROLTASK_H_

#include "digitalInputManager.h"
#include "dutyCycle.h"

//
// Function definition
//
void executeControl(void);
void disableDutyCycles(void);
int isOpenLoopControlSelected(void);

#endif /* APP_INCLUDE_CONTROLTASK_H_ */
