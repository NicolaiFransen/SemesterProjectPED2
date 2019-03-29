/*
 * GPIOConfig.h
 *
 * Created on: Mar 12, 2019
 *  Author: Nicolas
 *
 */

#ifndef SYSTEM_INCLUDE_GPIOCONFIG_H_
#define SYSTEM_INCLUDE_GPIOCONFIG_H_

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File


//
// Function declaration
//
void configureGPIO(void);

/*
 * PIN definition. The goal is to decouple the GPIO from the connector
 * or transducer itself. Then the developer will use the connector name
 * instead of the GPIO pin.
 * The first item is the connector or element as it is named in the PCB,
 * the second item is the GPIO pin where the element is connected to.
 */
#define	S1	    1
#define S2      3
#define DS17    5
//#define   Free pin    6
//#define   Free pin    7
#define J17     8
#define J18     8
#define J19     8
#define J21     9
#define	J20	    10
#define	J5	    11
#define	DS16	12
#define	DS18	13
#define	B3	    14
#define	DS10	16
#define	DS11	17
#define	DS15	18
#define	B1	    19
#define	DS14	22
#define	J11	    24
#define	J12	    25
#define	J10	    26
#define	J9	    27
#define	B2	    32
#define	DS13	33
#define	DS9	    44
#define	DS12	50
#define	DS20	51
#define	J8	    52
#define	J7	    53
#define	B4	    54
#define	DS19	55
#define	J6	    56


#endif /* SYSTEM_INCLUDE_GPIOCONFIG_H_ */
