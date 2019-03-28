/*
 * digitalOutputManager.h
 *
 *  Created on: 27. mar. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_DIGITALOUTPUTMANAGER_H_
#define APP_INCLUDE_DIGITALOUTPUTMANAGER_H_

#include "digitalOutput.h"

// Init function
void initDigitalOutputs(void);

// Set state functions
void setAntiSlipLED(digitalOutputStatus state);
void setCruiseControlLED(digitalOutputStatus state);
void setRegenerativeBrakingLED(digitalOutputStatus state);
void setTorqueReferenceSliderLED(digitalOutputStatus state);
void setTorqueReferencePedalLED(digitalOutputStatus state);
void setTorqueReferenceUARTLED(digitalOutputStatus state);
void setLED9(digitalOutputStatus state);
void setLED10(digitalOutputStatus state);
void setLED17(digitalOutputStatus state);
void setLED18(digitalOutputStatus state);
void setLED19(digitalOutputStatus state);
void setLED20(digitalOutputStatus state);
void setEnablePWM(digitalOutputStatus state);

// Get state functions
int getAntiSlipLEDState(void);
int getCruiseControlLEDState(void);
int getRegenerativeBrakingLEDState(void);
int getTorqueReferenceSliderLEDState(void);
int getTorqueReferencePedalLEDState(void);
int getTorqueReferenceUARTLEDState(void);
int getLED9State(void);
int getLED10State(void);
int getLED17State(void);
int getLED18State(void);
int getLED19State(void);
int getLED20State(void);
int getEnablePWMState(void);


#endif /* APP_INCLUDE_DIGITALOUTPUTMANAGER_H_ */
