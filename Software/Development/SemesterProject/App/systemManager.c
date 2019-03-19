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

#include "F2806x_Cla_typedefs.h"// F2806x CLA Type definitions

#include "F2806x_GlobalPrototypes.h"

#include "Include/systemManager.h"

//
// Quasi-global variables definition
//

static SysMgrState SystemState = STARTUP;


void systemManager(void)
{

    switch (SystemState)
    {
        case STARTUP:
        {

            if(startupSequenceFinished()) SystemState = STANDBY;


            for(;;)
            {
                //DELAY_US(READ_DELAY);         // Delay before converting ADC channels

            }
        }break;

        case STANDBY:
        {
            for(;;);


        }break;
//
//        case RUNNING:
//        {
//
//        }break;
//
//        case ERROR:
//        {
//
//        }break;
    }

}


SysMgrState readSystemState(void)
{
    return SystemState;
}


//
// End of File
//

