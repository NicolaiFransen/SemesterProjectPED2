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
#include "analogAcquisitionManager.h"

//
// Quasi-global variables definition
//
__interrupt void adc_isr(void);
#define READ_DELAY  100000L


static SysMgrState SystemState = STARTUP;


void systemManager(void)
{

    switch (SystemState)
    {
        case STARTUP:
        {
            EALLOW;
            PieVectTable.ADCINT1 = &adc_isr;
            EDIS;

            initADC();

            if(startupSequenceFinished()) SystemState = STANDBY;


            for(;;)
            {
                DELAY_US(READ_DELAY);         // Delay before converting ADC channels
                readAnalogSignals();
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

__interrupt void adc_isr(void)
{
    readAnalogSignals();
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;

    return;
}

SysMgrState readSystemState(void)
{
    return SystemState;
}


//
// End of File
//

