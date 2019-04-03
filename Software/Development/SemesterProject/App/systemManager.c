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
    setLED18(OFF);

    switch (systemState)
    {
        case STARTUP:
        {
            if(startupSequenceFinished()) systemState = STANDBY;
        }break;

        case STANDBY:
        {
            if(isPowerSwitchEnabled() && userACKHasBeenPressed()) systemState = RUNNING;
        }break;

        case RUNNING:
        {
            if(!isPowerSwitchEnabled() || referenceSourceHasChanged()) systemState = STANDBY;
           // if(errorDetected()) SystemState = ERROR;
            setLED18(ON); // System is in running state LED
        }break;

//        case ERROR:
//        {
//            if(errorIsAcknowledged()) systemState = STANDBY;
//        }break;
    }
    readDigitalInputs();
}

SysMgrState readSystemState(void)
{
    return systemState;
}


//
// End of File
//
