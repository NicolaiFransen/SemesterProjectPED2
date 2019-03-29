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
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;

    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;

    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 1;

    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;

    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO22 = 1;

    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;

    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;

    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;

    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1;

    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO55 = 1;

    /*
     * Extra Outputs:

   */
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
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;     // Select digital input

    //  Configure GPIO 3 (Open or closed loop selection switch) as input
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;     // Select digital input

    //  Configure GPIO 14 (cruise control pushbutton) as input
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;     // Select digital input

    //  Configure GPIO 19 (Torque reference input selection pushbutton) as input
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // Select digital input

    //  Configure GPIO 32 regenerative braking selection pushbutton) as input
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;     // Select digital input



    //  Configure GPIO 54 (Anti-slip pushbutton) as input
    GpioCtrlRegs.GPBPUD.bit.GPIO54 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPBDIR.bit.GPIO54 = 0;     // Select digital input



    /*
     * Init of extra digital inputs/outputs
     * Change the comments for the part you want to use.
     */
    // Configure GPIO11 as input
    /*GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;     // Select digital input*/

    // Configure GPIO11 as output
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;

    // Configure GPIO24 as input
    /*GpioCtrlRegs.GPAPUD.bit.GPIO24 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;     // Select digital input*/

    // Configure GPIO24 as output
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;

    // Configure GPIO25 as input
    /*GpioCtrlRegs.GPAPUD.bit.GPIO25 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;     // Select digital input*/

    // Configure GPIO25 as output
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 1;

    // Configure GPIO26 as input
    /*GpioCtrlRegs.GPAPUD.bit.GPIO26 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;     // Select digital input*/

    // Configure GPIO26 as output
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 1;

    // Configure GPIO27 as input
    /*GpioCtrlRegs.GPAPUD.bit.GPIO27 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;     // Select digital input*/

    // Configure GPIO as output
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;

    //  Configure GPIO 52 as input
    /*GpioCtrlRegs.GPBPUD.bit.GPIO52 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0;     // Select digital input*/

    // Configure GPIO52 as output
    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO52 = 1;

    // Configure GPIO 53 as input
    /*GpioCtrlRegs.GPBPUD.bit.GPIO53 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPBQSEL2.bit.GPIO53 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;     // Select digital input*/

    // Configure GPIO53 as output
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1;

    // Configure GPIO 56 as input
    /*GpioCtrlRegs.GPBPUD.bit.GPIO56 = 1; //Disable pull-up resistor
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 0; //Select amount of samples for qualifying, 0 = 1 sample.
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0;    // Select GPIO from MUX
    GpioCtrlRegs.GPBDIR.bit.GPIO56 = 0;     // Select digital input*/

    // Configure GPIO as output
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO56 = 1;

    EDIS;
}


