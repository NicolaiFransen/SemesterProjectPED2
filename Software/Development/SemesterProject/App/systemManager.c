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

    switch (systemState)
    {
        case STARTUP:
        {
            initDigitalInputs();
            if(startupSequenceFinished()) systemState = STANDBY;
        }break;

        case STANDBY:
        {
            if(isPowerSwitchEnabled()) systemState = RUNNING;
        }break;

        case RUNNING:
        {
            if(!isPowerSwitchEnabled()) systemState = STANDBY;
           // if(errorDetected()) SystemState = ERROR;
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

