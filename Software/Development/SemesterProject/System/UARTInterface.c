/*
 * UARTInterface.c
 *
 *  Created on: Apr 10, 2019
 *      Author: Nicolas
 *
 *      This module contain the interface for using UART.
 *      The UART uses GPIO 28 and 29, then JP6 and JP7 must be properly
 *      set in the Launchpad, as described in its datasheet.
 *
 *      The development was based in 'Example_2806xSci_Echoback' but mainly
 *      in 'Real-time Systems and Programming Languages' Digital commmunication
 *      Lecture's Slides.
 */

#include "Include/UARTInterface.h"
#include "DSP28x_Project.h"

struct INT16_BYTES
{
    Uint16 BYTE0:8; // 7:0
    Uint16 BYTE1:8; // 15:8
};

union INT16_DATA_PACKAGE
{
    int16 number;
    struct INT16_BYTES bytes;
};

union INT16_DATA_PACKAGE receivedData, dataToSend;


/*
 * When FIFO mode is enabled for SCI, characters written to
 * SCITXBUF are queued in to SCI-TXFIFO.
 *
 * TX interrupt generated when FIFO buffer is empty.
 * You can load up to 4 bytes in the FIFO buffer at once
 */
interrupt void SCIA_TX_isr(void)
{
    if (getUARTBufferSize() >= 4)
    {
        SciaRegs.SCITXBUF = getNextBufferValue();
        SciaRegs.SCITXBUF = getNextBufferValue();
        SciaRegs.SCITXBUF = getNextBufferValue();
        SciaRegs.SCITXBUF = getNextBufferValue();

        // If the UART buffer is not empty then enable the interrupt so the transmission keeps going
        if (!isUARTBufferEmpty())    SciaRegs.SCIFFTX.bit.TXFFINTCLR = 1;
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}


void initUART(void)
{
    constructUARTBuffer();
    InitSciGpio();
    sciConfiguration();
    UARTStringPrint("\n\rWelcome to the excellent Go-Kart controller, by PED-841.\n\r");
}

void sciConfiguration(void)
{
    SciaRegs.SCICTL1.bit.SWRESET = 0; // Hold SCIA in reset mode while configuring

//  SCICCR
    SciaRegs.SCICCR.bit.STOPBITS = 0;// 1 Stop bit
    SciaRegs.SCICCR.bit.LOOPBKENA = 0;// Loop back disabled
    SciaRegs.SCICCR.bit.PARITY = 0;// Odd parity
    SciaRegs.SCICCR.bit.PARITYENA = 0;// Disable parity
    SciaRegs.SCICCR.bit.SCICHAR = 111;// 8 data bits

//  SCICTL1
    SciaRegs.SCICTL1.bit.RXENA = 1; //Enable Rx (receive) pin
    SciaRegs.SCICTL1.bit.TXENA = 1; //Enable Tx (transmit) pin
    SciaRegs.SCICTL1.bit.RXERRINTENA = 0; //Disable receive error interrupt
    SciaRegs.SCICTL1.bit.SLEEP = 0; //Disable sleep mode
    SciaRegs.SCICTL1.bit.TXWAKE = 0; //No wakeup mode
    SciaRegs.SCICTL1.bit.SWRESET = 0; //Enable SCI after reset

//  Baudrate select desired speed. @LSPCLK = 22.5 MHz
    //38400 baud/s
    SciaRegs.SCIHBAUD = 0;
    SciaRegs.SCILBAUD = 0x48;
//    //115200 baud/s
//    SciaRegs.SCIHBAUD = 0x00;
//    SciaRegs.SCILBAUD = 0x17;



//  SCICTL2
    SciaRegs.SCICTL2.bit.TXINTENA = 0;//ENable transmit interrupt
    SciaRegs.SCICTL2.bit.RXBKINTENA = 0;//disable receive interrupt

//  Interrupt config
    EALLOW;
    PieVectTable.SCITXINTA = &SCIA_TX_isr;
//    PieVectTable.SCIRXINTA = &SCIA_RX_isr;
    EDIS;
    PieCtrlRegs.PIEIER9.bit.INTx2 = 1;// Enable SCIA TX interrupt
//    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;// Enable SCIA RX interrupt
    IER = M_INT9;

//  Config FIFO
    SciaRegs.SCIFFTX.bit.SCIRST = 1; //Relinquish FIFO unit from reset
    SciaRegs.SCIFFTX.bit.SCIFFENA = 1; //Enable FIFO- Enhancements
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;//Enable TX FIFO Operation
    SciaRegs.SCIFFTX.bit.TXFFINTCLR = 1;//Clear TXFFINT-Flag
    SciaRegs.SCIFFTX.bit.TXFFIENA = 1;//Enable TX FIFO match
    SciaRegs.SCIFFTX.bit.TXFFIL = 0;//Set FIFO interrupt level to interrupt, if FIFO is empty (0)
    SciaRegs.SCICTL1.bit.SWRESET = 1; // Release SCIA from reset mode while configuring

}





