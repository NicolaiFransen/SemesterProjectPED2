/*
 * UARTInterface.h
 *
 *  Created on: Apr 10, 2019
 *      Author: Nicolas
 */

#ifndef SYSTEM_INCLUDE_UARTINTERFACE_H_
#define SYSTEM_INCLUDE_UARTINTERFACE_H_

#include "queueObject.h"

#define UART_AMOUNT_OF_VARIABLES 1500


void initUART(void);
void UARTComms(void);
void scia_fifo_init(void);
void sciConfiguration(void);
void scia_echoback_init();
void scia_xmit(int a);
void scia_msg(char * msg);

int getUartCounter(void);
void increaseUARTCounter(void);


#endif /* SYSTEM_INCLUDE_UARTINTERFACE_H_ */
