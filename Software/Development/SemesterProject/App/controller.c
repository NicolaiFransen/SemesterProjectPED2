/*
 * controller.c
 *
 *  Created on: 15. apr. 2019
 *      Author: Nicolai Fransen
 */

//
// Includes
//
#include "controller.h"

float calculateIdReference(void)
{
    return D_CURRENT_REFERENCE;
}

float calculateIqReference(float torqueReference)
{
    return torqueReference * TORQUE_TO_Q_CURRENT;
}
