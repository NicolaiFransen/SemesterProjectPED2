/*
 * openLoopControlManager.c
 *
 *  Created on: 21 mar. 2019
 *      Author: Aitor Teran
 */


//
// Includes
//
#include "Include/openLoopControlManager.h"


//
//Quasi global variables.
//
static int16 currentCyclePos = 0;
//LUT for sine wave.
const int16 sineLut[SINE_LUT_LENGTH] = {500, 531, 563, 594, 624, 655, 684, 713, 741, 768, 794, 819, 842, 864, 885, 905, 922, 938, 952, 965, 976, 984, 991, 996, 999, 1000, 999, 996, 991, 984, 976, 965, 952, 938, 922, 905, 885, 864, 842, 819, 794, 768, 741, 713, 684, 655, 624, 594, 563, 531, 500, 469, 437, 406, 376, 345, 316, 287, 259, 232, 206, 181, 158, 136, 115, 95, 78, 62, 48, 35, 24, 16, 9, 4, 1, 0, 1, 4, 9, 16, 24, 35, 48, 62, 78, 95, 115, 136, 158, 181, 206, 232, 259, 287, 316, 345, 376, 406, 437, 469};


/*
 * mapFloat maps the value from one reference to another.
 * Assuming only floats and minimum value of 0 for x and y.
 */
float mapFloat(float x, float xMax, float yMax)
{
    return x * yMax / xMax;
}

int16 mapInt(int16 x, int16 xMax, int16 yMax)
{
    return x * yMax / xMax;
}



void setConstantDutyFromPot(void)
{
    setAllDuties(mapFloat(1.2, 3.3, readMaxDuty())); //mapFloat(readADC(), readMaxADC(), readMaxDuty()));
}


//
//This function is called at switching frequency so the duty needs to get updated in every iteration.
//
void setFrequencyFromPot(void)
{
    float statorFreq;
    float dutyA;
    int16 pulsesPerCycle;

    statorFreq = mapFloat(0.05, 3.3, MAX_STATOR_FREQ);//mapFloat(readADC(), readMaxADC(), MAX_STATOR_FREQ);
    pulsesPerCycle = (int16)((float)SW_FREQ / statorFreq);


    dutyA = sineLut[mapInt(currentCyclePos, pulsesPerCycle, SINE_LUT_LENGTH)]/10.0;

    //Update current cycle position
    currentCyclePos ++;
    currentCyclePos %= pulsesPerCycle;

    setDutyA(MA*dutyA);
}
