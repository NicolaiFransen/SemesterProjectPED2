/*
 * PIController.h
 *
 *  Created on: 2. apr. 2019
 *      Author: Nicolai Fransen
 */

#ifndef APP_INCLUDE_PICONTROLLER_H_
#define APP_INCLUDE_PICONTROLLER_H_


typedef struct PIobjectTag
{
    int KP;
    int KI;
} PIobject;

void PIObject_Constructor(PIobject *PI, int KP, int KI);
void initPIControllers(void);
float PiCalculation(PIobject *PI, int errors[]);

#endif /* APP_INCLUDE_PICONTROLLER_H_ */
