//###########################################################################
// Created by Laszlo Mathe
// August 30, 2010 
//###########################################################################

#ifndef CONSTANTS_H
#define CONSTANTS_H


//Processor related parameters
#define CLOCK_FREQUENCY ((double)150e6)     // 150 MHz clock frequency
#define CLOCK_PERIOD    ((double)6.667e-9 ) // 1/CLOCK_FREQUENCY clock period
#define SW_FREQ      10000          //Switching frequency [10kHz].
#define SW_PERIOD_US   50           //Period of the PWM in us.
#define SW_PERIOD_S    ((float)50e-6)   //PWM period in s.
#define INTERNAL_FREQ   90000000    //Internal frequency of the device [90MHz]. Configured in InitSysCtrl().

#define MinPulseWidth	((double)2e-6)                  //minimum pulse width in s
#define MinPulseWidthCNT	((unsigned short)300)       //MinPulseWidth/CLOCK_PERIOD (2us)
#define Half_MinPulseWidthCNT	((unsigned short)150)	//half MinPulseWidth/CLOCK_PERIOD (1us)	

//Mathematical Constants
#define PI      		((double)(3.141592653589793)) // pi
#define TWO_PI      	((double)(6.283185307179586)) // 2 * pi
#define THREE_PI_DIV_2	((double)(4.712388980384690)) // '3*pi/2'
#define PI_DIV_2 		((double)(1.570796326794897)) // 'pi/2'
#define PI_DIV_6		((double)(0.523599)) // 'pi/6'
#define PI_DIV_3		((double)(1.047198)) // 'pi/3'
#define TWO_PI_DIV_3	((double)(2.094395)) // '2*pi/3'
#define FOUR_PI_DIV_3	((double)(4.18879))  // '4*pi/3'
#define FIVE_PI_DIV_3	((double)(5.235988)) // '5*pi/3'

#define  SQRT_2  ((double)1.41421356237309)  // sqrt(2)
#define  SQRT_3  ((double)1.73205080756887)  // sqrt(3)

// set implementation definitions:
#define ONE_DIV_3     ((double)0.333333333333333) // '1/3'
#define TWO_DIV_3     ((double)0.666666666666667) // '2/3'
#define SQRT2_DIV_3   ((double)0.471404520791032) // 'sqrt(2)/3'
#define SQRT3_DIV_2   ((double)0.866025403784439) // 'sqrt(3)/2'
#define SQRT3		  ((double)1.732050807568877) // 'sqrt(3)/2'
#define ONE_DIV_SQRT2 ((double)0.707106781186547) // '1/sqrt(2)'
#define ONE_DIV_SQRT3 ((double)0.577350269189626) // '1/sqrt(3)'
#define ONE_DIV_SQRT6 ((double)0.408248290463863) // '1/sqrt(6)'
#define TWO_DIV_SQRT6 ((double)0.816496580927726) // '2/sqrt(6)'
#define TWO_DIV_SQRT3 ((double)1.154700538379252) // '2/sqrt(3)'
#define TWO_SQRT3_DIV_PI ((double)1.102657790843584) // '2*sqrt(3)/pi'

// definitions for sector angle limits
#define DEG_10_TO_RAD  ((double)0.174532925199433) // '10 deg --> rad'
#define DEG_30_TO_RAD  ((double)0.523598775598299) // '30 deg --> rad'
#define DEG_60_TO_RAD  ((double)1.047197551196598) // '60 deg --> rad'
#define DEG_90_TO_RAD  ((double)1.570796326794897) // '90 deg --> rad'
#define DEG_120_TO_RAD ((double)2.094395102393195) // '120 deg --> rad'
#define DEG_180_TO_RAD ((double)3.141592653589793) // '180 deg --> rad'
#define DEG_240_TO_RAD ((double)4.188790204786391) // '240 deg --> rad'
#define DEG_300_TO_RAD ((double)5.235987755982989) // '300 deg --> rad'
#define DEG_360_TO_RAD ((double)6.283185307179586) // '360 deg --> rad'
#define REV_TO_RAD     ((double)6.283185307179586) // '1 rev   --> rad'
#define RAD_TO_REV     ((double)0.159154943091895) // '1 rad   --> rev'

// definitions specific to the motor
#define LM             ((float)0.38e-3)            // 'Magnetizing inductivity --> H'
#define LM_INVERSE     ((float)26315.78947)
#define RR             ((float)2.69e-3)            // 'Rotor resistance --> Ohm'
#define LR             ((float)411.16e-6)          // 'Rotor total inductance --> H'
#define TR             ((float)0.1528475836)       // 'Lr/Rr --> H/Ohm'
#define TR_INVERSE     ((float)6.54246522)         // 'Rr/Lr --> Ohm/H'
#define LAMDA_R        ((float)0.0567)
#define LAMDA_R_INVERSE ((float)17.6366843)
#define ID_RATED       ((float)149.2287)           // 'Id rated current --> A'
#define ID_RATED_INVERSE ((float)0.006701123845)   // 'Id rated current inverse --> A^-1'

#define ENCODER_STEPS 2048
#define ENCODER_STEPS_INVERSE ((float)(1.0 / ENCODER_STEPS))
#define POLE_PAIRS  2   //Number of pole pairs of the motor.
#define POLE_PAIRS_INVERSE ((float) 0.5)    //To be used instead of a division.


#define d_axis			0
#define	q_axis			1
#define	z_seq			2


#define ALPHA_AX		0
#define BETA_AX			1
#define ZERO_SEQ		2


// Constant component values from interface PCB
#define R_IN_CURRENT_MEAS           9.1     // Ohm
#define BIAS_VOLTAGE_OPAMP          0.817   // V
#define OPAMP_GAIN_CURRENT_MEAS     (float)-1      // []
#define CURRENT_SENSOR_GAIN         (float)2000    // []
#define R1_DCLINK_MEAS              (float)21500   // Ohm
#define R2_DCLINK_MEAS              (float)1000    // Ohm
#define R3_DCLINK_MEAS              (float)16200   // Ohm
#define R4_DCLINK_MEAS              (float)10000   // Ohm
#define R1_CONTROL_SUPPLY_MEAS      (float)8200    // Ohm
#define R2_CONTROL_SUPPLY_MEAS      (float)1000    // Ohm
#define TEMP_SENSOR_GAIN            0.01    // 10mV/deg



#endif  


//===========================================================================
// End of file.
//===========================================================================
