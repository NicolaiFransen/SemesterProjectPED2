//###########################################################################
// Created by Laszlo Mathe
// August 30, 2010 
//###########################################################################

#ifndef CONSTANTS_H
#define CONSTANTS_H

//Processor related parameters
#define CLOCK_FREQUENCY ((double)150e6)  // 150 MHz clock frequency
#define CLOCK_PERIOD    ((double)6.667e-9 ) // 1/CLOCK_FREQUENCY clock period

#define MinPulseWidth	((double)2e-6) //minimum pulse width in s
#define MinPulseWidthCNT	((unsigned short)300)        //MinPulseWidth/CLOCK_PERIOD (2us)
#define Half_MinPulseWidthCNT	((unsigned short)150)	//half MinPulseWidth/CLOCK_PERIOD (1us)	

//Mathematical Constants
#define PI      		((double)(3.141592653589793)) // pi
#define TWO_PI      	((double)(6.283185307179586)) // 2 * pi
#define THREE_PI_DIV_2	((double)(4.712388980384690)) // '3*pi/2'
#define PI_DIV_2 		((double)(1.570796326794897)) // 'pi/2'
#define PI_DIV_6		((double)(0.523599)) // 'pi/6'
#define PI_DIV_3		((double)(1.047198)) // 'pi/3'
#define TWO_PI_DIV_3	((double)(2.094395)) // '2*pi/3'
#define FOUR_PI_DIV_3	((double)(4.18879)) // '4*pi/3'
#define FIVE_PI_DIV_3	((double)(5.235988)) // '5*pi/3'

#define  SQRT_2  ((double)1.41421356237309) // sqrt(2)
#define  SQRT_3  ((double)1.73205080756887) // sqrt(3)

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
#define DEG_30_TO_RAD  ((double)0.523598775598299) // '30 deg --> rad'
#define DEG_60_TO_RAD  ((double)1.047197551196598) // '60 deg --> rad'9
#define DEG_90_TO_RAD  ((double)1.570796326794897) // '90 deg --> rad'
#define DEG_120_TO_RAD ((double)2.094395102393195) // '120 deg --> rad'
#define DEG_180_TO_RAD ((double)3.141592653589793) // '180 deg --> rad'
#define DEG_240_TO_RAD ((double)4.188790204786391) // '240 deg --> rad'
#define DEG_300_TO_RAD ((double)5.235987755982989) // '300 deg --> rad'
#define DEG_360_TO_RAD ((double)6.283185307179586) // '360 deg --> rad'

#define d_axis			0
#define	q_axis			1
#define	z_seq			2


#define ALPHA_AX		0
#define BETA_AX			1
#define ZERO_SEQ		2

#endif  


//===========================================================================
// End of file.
//===========================================================================
