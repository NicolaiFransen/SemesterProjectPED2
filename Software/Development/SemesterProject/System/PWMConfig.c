/*
 * PWMConfig.c
 *
 *  Created on: 13 mar. 2019
 *      Author: Aitor Teran
 *
 *      Configuration of PWM ports.
 *      Main sources of information are:
 *          1- Lecture 6: Digital to analog conversion of
 *          'Realtidssystemer og programmeringssprog' AAU
 *          course by Sergiu Spataru.
 *          2- TMS320x2806x Piccolo technical reference manual.
 */

//
// Included Files
//
#include "Include/PWMConfig.h"

//
// There are three PWM signals to be configured, these are connected to
// EPWM1A, EPWM2A and EPWM3A.
//

/*
*Function: configurePWM
*
*
*/


void configurePWM(void)
{
    //
    //Pin configuration
    //

    EALLOW;

    //  Configure EPWMA1
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;    // Select ePWMA1 from MUX

    //  Configure EPWMA2
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;    // Select ePWMA2 from MUX

    //  Configure EPWMA3
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;    // Select ePWMA3 from MUX



    //
    //Initialize EPWM_A1, EPWM_A2 and EPWM_A3
    //

    //Configure PWM period. (Page 336)
    //PWM PERIOD is configured according to the switching frequency found in PWMConfig.h
    // Period: For up-down-count mode, period is calculated as 2*TBPRD*T_tbclk
    EPwm1Regs.TBPRD = INTERNAL_FREQ/(2*SW_FREQ);
    EPwm2Regs.TBPRD = INTERNAL_FREQ/(2*SW_FREQ);
    EPwm3Regs.TBPRD = INTERNAL_FREQ/(2*SW_FREQ);

    //Clear TB counter register. (Page 338) Set the current time-base counter to zero.
    EPwm1Regs.TBCTR = 0;
    EPwm2Regs.TBCTR = 0;
    EPwm3Regs.TBCTR = 0;

    //
    //TBCTL (Time base control)
    //
    //Set symmetric triangular carrier.
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;

    //Align PWM phases.
    EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;

    //Enable shadow register*
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;

    //These bits select the source of the EPWMxSYNCO signal, useful for aligning pwm phases. Page 339 of datasheet.
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; //Aligning when CTR = 0.
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;

    //Do not force software synchronization pulse.
    EPwm1Regs.TBCTL.bit.SWFSYNC = 0;
    EPwm2Regs.TBCTL.bit.SWFSYNC = 0;
    EPwm3Regs.TBCTL.bit.SWFSYNC = 0;

    //High speed time-base prescale bits.
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; // /1 --> TBCLK = SYSCLKOUT (Page 339 of datasheet).
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;

    //Time-base clock prescale bits.
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1; // /1 --> TBCLK = SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    //Stablish direction of syncro event. (Pag 269 of datasheet).
    EPwm1Regs.TBCTL.bit.PHSDIR = 0; //Count down after the synchronization event. (1 counts up). This shouldn't make much of a difference.
    EPwm2Regs.TBCTL.bit.PHSDIR = 0;
    EPwm3Regs.TBCTL.bit.PHSDIR = 0;
    //
    //TBCTL (Time base control) finished.
    //

    //
    //COUNTER COMPARE.
    //
    //Counter compare control register (CMPCTL). (Page 345)
    //Load duty on zero.
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;

    //No need to load duty on B.
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_LD_DISABLE;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_LD_DISABLE;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_LD_DISABLE;

    //Operating as double buffer. First load shadow and then write via shadow reg.
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;

    //The Action-qualifier output register A (AQCTLA) decides the final output value based on the CMPA value.
    //Since a triangular carrier is used, it has to be configured that way.
    //When counter equals zero.
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm3Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;

    //When counter equals the period.
    EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm2Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm3Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;

    //When counter equals CMPA register and counter is incrementing
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;

    //When counter equals CMPA register and counter is decrementing
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;

    //DEADBAND register configuration
    //Since the deadband is performed in the inverter circuit, it must be bypassed here.
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EDIS;
}
