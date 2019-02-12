EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Ucenje-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 5600 3400 0    60   Input ~ 0
Uref
Text GLabel 7850 2700 1    60   Input ~ 0
+15
Text GLabel 6600 2950 1    60   Input ~ 0
+15
$Comp
L R R1
U 1 1 5AD5EF4B
P 6500 2250
F 0 "R1" V 6580 2250 50  0000 C CNN
F 1 "430k" V 6500 2250 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 6430 2250 50  0001 C CNN
F 3 "" H 6500 2250 50  0001 C CNN
	1    6500 2250
	0    1    1    0   
$EndComp
Text GLabel 9450 1800 1    60   Input ~ 0
Uin
$Comp
L R R3
U 1 1 5AD5F2D5
P 2500 3300
F 0 "R3" V 2580 3300 50  0000 C CNN
F 1 "39k" V 2500 3300 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 2430 3300 50  0001 C CNN
F 3 "" H 2500 3300 50  0001 C CNN
	1    2500 3300
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5AD5F34B
P 2500 3850
F 0 "R4" V 2580 3850 50  0000 C CNN
F 1 "5.1k" V 2500 3850 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 2430 3850 50  0001 C CNN
F 3 "" H 2500 3850 50  0001 C CNN
	1    2500 3850
	1    0    0    -1  
$EndComp
Text GLabel 2950 3550 2    60   Input ~ 0
OpIn
Text GLabel 5600 3200 0    60   Input ~ 0
OpIn
$Comp
L R R5
U 1 1 5AD60192
P 1900 5800
F 0 "R5" V 1980 5800 50  0000 C CNN
F 1 "30k" V 1900 5800 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 1830 5800 50  0001 C CNN
F 3 "" H 1900 5800 50  0001 C CNN
	1    1900 5800
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 5AD60198
P 1900 6350
F 0 "R6" V 1980 6350 50  0000 C CNN
F 1 "15k" V 1900 6350 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 1830 6350 50  0001 C CNN
F 3 "" H 1900 6350 50  0001 C CNN
	1    1900 6350
	1    0    0    -1  
$EndComp
Text GLabel 1350 5550 0    60   Input ~ 0
+15
Text GLabel 2350 6050 2    60   Input ~ 0
Uref
$Comp
L OP179GS U1
U 1 1 5AD5E98B
P 6700 3300
F 0 "U1" H 6700 3550 50  0000 L CNN
F 1 "OPA197IDGKR " H 6700 3450 50  0000 L CNN
F 2 "Housings_SSOP:VSSOP-8_3.0x3.0mm_Pitch0.65mm" H 6700 3300 50  0001 C CNN
F 3 "" H 6850 3450 50  0001 C CNN
	1    6700 3300
	1    0    0    -1  
$EndComp
$Comp
L LM317_3PinPackage U2
U 1 1 5ADCC378
P 4600 5650
F 0 "U2" H 4450 5775 50  0000 C CNN
F 1 "LM317_3PinPackage" H 4600 5775 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 4600 5900 50  0001 C CIN
F 3 "" H 4600 5650 50  0001 C CNN
	1    4600 5650
	1    0    0    -1  
$EndComp
Text GLabel 3950 5650 0    60   Input ~ 0
Uin
$Comp
L R R8
U 1 1 5ADCC647
P 5100 5850
F 0 "R8" V 5180 5850 50  0000 C CNN
F 1 "220" V 5100 5850 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5030 5850 50  0001 C CNN
F 3 "" H 5100 5850 50  0001 C CNN
	1    5100 5850
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 5ADCC6A1
P 5100 6450
F 0 "R9" V 5180 6450 50  0000 C CNN
F 1 "2.4k" V 5100 6450 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5030 6450 50  0001 C CNN
F 3 "" H 5100 6450 50  0001 C CNN
	1    5100 6450
	1    0    0    -1  
$EndComp
Text GLabel 5400 5650 2    60   Input ~ 0
+15
$Comp
L C C1
U 1 1 5ADCCBB7
P 4250 6150
F 0 "C1" H 4275 6250 50  0000 L CNN
F 1 "0.1uF" H 4275 6050 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 4288 6000 50  0001 C CNN
F 3 "" H 4250 6150 50  0001 C CNN
	1    4250 6150
	1    0    0    -1  
$EndComp
$Comp
L CP1 C2
U 1 1 5ADCCE21
P 5350 6150
F 0 "C2" H 5375 6250 50  0000 L CNN
F 1 "1uF" H 5375 6050 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 5350 6150 50  0001 C CNN
F 3 "" H 5350 6150 50  0001 C CNN
	1    5350 6150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5ADCD076
P 4750 6650
F 0 "#PWR01" H 4750 6400 50  0001 C CNN
F 1 "GND" H 4750 6500 50  0000 C CNN
F 2 "" H 4750 6650 50  0001 C CNN
F 3 "" H 4750 6650 50  0001 C CNN
	1    4750 6650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5ADCD1CE
P 1350 6700
F 0 "#PWR02" H 1350 6450 50  0001 C CNN
F 1 "GND" H 1350 6550 50  0000 C CNN
F 2 "" H 1350 6700 50  0001 C CNN
F 3 "" H 1350 6700 50  0001 C CNN
	1    1350 6700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5ADCD229
P 7950 4200
F 0 "#PWR03" H 7950 3950 50  0001 C CNN
F 1 "GND" H 7950 4050 50  0000 C CNN
F 2 "" H 7950 4200 50  0001 C CNN
F 3 "" H 7950 4200 50  0001 C CNN
	1    7950 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5ADCD2D1
P 9450 3950
F 0 "#PWR04" H 9450 3700 50  0001 C CNN
F 1 "GND" H 9450 3800 50  0000 C CNN
F 2 "" H 9450 3950 50  0001 C CNN
F 3 "" H 9450 3950 50  0001 C CNN
	1    9450 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5ADCD40C
P 6600 3650
F 0 "#PWR05" H 6600 3400 50  0001 C CNN
F 1 "GND" H 6600 3500 50  0000 C CNN
F 2 "" H 6600 3650 50  0001 C CNN
F 3 "" H 6600 3650 50  0001 C CNN
	1    6600 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5ADCD447
P 1950 4150
F 0 "#PWR06" H 1950 3900 50  0001 C CNN
F 1 "GND" H 1950 4000 50  0000 C CNN
F 2 "" H 1950 4150 50  0001 C CNN
F 3 "" H 1950 4150 50  0001 C CNN
	1    1950 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3200 6400 3200
Wire Wire Line
	7000 2250 7000 3300
Wire Wire Line
	6650 2250 7000 2250
Wire Wire Line
	6400 3400 5600 3400
Wire Wire Line
	7000 3300 8000 3300
Wire Wire Line
	6350 2250 6250 2250
Wire Wire Line
	6250 2250 6250 3200
Connection ~ 6250 3200
Wire Wire Line
	9100 2650 9750 2650
Wire Wire Line
	9200 2050 9200 2300
Wire Wire Line
	9200 2050 9650 2050
Wire Wire Line
	9450 2050 9450 1800
Connection ~ 9450 2050
Wire Wire Line
	1950 3050 2500 3050
Wire Wire Line
	2500 3050 2500 3150
Wire Wire Line
	2500 3450 2500 3700
Wire Wire Line
	2500 4100 2500 4000
Wire Wire Line
	1950 4100 2500 4100
Wire Wire Line
	2500 3550 2950 3550
Connection ~ 2500 3550
Wire Wire Line
	1900 5950 1900 6200
Wire Wire Line
	1900 6500 1900 6600
Wire Wire Line
	1900 6600 1350 6600
Wire Wire Line
	1900 6050 2350 6050
Connection ~ 1900 6050
Wire Wire Line
	9450 2650 9450 3100
Wire Wire Line
	1900 5650 1900 5550
Wire Wire Line
	1900 5550 1350 5550
Wire Wire Line
	6600 2950 6600 3000
Wire Wire Line
	6600 3650 6600 3600
Wire Wire Line
	1950 4100 1950 4150
Connection ~ 6600 3600
Connection ~ 6600 3000
Wire Wire Line
	1350 6600 1350 6700
Wire Wire Line
	4900 5650 5400 5650
Wire Wire Line
	5100 5650 5100 5700
Connection ~ 5100 5650
Wire Wire Line
	5100 6000 5100 6300
Wire Wire Line
	5100 6150 4600 6150
Wire Wire Line
	4600 6150 4600 5950
Connection ~ 5100 6150
Wire Wire Line
	4250 6600 4250 6300
Wire Wire Line
	4250 6000 4250 5650
Wire Wire Line
	3950 5650 4300 5650
Wire Wire Line
	4250 6600 5350 6600
Wire Wire Line
	5350 6000 5350 5650
Connection ~ 5350 5650
Wire Wire Line
	5350 6600 5350 6300
Connection ~ 5100 6600
Text Notes 7550 7500 0    60   ~ 0
Dc Chopper \n
$Comp
L GND #PWR07
U 1 1 5ADCF9F7
P 1800 1350
F 0 "#PWR07" H 1800 1100 50  0001 C CNN
F 1 "GND" H 1800 1200 50  0000 C CNN
F 2 "" H 1800 1350 50  0001 C CNN
F 3 "" H 1800 1350 50  0001 C CNN
	1    1800 1350
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG08
U 1 1 5ADCFE31
P 2200 3050
F 0 "#FLG08" H 2200 3125 50  0001 C CNN
F 1 "PWR_FLAG" H 2200 3200 50  0000 C CNN
F 2 "" H 2200 3050 50  0001 C CNN
F 3 "" H 2200 3050 50  0001 C CNN
	1    2200 3050
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG09
U 1 1 5ADCFEBA
P 2200 4100
F 0 "#FLG09" H 2200 4175 50  0001 C CNN
F 1 "PWR_FLAG" H 2200 4250 50  0000 C CNN
F 2 "" H 2200 4100 50  0001 C CNN
F 3 "" H 2200 4100 50  0001 C CNN
	1    2200 4100
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG010
U 1 1 5ADD0254
P 1650 5550
F 0 "#FLG010" H 1650 5625 50  0001 C CNN
F 1 "PWR_FLAG" H 1650 5700 50  0000 C CNN
F 2 "" H 1650 5550 50  0001 C CNN
F 3 "" H 1650 5550 50  0001 C CNN
	1    1650 5550
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG011
U 1 1 5ADD0292
P 1600 6600
F 0 "#FLG011" H 1600 6675 50  0001 C CNN
F 1 "PWR_FLAG" H 1600 6750 50  0000 C CNN
F 2 "" H 1600 6600 50  0001 C CNN
F 3 "" H 1600 6600 50  0001 C CNN
	1    1600 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 2700 7850 3200
Wire Wire Line
	7950 3500 7950 4200
$Comp
L PWR_FLAG #FLG012
U 1 1 5ADD0846
P 9450 3750
F 0 "#FLG012" H 9450 3825 50  0001 C CNN
F 1 "PWR_FLAG" H 9450 3900 50  0000 C CNN
F 2 "" H 9450 3750 50  0001 C CNN
F 3 "" H 9450 3750 50  0001 C CNN
	1    9450 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	4750 6650 4750 6600
Connection ~ 4750 6600
$Comp
L FAN3122 U3
U 1 1 5ADDBFAC
P 8200 3450
F 0 "U3" H 8200 3450 60  0000 C CNN
F 1 "FAN3122" H 8250 3300 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 8200 3450 60  0001 C CNN
F 3 "" H 8200 3450 60  0001 C CNN
	1    8200 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3200 8000 3200
Wire Wire Line
	8000 3500 7950 3500
Wire Wire Line
	7750 3800 7950 3800
$Comp
L R R7
U 1 1 5ADDC3C8
P 9000 3300
F 0 "R7" V 9080 3300 50  0000 C CNN
F 1 "1.6" V 9000 3300 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 8930 3300 50  0001 C CNN
F 3 "" H 9000 3300 50  0001 C CNN
	1    9000 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	8750 3400 8850 3400
Wire Wire Line
	8850 3400 8850 3300
Connection ~ 8850 3300
Wire Wire Line
	8850 3300 8750 3300
$Comp
L Conn_01x02 J1
U 1 1 5ADDD5F4
P 2250 1250
F 0 "J1" H 2250 1350 50  0000 C CNN
F 1 "Dc-Link" V 1500 1250 50  0000 C CNN
F 2 "Kicad stuff:WireConnection_2.50mmDrill" H 2250 1250 50  0001 C CNN
F 3 "" H 2250 1250 50  0001 C CNN
	1    2250 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1250 2050 1250
Wire Wire Line
	2050 1350 1800 1350
$Comp
L Q_NMOS_GSD Q1
U 1 1 5ADDE11B
P 9350 3300
F 0 "Q1" H 9550 3350 50  0000 L CNN
F 1 "Q_NMOS_GSD" H 9550 3250 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:Infineon_PG-HSOF-8-1" H 9550 3400 50  0001 C CNN
F 3 "" H 9350 3300 50  0001 C CNN
	1    9350 3300
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J2
U 1 1 5ADDE720
P 9400 2300
F 0 "J2" H 9400 2400 50  0000 C CNN
F 1 "Power_Res_conn" H 9400 2100 50  0000 C CNN
F 2 "Kicad stuff:WireConnection_2.50mmDrill" H 9400 2300 50  0001 C CNN
F 3 "" H 9400 2300 50  0001 C CNN
	1    9400 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 2400 9100 2400
Wire Wire Line
	9100 2400 9100 2650
Wire Notes Line
	5900 5250 3650 5250
Wire Notes Line
	2800 5200 950  5200
Text Notes 3600 6700 1    60   ~ 0
Linear voltage regulato  15 V\n
Text Notes 1000 6500 1    60   ~ 0
Reference voltage  5 v\n
Wire Notes Line
	10400 1500 4750 1500
Text Notes 6300 1800 0    60   ~ 0
Dc Chopper\n
Connection ~ 7000 3300
Connection ~ 2200 3050
Connection ~ 2200 4100
Connection ~ 4250 5650
Wire Wire Line
	9450 3500 9450 3950
Connection ~ 9450 2650
NoConn ~ 8000 3400
Text GLabel 8850 2800 1    60   Input ~ 0
+15
$Comp
L GND #PWR013
U 1 1 5AF0514F
P 8850 4200
F 0 "#PWR013" H 8850 3950 50  0001 C CNN
F 1 "GND" H 8850 4050 50  0000 C CNN
F 2 "" H 8850 4200 50  0001 C CNN
F 3 "" H 8850 4200 50  0001 C CNN
	1    8850 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 3500 8850 3500
Wire Wire Line
	8850 3500 8850 4200
Wire Wire Line
	8850 2800 8850 3200
Wire Wire Line
	8750 3200 9200 3200
$Comp
L C C3
U 1 1 5AF058B6
P 7750 3500
F 0 "C3" H 7775 3600 50  0000 L CNN
F 1 "1uF" H 7775 3400 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7788 3350 50  0001 C CNN
F 3 "" H 7750 3500 50  0001 C CNN
	1    7750 3500
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5AF05A5E
P 9200 3550
F 0 "C4" H 9225 3650 50  0000 L CNN
F 1 "100nF" H 9225 3450 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 9238 3400 50  0001 C CNN
F 3 "" H 9200 3550 50  0001 C CNN
	1    9200 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3200 7750 3350
Connection ~ 7850 3200
Wire Wire Line
	7750 3650 7750 3800
Connection ~ 7950 3800
Wire Wire Line
	9200 3200 9200 3400
Connection ~ 8850 3200
Wire Wire Line
	9200 3700 9200 3800
Wire Wire Line
	9200 3800 8850 3800
Connection ~ 8850 3800
$Comp
L R R2
U 1 1 5AF06405
P 6000 3200
F 0 "R2" V 6080 3200 50  0000 C CNN
F 1 "3k" V 6000 3200 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5930 3200 50  0001 C CNN
F 3 "" H 6000 3200 50  0001 C CNN
	1    6000 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	5600 3200 5850 3200
Wire Notes Line
	1400 900  2350 900 
Text GLabel 1850 1250 0    60   Input ~ 0
Uin
Text GLabel 1950 3050 0    60   Input ~ 0
Uin
Wire Notes Line
	1600 2850 3300 2850
$Comp
L D_Schottky_AKA D1
U 1 1 5AF19686
P 9650 2300
F 0 "D1" H 9650 2400 50  0000 C CNN
F 1 "D_Schottky_AKA" H 9650 2200 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 9650 2300 50  0001 C CNN
F 3 "" H 9650 2300 50  0001 C CNN
	1    9650 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	9750 2650 9750 2500
Wire Wire Line
	9650 2050 9650 2150
Wire Wire Line
	9650 2500 9650 2650
Connection ~ 9650 2650
$EndSCHEMATC
