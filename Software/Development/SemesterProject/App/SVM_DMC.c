/*
 * SVM_DMC.c
 *
 *  Created on: May 15, 2019
 *      Author: Nicolas
 *
 *      This module provides the interfaces for using TI's DMC SVGEN.
 *
 *
 */

#include "SVM_DMC.h"

static SVGENDQ svgen_dq;

static _iq Va,Vb,Vc,t1,t2,temp_sv1,temp_sv2;
static unsigned short Sector = 0;  // Sector is treated as Q0 - independently with global Q


void SVMInit_DMC(void)
{
    svgen_dq.Ta = 0;
    svgen_dq.Tb = 0;
    svgen_dq.Tc = 0;
    svgen_dq.Ualpha = 0;
    svgen_dq.Ubeta =0;

}

void runSVM_DMC(alphaBetaObject abVoltages)
{

    svgen_dq.Ualpha = abVoltages.alphaComponent;     // Pass inputs to svgen_dq1
    svgen_dq.Ubeta = abVoltages.betaComponent;       // Pass inputs to svgen_dq1

    SVGEN_MACRO (svgen_dq);        // Call compute macro for svgen_dq1

//     Ta1 = svgen_dq.Ta;            // Access the outputs of svgen_dq1
//     Tb1 = svgen_dq.Tb;            // Access the outputs of svgen_dq1
//     Tc1 = svgen_dq.Tc;            // Access the outputs of svgen_dq1

     setDutyA(svgen_dq.Ta * MAX_DUTY_CYCLE);
     setDutyB(svgen_dq.Tb * MAX_DUTY_CYCLE);
     setDutyC(svgen_dq.Tc * MAX_DUTY_CYCLE);

}
