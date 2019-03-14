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
#include "analogAcquisitionManager.h"

//
// Quasi-global variables definition
//
__interrupt void adc_isr(void);

static SysMgrState SystemState = STARTUP;


void systemManager(void)
{

    switch (SystemState)
    {
        case STARTUP:
        {
            InitPieCtrl();
            IER = 0x0000;
            IFR = 0x0000;
            EALLOW;
            PieVectTable.ADCINT1 = &adc_isr;
            EDIS;

            initADC();


            PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
            /*IER |= M_INT1;
            EINT;
            ERTM;*/


            if(startupSequenceFinished()) SystemState = STANDBY;
        }break;

        case STANDBY:
        {
            for(;;);
            /*AnalogSignal sig1;
            char type = 'L';
            int order = 1, filterFreq = 50;
            Uint16 sig1Channel = 0, sig2Channel = 1;
            int threshold[2] = {300, 3000};
            Signal_Constructor(&sig1, type, order, filterFreq, sig1Channel, threshold);
               */



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

