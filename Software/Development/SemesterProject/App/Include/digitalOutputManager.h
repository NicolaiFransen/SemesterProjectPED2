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
void setErrorLED(digitalOutputStatus state);
void setRunningLED(digitalOutputStatus state);
void setLED19(digitalOutputStatus state);
void setLED20(digitalOutputStatus state);
void setExtraLED1(digitalOutputStatus state);
void setExtraLED2(digitalOutputStatus state);
void setExtraLED3(digitalOutputStatus state);
void setExtraLED4(digitalOutputStatus state);
void setExtraLED5(digitalOutputStatus state);
void setExtraLED6(digitalOutputStatus state);
void setExtraLED7(digitalOutputStatus state);
void setExtraLED8(digitalOutputStatus state);

void setEnablePWM(digitalOutputStatus state);
void setExtraConnectorJ20(digitalOutputStatus state);
void setExtraConnectorJ21(digitalOutputStatus state);

// Get state functions
int getAntiSlipLEDState(void);
int getCruiseControlLEDState(void);
int getRegenerativeBrakingLEDState(void);
int getTorqueReferenceSliderLEDState(void);
int getTorqueReferencePedalLEDState(void);
int getTorqueReferenceUARTLEDState(void);
int getLED9State(void);
int getLED10State(void);
int getErrorLEDState(void);
int getRunningLEDState(void);
int getLED19State(void);
int getLED20State(void);
int getExtraLED1State(void);
int getExtraLED2State(void);
int getExtraLED3State(void);
int getExtraLED4State(void);
int getExtraLED5State(void);
int getExtraLED6State(void);
int getExtraLED7State(void);
int getExtraLED8State(void);

int getEnablePWMState(void);
int getExtraConnectorJ20State(void);
int getExtraConnectorJ21State(void);


#endif /* APP_INCLUDE_DIGITALOUTPUTMANAGER_H_ */
