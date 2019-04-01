/*
 * encoderManager.c
 *
 *  Created on: 1 abr. 2019
 *      Author: Aitor Teran
 */

#include "encoderManager.h"


void initEncoder(void)
{
    EQep1Regs.QUPRD = 900000;         // Unit Timer for 100Hz at 80 MHz SYSCLKOUT

    EQep1Regs.QDECCTL.bit.QSRC = 00;      // QEP quadrature count mode

    //EQep control:
    EQep1Regs.QEPCTL.bit.FREE_SOFT = 2;
    EQep1Regs.QEPCTL.bit.PCRM = 00;   // PCRM=00 mode - QPOSCNT reset on index event
    EQep1Regs.QEPCTL.bit.SEI = 00;    // Strobe event initialization of position counter. 00 -> does nothing.
    EQep1Regs.QEPCTL.bit.IEI = 10;    // Index event initialization. 10 -> init on rising edge.
    EQep1Regs.QEPCTL.bit.SWI = 0;     // Software init of position counter. 0 -> do nothing.
    EQep1Regs.QEPCTL.bit.SEL = 0;     // Strobe event latch of pos counter. 0 -> latched on rising edge of QEPS ¿?
    EQep1Regs.QEPCTL.bit.IEL = 01;    // Index event latch of pos counter. 01 -> latches on rising edge of index.
    EQep1Regs.QEPCTL.bit.QPEN = 1;    // Quadrature pos counter enable/software reset. 1 -> eQEP pos counter enabled.

    //QCLM REGISTER DETERMINES CONSTANT X vs T.
    EQep1Regs.QEPCTL.bit.QCLM = 1;    // eQEP capture latch mode. 1 -> latch on unit time out
    EQep1Regs.QEPCTL.bit.UTE = 1;     // Unit Timeout Enable. 1 -> Enabled.
    EQep1Regs.QEPCTL.bit.WDE = 0;     // Watchdog enable. 0 -> disabled

    EQep1Regs.QPOSMAX = 0xffffffff;     // Maximum possible counter value.
    EQep1Regs.QPOSINIT = 0;             // Position value used to initialize when index event.

    EQep1Regs.QCAPCTL.bit.CEN = 1;      // QEP Capture Enable
    EQep1Regs.QCAPCTL.bit.CCPS = 6;     // 1/64 for CAP clock prescaler
    EQep1Regs.QCAPCTL.bit.UPPS = 5;     // 1/32 for unit position prescaler

    //// page 480 TO BE CONTINUED.
}
