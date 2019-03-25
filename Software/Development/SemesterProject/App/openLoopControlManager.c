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
static float currentCyclePos[3] = {0,0,0};

//LUT for sine wave.
//Sine wave has an offset to be compared easily with a reference to set duty cycle, minimum value is then 0.
//It has three significant figures in the integer form, with values ranging from 0 to 1000.
const int16 sineLut[SINE_LUT_LENGTH] = {500, 503, 506, 509, 513, 516, 519, 522, 525, 528, 531, 534, 538, 541, 544, 547, 550, 553, 556, 559, 563, 566, 569, 572, 575, 578, 581, 584, 587, 590, 594, 597, 600, 603, 606, 609, 612, 615, 618, 621, 624, 627, 630, 633, 636, 639, 642, 645, 648, 651, 654, 657, 660, 663, 666, 669, 672, 675, 678, 681, 684, 687, 690, 692, 695, 698, 701, 704, 707, 710, 712, 715, 718, 721, 724, 727, 729, 732, 735, 738, 740, 743, 746, 749, 751, 754, 757, 759, 762, 765, 767, 770, 773, 775, 778, 781, 783, 786, 788, 791, 793, 796, 798, 801, 803, 806, 808, 811, 813, 816, 818, 821, 823, 825, 828, 830, 832, 835, 837, 839, 842, 844, 846, 849, 851, 853, 855, 857, 860, 862, 864, 866, 868, 870, 872, 874, 877, 879, 881, 883, 885, 887, 889, 891, 893, 895, 896, 898, 900, 902, 904, 906, 908, 909, 911, 913, 915, 916, 918, 920, 922, 923, 925, 927, 928, 930, 931, 933, 935, 936, 938, 939, 941, 942, 944, 945, 946, 948, 949, 951, 952, 953, 955, 956, 957, 958, 960, 961, 962, 963, 964, 966, 967, 968, 969, 970, 971, 972, 973, 974, 975, 976, 977, 978, 979, 980, 981, 982, 982, 983, 984, 985, 985, 986, 987, 988, 988, 989, 990, 990, 991, 991, 992, 993, 993, 994, 994, 995, 995, 995, 996, 996, 997, 997, 997, 998, 998, 998, 998, 999, 999, 999, 999, 999, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 999, 999, 999, 999, 999, 998, 998, 998, 998, 997, 997, 997, 996, 996, 995, 995, 995, 994, 994, 993, 993, 992, 991, 991, 990, 990, 989, 988, 988, 987, 986, 985, 985, 984, 983, 982, 982, 981, 980, 979, 978, 977, 976, 975, 974, 973, 972, 971, 970, 969, 968, 967, 966, 964, 963, 962, 961, 960, 958, 957, 956, 955, 953, 952, 951, 949, 948, 946, 945, 944, 942, 941, 939, 938, 936, 935, 933, 931, 930, 928, 927, 925, 923, 922, 920, 918, 916, 915, 913, 911, 909, 908, 906, 904, 902, 900, 898, 896, 895, 893, 891, 889, 887, 885, 883, 881, 879, 877, 874, 872, 870, 868, 866, 864, 862, 860, 857, 855, 853, 851, 849, 846, 844, 842, 839, 837, 835, 832, 830, 828, 825, 823, 821, 818, 816, 813, 811, 808, 806, 803, 801, 798, 796, 793, 791, 788, 786, 783, 781, 778, 775, 773, 770, 767, 765, 762, 759, 757, 754, 751, 749, 746, 743, 740, 738, 735, 732, 729, 727, 724, 721, 718, 715, 712, 710, 707, 704, 701, 698, 695, 692, 690, 687, 684, 681, 678, 675, 672, 669, 666, 663, 660, 657, 654, 651, 648, 645, 642, 639, 636, 633, 630, 627, 624, 621, 618, 615, 612, 609, 606, 603, 600, 597, 594, 590, 587, 584, 581, 578, 575, 572, 569, 566, 563, 559, 556, 553, 550, 547, 544, 541, 538, 534, 531, 528, 525, 522, 519, 516, 513, 509, 506, 503, 500, 497, 494, 491, 487, 484, 481, 478, 475, 472, 469, 466, 462, 459, 456, 453, 450, 447, 444, 441, 437, 434, 431, 428, 425, 422, 419, 416, 413, 410, 406, 403, 400, 397, 394, 391, 388, 385, 382, 379, 376, 373, 370, 367, 364, 361, 358, 355, 352, 349, 346, 343, 340, 337, 334, 331, 328, 325, 322, 319, 316, 313, 310, 308, 305, 302, 299, 296, 293, 290, 288, 285, 282, 279, 276, 273, 271, 268, 265, 262, 260, 257, 254, 251, 249, 246, 243, 241, 238, 235, 233, 230, 227, 225, 222, 219, 217, 214, 212, 209, 207, 204, 202, 199, 197, 194, 192, 189, 187, 184, 182, 179, 177, 175, 172, 170, 168, 165, 163, 161, 158, 156, 154, 151, 149, 147, 145, 143, 140, 138, 136, 134, 132, 130, 128, 126, 123, 121, 119, 117, 115, 113, 111, 109, 107, 105, 104, 102, 100, 98, 96, 94, 92, 91, 89, 87, 85, 84, 82, 80, 78, 77, 75, 73, 72, 70, 69, 67, 65, 64, 62, 61, 59, 58, 56, 55, 54, 52, 51, 49, 48, 47, 45, 44, 43, 42, 40, 39, 38, 37, 36, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 18, 17, 16, 15, 15, 14, 13, 12, 12, 11, 10, 10, 9, 9, 8, 7, 7, 6, 6, 5, 5, 5, 4, 4, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5, 6, 6, 7, 7, 8, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 36, 37, 38, 39, 40, 42, 43, 44, 45, 47, 48, 49, 51, 52, 54, 55, 56, 58, 59, 61, 62, 64, 65, 67, 69, 70, 72, 73, 75, 77, 78, 80, 82, 84, 85, 87, 89, 91, 92, 94, 96, 98, 100, 102, 104, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 126, 128, 130, 132, 134, 136, 138, 140, 143, 145, 147, 149, 151, 154, 156, 158, 161, 163, 165, 168, 170, 172, 175, 177, 179, 182, 184, 187, 189, 192, 194, 197, 199, 202, 204, 207, 209, 212, 214, 217, 219, 222, 225, 227, 230, 233, 235, 238, 241, 243, 246, 249, 251, 254, 257, 260, 262, 265, 268, 271, 273, 276, 279, 282, 285, 288, 290, 293, 296, 299, 302, 305, 308, 310, 313, 316, 319, 322, 325, 328, 331, 334, 337, 340, 343, 346, 349, 352, 355, 358, 361, 364, 367, 370, 373, 376, 379, 382, 385, 388, 391, 394, 397, 400, 403, 406, 410, 413, 416, 419, 422, 425, 428, 431, 434, 437, 441, 444, 447, 450, 453, 456, 459, 462, 466, 469, 472, 475, 478, 481, 484, 487, 491, 494, 497};

//Max line to line voltage divided by DC voltage (to be updated when measured) and divided by freq to get vf control.
const float vfConst = ( 24 * 1.414214 / 36 ) / MAX_STATOR_FREQ;


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


/*
 * This function sets all the PWM signals to a constant value
 * obtained from a reference.
 */
void setConstantDutyFromReference(void)
{
    float duty;
    float torqueRef, maxRef;
    /*  INCLUDE THIS WHEN EVERYTHING IS ADDED
    switch (getReferenceInput())
    {
        case POT:
        {
            torqueRef = getTorqueReferenceSliderMeasurement();
            maxRef = getMaximumReferenceValue();
        }break;
        case GUI:
        {
            torqueRef = getTorqueReferenceFromGUI();
            maxRef = getMaximumReferenceGUI();
        }
        case PEDAL:
        {
            torqueRef = getTorqueReferenceFromPedal();
            maxRef = getMaximumReferencePedal();
        }

    }*/

    torqueRef = getTorqueReferenceSliderMeasurement();
    maxRef = 3.3;//getMaximumReferenceADC();

    duty = mapFloat(torqueRef, maxRef, readMaxDuty());

    setAllDuties(duty);
}


//
//Function called at switching frequency.
//It sets VF control on the motor according to the torque reference potentiometer.
//
void openLoopVFControl(void)
{
    float statorFreq;
    float stepsPerCycle;
    float dutyA, dutyB, dutyC;
    int phaseToUpdate = 0;
    float vfFactor;
    float torqueRef, maxRef;

    /*  INCLUDE THIS WHEN EVERYTHING IS ADDED
    switch (getReferenceInput())
    {
        case POT:
        {
            torqueRef = getTorqueReferenceSliderMeasurement();
            maxRef = getMaximumReferenceADC();
        }break;
        case GUI:
        {
            torqueRef = getTorqueReferenceFromGUI();
            maxRef = getMaximumReferenceGUI();
        }
        case PEDAL:
        {
            torqueRef = getTorqueReferenceFromPedal();
            maxRef = getMaximumReferenceADC();
        }

    }*/


    torqueRef = getTorqueReferenceSliderMeasurement();
    maxRef = 3.3;//getMaximumReferenceADC();

    //Calculate at what frequency the stator should go according to input.
    statorFreq = mapFloat(torqueRef, maxRef, MAX_STATOR_FREQ);

    //VF factor value. This value is calculated assuming that at max
    //frequency, the sine goes all the way up to battery voltage.
    vfFactor = statorFreq * vfConst;

    //The higher the frequency the more steps to advance in the LUT per cycle.
    stepsPerCycle = statorFreq * SINE_LUT_LENGTH / SW_FREQ;

    //Update current cycle position in all phases.
    currentCyclePos[phaseToUpdate] += stepsPerCycle;
    for (phaseToUpdate = 0; phaseToUpdate < 3; phaseToUpdate++)
    {
        currentCyclePos[phaseToUpdate] = currentCyclePos[0] + phaseToUpdate * SINE_LUT_LENGTH/3;
        if (currentCyclePos[phaseToUpdate] >= SINE_LUT_LENGTH) {currentCyclePos[phaseToUpdate] -= SINE_LUT_LENGTH;}
    }

    //Calculate duty value.
    dutyA = vfFactor * sineLut[(int16) currentCyclePos[0]]/10;
    dutyB = vfFactor * sineLut[(int16) currentCyclePos[1]]/10;
    dutyC = vfFactor * sineLut[(int16) currentCyclePos[2]]/10;

    //Set duties.
    setDutyA(dutyA);
    setDutyB(dutyB);
    setDutyC(dutyC);
}
