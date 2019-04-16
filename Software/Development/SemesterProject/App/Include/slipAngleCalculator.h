/*
 * slipAngleCalculator.h
 *
 *  Created on: 15 abr. 2019
 *      Author: Aitor Teran
 */

#ifndef APP_INCLUDE_SLIPANGLECALCULATOR_H_
#define APP_INCLUDE_SLIPANGLECALCULATOR_H_


typedef struct
{
    float speed;
    float position;
} slip;


void readSlipSpeed(void);


#endif /* APP_INCLUDE_SLIPANGLECALCULATOR_H_ */
