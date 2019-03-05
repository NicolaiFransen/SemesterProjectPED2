//###########################################################################
//FILE: main.c
//
//Project: Electric Go-kart
//
//Author: PED-841 AAU, February 2019 - May 2019.
//
//Notes:
//    The system initialization has been performed using TI's blinking LED example.
//    TI Data:  $TI Release: F2806x Support Library v2.04.00.00 $
//              $Release Date: Thu Oct 18 15:47:20 CDT 2018 $
//
//
//###########################################################################

//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Function Prototypes statements for functions found within this file.
//
void systemInit(void);

//
// Quasi-global variables definition
//


//
// Main
//
void main(void)
{
    systemInit();
    for(;;)
    {
        systemManager(); //This call to the system manager is temporary
                         //until it the Scheduler component is developed.
    }
}


//
// End of File
//

