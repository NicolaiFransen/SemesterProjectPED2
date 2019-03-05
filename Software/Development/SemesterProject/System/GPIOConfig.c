/*
 * GPIOConfig.c
 *
 *  Created on: Mar 4, 2019
 *      Author: Nicolas
 *
 *      Configuration of ports as GPIO, input/output.
 *      Main sources of information are:
 *          1- 1.5 General-Purpose Input/Output (GPIO), from technical reference (p.113)
 *          2- Table 6-72, from MCU datasheet (p.146)
 */

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Function declaration
//
void configureGPIO(void);


//Function: configureGPIO
//-----------------------
//This function configures the GPIO pins.
//GpioCtrlRegs.GP<A/B>MUX<1/2>.bit.GPIO<whatever number> configures the MUX
//    to select the appropriate feature in a specific pin. Read Table 6-72.
//    of MCU datasheet to see options. 0 is GPIO usually.
//    A or B and 1 or 2 depends in what GPIO is desired to be used. Read Table 6-72.
//GpioCtrlRegs.GP<A/B>DIR.bit.GPIO<whatever number> configures the GPIO
//    as digital output (1) or digital input (0).
//    A or B depends in what GPIO is desired to be used. Read Table 6-72.
//
void configureGPIO(void)
{
    EALLOW;
//    Configure GPIO34 as a GPIO output pin
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

//    Configure GPIO 52 (pushbutton for selecting reference input) as input
    // first start for input qualification config, point 1.5.4 of technical reference
    //TODO...

    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPBDIR.bit.GPIO52 = 1;     // Select digital input


//    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;
//    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;
    EDIS;
}
