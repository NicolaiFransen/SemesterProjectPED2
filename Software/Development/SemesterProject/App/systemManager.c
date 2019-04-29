//###########################################################################
//FILE: systemManager.c
//
//Project: Electric Go-kart
//
//Author: Nicolas Murguizur, 3/3/19
//
//Notes:
//      System's state FSM is included in this file. More details about
//      might be found in the detailed class description:
//      SemesterProjectPED2\Software\Design\SystemArchitectureDescription.pdf
//
//###########################################################################

//###########################################################################

//
// Included Files
//
#include "Include/systemManager.h"


//
// Quasi-global variables definition
//
static SysMgrState systemState = STARTUP;


void manageSystem(void)
{
    // Switch LEDs off
    setRunningLED(OFF);

    switch (systemState)
    {
        case STARTUP:
        {
            resetSafetyReactions();
            if(startupSequenceFinished()) systemState = STANDBY;
        }break;

        case STANDBY:
        {
            if(isPowerSwitchEnabled() && userACKHasBeenPressed()) systemState = RUNNING;
            if(getSystemErrorStatus() == ERROR_HAS_HAPPENED) systemState = ERROR;
            resetIntegrators();
        }break;

        case RUNNING:
        {
            if(!isPowerSwitchEnabled() || referenceSourceHasChanged()) systemState = STANDBY;
            if(getSystemErrorStatus() == ERROR_HAS_HAPPENED) systemState = ERROR;
            setRunningLED(ON); // System is in running state LED
            enableDrivers();

        }break;

        case ERROR:
        {
            performSafetyReactions();
            if(userACKHasBeenPressed())
            {
                resetSafetyReactions();
                systemState = STANDBY;
            }
        }break;
        default: forceSystemError();
        break;

    }
}

SysMgrState readSystemState(void)
{
    return systemState;
}

