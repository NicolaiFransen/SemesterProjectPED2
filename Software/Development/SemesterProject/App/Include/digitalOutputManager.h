/*
 * digitalOutputManager.h
 *
 *  Created on: 27. mar. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_DIGITALOUTPUTMANAGER_H_
#define APP_INCLUDE_DIGITALOUTPUTMANAGER_H_

#include "digitalOutput.h"

void initDigitalOutputs(void);
void setAntiSlipLED(LEDStatus state);
void setCruiseControlLED(LEDStatus state);
void setRegenerativeBrakingLED(LEDStatus state);
void setTorqueReferenceSliderLED(LEDStatus state);
void setTorqueReferencePedalLED(LEDStatus state);
void setTorqueReferenceUARTLED(LEDStatus state);
void setLed9(LEDStatus state);
void setLED10(LEDStatus state);
void setLED17(LEDStatus state);
void setLED18(LEDStatus state);
void setLED19(LEDStatus state);
void setLED20(LEDStatus state);
void setEnablePWM(LEDStatus state);

#endif /* APP_INCLUDE_DIGITALOUTPUTMANAGER_H_ */
