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

static SysMgrState SystemState = STARTUP;


void manageSystem(void)
{

    switch (SystemState)
    {
        case STARTUP:
        {
            initDigitalInputs();
            if(startupSequenceFinished()) SystemState = STANDBY;
        }break;

        case STANDBY:
        {
            if(isPowerSwitchEnabled()) SystemState = RUNNING;
        }break;

        case RUNNING:
        {
            if(!isPowerSwitchEnabled()) SystemState = STANDBY;
           // if(errorDetected()) SystemState = ERROR;
        }break;

//        case ERROR:
//        {
//            if(errorIsAcknowledged()) SystemState = STANDBY;
//        }break;
    }
    readDigitalInputs();
}

SysMgrState readSystemState(void)
{
    return SystemState;
}


//
// End of File
//

