/*
 * systemManager.h
 *
 *  Created on: Mar 4, 2019
 *      Author: Nicolas
 */

#ifndef APP_INCLUDE_SYSTEMMANAGER_H_
#define APP_INCLUDE_SYSTEMMANAGER_H_

//
// Objects declaration
//
typedef enum
{
    STARTUP,
    STANDBY,
    RUNNING,
    ERROR,
}SysMgrState;

//
// Function Prototypes statements for functions found within this file.
//
void manageSystem();
SysMgrState readSystemState();

#endif /* APP_INCLUDE_SYSTEMMANAGER_H_ */
