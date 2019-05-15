/*
 * SVM_DMC.h
 *
 *  Created on: May 15, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_SVM_DMC_H_
#define APP_INCLUDE_SVM_DMC_H_

#include "svgen_dq.h"
#include "referenceFrameConversion.h"
#include "Constants.h"
#include "dutyCycle.h"


void runSVM_DMC(alphaBetaObject abVoltages);
void SVMInit_DMC(void);




#endif /* APP_INCLUDE_SVM_DMC_H_ */
