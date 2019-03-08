/*
 * systemInit.h
 *
 *  Created on: Mar 7, 2019
 *      Author: Nicolas
 */

#ifndef SYSTEM_INCLUDE_SYSTEMINIT_H_
#define SYSTEM_INCLUDE_SYSTEMINIT_H_

//
// Function Prototypes statements for functions found within this file.
//
void systemInit(void);
int startupSequenceFinished(void);
__interrupt void cpu_timer0_isr(void);
void configureGPIO(void);



#endif /* SYSTEM_INCLUDE_SYSTEMINIT_H_ */
