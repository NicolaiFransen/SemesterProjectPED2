//###########################################################################
// Created by Laszlo Mathe
// August 30, 2010 
//###########################################################################

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "analogSignal.h"


//Processor related parameters
#define CLOCK_FREQUENCY             ((float)150e6)          // 150 MHz clock frequency
#define CLOCK_PERIOD                ((float)6.667e-9)       // 1/CLOCK_FREQUENCY clock period
#define SW_FREQ                     10000                   //Switching frequency [10kHz].
#define SW_PERIOD_US                100                     //Period of the PWM.
#define SW_PERIOD_S                 ((float)100e-6)         //PWM period in s.
#define INTERNAL_FREQ               90000000                //Internal frequency of the device [90MHz]. Configured in InitSysCtrl().

#define MinPulseWidth	            ((float)2e-6)           //minimum pulse width in s
#define MinPulseWidthCNT	        ((unsigned short)300)   //MinPulseWidth/CLOCK_PERIOD (2us)
#define Half_MinPulseWidthCNT	    ((unsigned short)150)	//half MinPulseWidth/CLOCK_PERIOD (1us)

//Mathematical Constants
#define PI      		    ((float)(3.141592653589793))    // pi
#define TWO_PI      	    ((float)(6.283185307179586))    // 2*pi
#define THREE_PI_DIV_2	    ((float)(4.712388980384690))    // '3*pi/2'
#define PI_DIV_2 		    ((float)(1.570796326794897))    // 'pi/2'
#define PI_DIV_6		    ((float)(0.523599))             // 'pi/6'
#define PI_DIV_3		    ((float)(1.047198))             // 'pi/3'
#define TWO_PI_DIV_3	    ((float)(2.094395))             // '2*pi/3'
#define FOUR_PI_DIV_3	    ((float)(4.18879))              // '4*pi/3'
#define FIVE_PI_DIV_3	    ((float)(5.235988))             // '5*pi/3'

#define  SQRT_2             ((float)1.41421356237309)       // sqrt(2)
#define  SQRT_3             ((float)1.73205080756887)       // sqrt(3)

// set implementation definitions:
#define ONE_DIV_3           ((float)0.333333333333333)      // '1/3'
#define TWO_DIV_3           ((float)0.666666666666667)      // '2/3'
#define SQRT2_DIV_3         ((float)0.471404520791032)      // 'sqrt(2)/3'
#define SQRT3_DIV_2         ((float)0.866025403784439)      // 'sqrt(3)/2'
#define SQRT3		        ((float)1.732050807568877)      // 'sqrt(3)/2'
#define ONE_DIV_SQRT2       ((float)0.707106781186547)      // '1/sqrt(2)'
#define ONE_DIV_SQRT3       ((float)0.577350269189626)      // '1/sqrt(3)'
#define ONE_DIV_SQRT6       ((float)0.408248290463863)      // '1/sqrt(6)'
#define TWO_DIV_SQRT6       ((float)0.816496580927726)      // '2/sqrt(6)'
#define TWO_DIV_SQRT3       ((float)1.154700538379252)      // '2/sqrt(3)'
#define TWO_SQRT3_DIV_PI    ((float)1.102657790843584)      // '2*sqrt(3)/pi'

// definitions for sector angle limits
#define DEG_10_TO_RAD       ((float)0.174532925199433)      // '10 deg --> rad'
#define DEG_30_TO_RAD       ((float)0.523598775598299)      // '30 deg --> rad'
#define DEG_60_TO_RAD       ((float)1.047197551196598)      // '60 deg --> rad'
#define DEG_90_TO_RAD       ((float)1.570796326794897)      // '90 deg --> rad'
#define DEG_120_TO_RAD      ((float)2.094395102393195)      // '120 deg --> rad'
#define DEG_180_TO_RAD      ((float)3.141592653589793)      // '180 deg --> rad'
#define DEG_240_TO_RAD      ((float)4.188790204786391)      // '240 deg --> rad'
#define DEG_300_TO_RAD      ((float)5.235987755982989)      // '300 deg --> rad'
#define DEG_360_TO_RAD      ((float)6.283185307179586)      // '360 deg --> rad'
#define REV_TO_RAD          ((float)6.283185307179586)      // '1 rev   --> rad'
#define RAD_TO_REV          ((float)0.159154943091895)      // '1 rad   --> rev'
#define RAD_TO_DEG     		((float)57.29577951)


// definitions specific to the motor
#define LM                  ((float)0.38e-3)                // 'Magnetizing inductivity --> H'
#define LM_INVERSE          ((float)26315.78947)
#define RR                  ((float)2.69e-3)                // 'Rotor resistance --> Ohm'
#define LR                  ((float)411.16e-6)              // 'Rotor total inductance --> H'
#define TR                  ((float)0.1528475836)           // 'Lr/Rr --> H/Ohm'
#define TR_INVERSE          ((float)6.54246522)             // 'Rr/Lr --> Ohm/H'
#define LAMDA_R             ((float)0.0567)
#define LAMDA_R_INVERSE     ((float)17.6366843)
#define ID_RATED            ((float)149.2287)               // 'Id rated current --> A'
#define ID_RATED_INVERSE    ((float)0.006701123845)         // 'Id rated current inverse --> A^-1'

#define MAX_STATOR_FREQ     58 //Hz used for VF control
#define ENCODER_STEPS       8192

#define ENCODER_STEPS_INVERSE ((float)(1.0 / ENCODER_STEPS))
#define POLE_PAIRS            2                             //Number of pole pairs of the motor.
#define POLE_PAIRS_INVERSE    ((float)0.5)                  //To be used instead of a division.

#define THETA_RAW_TO_THETA_ELEC     POLE_PAIRS * REV_TO_RAD * ENCODER_STEPS_INVERSE
#define THETA_RAW_TO_THETA_MECH     REV_TO_RAD * ENCODER_STEPS_INVERSE

#define TORQUE_TO_Q_CURRENT         1/(TWO_DIV_3 * POLE_PAIRS * (LM/LR) * LAMDA_R)
#define D_CURRENT_REFERENCE         LAMDA_R/LM

#define MAX_ADC_STEPS               (float)4095.0
#define MAX_ADC_REFERENCE           (float)3.3
#define MAX_ADC_STEPS_INVERSE       1 / MAX_ADC_STEPS

#define d_axis			0
#define	q_axis			1
#define	z_seq			2


#define ALPHA_AX		0
#define BETA_AX			1
#define ZERO_SEQ		2

#define PI_Ratio        1
#define KP_IQ           (float)0.78/PI_Ratio
#define KI_IQ           (float)4.3/PI_Ratio
#define KP_ID           (float)0.78/PI_Ratio
#define KI_ID           (float)4.3/PI_Ratio
#define KP_SPEED        (float)3.7
#define KI_SPEED        (float)0.37

#define CURRENT_LIMIT           100    //189 * SQRT_2    // Maximum output for current PI's
#define MAXIMUM_ROTOR_SPEED     1700            // Maximum rotor speed, for errorManager

// Constant component values from interface PCB
#define R_IN_CURRENT_MEAS           (float)9.1                 // Ohm
#define BIAS_VOLTAGE_OPAMP          (float)0.817               // V
#define OPAMP_GAIN_CURRENT_MEAS     (float)-1           // []
#define CURRENT_SENSOR_GAIN         (float)2000         // []
#define R1_DCLINK_MEAS              (float)21500        // Ohm
#define R2_DCLINK_MEAS              (float)1000         // Ohm
#define R3_DCLINK_MEAS              (float)16200        // Ohm
#define R4_DCLINK_MEAS              (float)10000        // Ohm
#define R1_CONTROL_SUPPLY_MEAS      (float)8200         // Ohm
#define R2_CONTROL_SUPPLY_MEAS      (float)1000         // Ohm
#define TEMP_SENSOR_GAIN            (float)0.01                // 10mV/deg
#define MEAS_TO_TEMP                (float)100          // 100deg/V

// Defines of inverse sensor gains
#define DC_LINK_MEAS_TO_VOLTAGE         (R4_DCLINK_MEAS/R3_DCLINK_MEAS)*((R1_DCLINK_MEAS+R2_DCLINK_MEAS)/R2_DCLINK_MEAS)
#define CONTROL_SUPPLY_MEAS_TO_VOLTAGE  ((R1_CONTROL_SUPPLY_MEAS+R2_CONTROL_SUPPLY_MEAS)/R2_CONTROL_SUPPLY_MEAS)

// Defines of inverse current sensor transfer function
#define OPAMP_OFFSET_CURRENT            (float)((1 - OPAMP_GAIN_CURRENT_MEAS) * BIAS_VOLTAGE_OPAMP)
#define CURRENT_SENSOR_GAIN_INVERSE     (float)(CURRENT_SENSOR_GAIN / (OPAMP_GAIN_CURRENT_MEAS * R_IN_CURRENT_MEAS))

// Sensor offsets
#define CURRENT_SENSOR_OFFSET_A           9       // [A]
#define CURRENT_SENSOR_OFFSET_B           9       // [A]
#define CURRENT_SENSOR_OFFSET_C           9       // [A]
#define CONTROL_SUPPLY_OFFSET             2       // [V]
#define DC_LINK_OFFSET                    0       // [V]
#define TEMP_SENSOR_OFFSET                0       // [deg C]

// Defines of struct sizes
#define ANALOG_SIGNAL_SIZE_INVERSE         1 / 24


#endif  
