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
#include "Include/GPIOConfig.h"

/*
*Function: configureGPIO
*-----------------------
*This function configures the GPIO pins. Steps:
*1)Enable or disable pull-up resistors with GP<A/B>PUD.
*  Enabled by default. For digital input, we want to disable them:
*
*2)Select input qualification by GP<A/B>CTRL and GP<A/B>QSEL<1/2>.
*  This allows to qualify the error asynchronously, synchronized with SYCLOCK
*  or to qualify after a time window. For digital input we will go for sync
*  with SYSCLOCK. This is the default configuration. However these can be
*  explicitly declared by GpioCtrlRegs.GPBCTRL.bit.QUALPRD2 = 0; (GPIO50-55)
*3)Select pin function by GpioCtrlRegs.GP<A/B>MUX<1/2>.bit.GPIO<whatever number>
*    to select the appropriate feature in a specific pin, for example GPIO or PWM:
*    Read Table 6-72 of MCU datasheet to see options. 0 is usually GPIO.
*    A or B and 1 or 2 depends in what GPIO is desired to be used. Read Table 6-72.
*4)Select direction of the PIN I/O by GpioCtrlRegs.GP<A/B>DIR.bit.GPIO<whatever number>
*    as digital output (1) or digital input (0).
*
*A or B depends in what GPIO is desired to be used. Read Table 6-72.
*/
void configureGPIO(void)
{
    EALLOW;
    /*
     * Output pins configuration
     */
//    Configure GPIO34 as a GPIO output pin
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

    /*
     * Input pins configuration
     */
//  Select digital input sampling frequency; 0 = Tsysclockout

    GpioCtrlRegs.GPACTRL.bit.QUALPRD0 = 0; //(GPIO0-07)
    GpioCtrlRegs.GPACTRL.bit.QUALPRD1 = 0; //(GPIO8-15)
    GpioCtrlRegs.GPACTRL.bit.QUALPRD2 = 0; //(GPIO16-23)
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD0 = 0; //(GPIO32-39)
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD2 = 0; //(GPIO50-55)

    //  Configure GPIO 1 (Power Enable switch) as input
    GpioCtrlRegs.GPAPUD.bit.GPIO1= 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;     // Select digital input

    //  Configure GPIO 3 (Open or closed loop selection switch) as input
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;     // Select digital input

    //  Configure GPIO 14 (cruise control pushbutton) as input
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;     // Select digital input

    //  Configure GPIO 19 (Torque reference input selection pushbutton) as input
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;     // Select digital input

    //  Configure GPIO 32 regenerative braking selection pushbutton) as input
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;     // Select digital input

    //  Configure GPIO 52 (pushbutton for selecting reference input) as input
    GpioCtrlRegs.GPBPUD.bit.GPIO52 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPBDIR.bit.GPIO52 = 1;     // Select digital input

    //  Configure GPIO 54 (Anti-slip pushbutton) as input
    GpioCtrlRegs.GPBPUD.bit.GPIO54 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPBDIR.bit.GPIO54 = 1;     // Select digital input


//    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;
//    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;
    EDIS;
}
