//###########################################################################
//FILE: systemInit.c
//
//Project: Electric Go-kart
//
//Author: Nicolas Murguizur, 3/3/19
//
//Notes:
//      System initialization file, including configuring CPU Timer0
//      for a 500 msec period, and toggles the
//!     GPIO34 LED once per interrupt. For testing purposes, this example
//!     also increments a counter each time the timer asserts an interrupt.
//!
//!     \b Watch \b Variables \n
//!     - CpuTimer0.InterruptCount
//
//###########################################################################

//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Include/systemInit.h"
#include "../App/Include/digitalInputManager.h"
#include "pushButtonManager.h"
#include "../App/Include/analogAcquisitionManager.h"


//
// Quasi-global variables definition
//
static int startupSequenceFinishedFlag = 0;



void systemInit(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initalize GPIO:
    // This example function is found in the F2806x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2806x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2806x_DefaultIsr.c.
    // This function is found in F2806x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;    // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = &cpu_timer0_isr;
    PieVectTable.TINT1 = &cpu_timer1_isr;
    PieVectTable.ADCINT1 = &adc_isr;
    EDIS;      // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize the Device Peripheral. This function can be
    //         found in F2806x_CpuTimers.c
    //
    InitCpuTimers();   // For this example, only initialize the Cpu Timers

    //
    // Configure CPU-Timer 0 to interrupt every 50 microseconds:
    // 90MHz CPU Freq, 50 millisecond Period (in uSeconds)
    //
    ConfigCpuTimer(&CpuTimer0, 90, 50);
    ConfigCpuTimer(&CpuTimer1, 90, 50);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in ConfigCpuTimer and InitCpuTimers (in F2806x_CpuTimers.h), the
    // below settings must also be updated.
    //

    //
    // Use write-only instruction to set TSS bit = 0
    //
    CpuTimer0Regs.TCR.all = 0x4001;
    CpuTimer1Regs.TCR.all = 0x4001;

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Configure GPIO
    //
    configureGPIO();

    //
    // Configure PWMs
    //
    configurePWM();

    //
    // Enable CPU INT1 which is connected to CPU-Timer 0
    // Initialize and calibrate ADC blocks
    //
    InitAdc();
    AdcOffsetSelfCal();

    //
    //  App structures initialization
    //
    initDigitalInputs();
    initPWM();
    initAnalogSignals();      // Initialize the analog signals and their ADC channels

	initPushbuttons();
	
    //
    // Enable CPU INT1 which is connected to CPU-Timer 0, CPU int13
    // which is connected to CPU-Timer 1:
    //
    IER |= M_INT1;
    IER |= M_INT13;

    //
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

<<<<<<< HEAD

    //
    //  App structures initialization
    //
    initDigitalInputs();
    initPWM();
    initPushbuttons();

    initAnalogSignals();      // Initialize the analog signals and their ADC channels

=======
>>>>>>> develop
    startupSequenceFinishedFlag = 1;

}

int startupSequenceFinished(void)
{
    return startupSequenceFinishedFlag;
}


//
// End of File
//

