/*
 * PIController.c
 *
 *  Created on: 2. apr. 2019
 *      Author: Nicolai Fransen
 */

//
// Includes
//
#include "PIController.h"
#include "DSP28x_Project.h"

//
// Quasi-global variables definition
//


static struct
{
    PIobject IqController;
    PIobject IdController;
    PIobject TorqueController;
} PIControllerList;

void PIObject_Constructor(PIobject *PIcontroller, int KP, int KI)
{
    PIcontroller->KP = KP;
    PIcontroller->KI = KI;
}

void initPIControllers(void)
{
    PIObject_Constructor(&PIControllerList.IdController, 10, 10);
    PIObject_Constructor(&PIControllerList.IdController, 10, 10);
    PIObject_Constructor(&PIControllerList.TorqueController, 10, 10);
}

float PiCalculation(PIobject *PIcontroller, int errors[])
{
    int KP = PIcontroller->KP;
    int KI = PIcontroller->KI;
    int arrayPosition;
    float output = 0, sumOfErrors = 0;

    for (arrayPosition = 0; arrayPosition < sizeof(errors); arrayPosition++)
        sumOfErrors = sumOfErrors + errors[arrayPosition];

    output = KP*errors[0] + KI*sumOfErrors;

    return output;
}
