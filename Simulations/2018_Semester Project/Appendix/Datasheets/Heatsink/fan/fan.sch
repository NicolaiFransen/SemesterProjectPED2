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
$Comp
L C C1
U 1 1 5ACDEC5B
P 4600 4250
F 0 "C1" H 4625 4350 50  0000 L CNN
F 1 "330n" H 4625 4150 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 4638 4100 50  0001 C CNN
F 3 "" H 4600 4250 50  0001 C CNN
	1    4600 4250
	1    0    0    -1  
$EndComp
$Comp
L uA7812 U1
U 1 1 5ACDED0F
P 5100 3750
F 0 "U1" H 4950 3875 50  0000 C CNN
F 1 "TS7812" H 5100 3875 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Horizontal" H 5125 3600 50  0001 L CIN
F 3 "" H 5100 3700 50  0001 C CNN
	1    5100 3750
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5ACDEE4A
P 5600 4250
F 0 "C2" H 5625 4350 50  0000 L CNN
F 1 "100n" H 5625 4150 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 5638 4100 50  0001 C CNN
F 3 "" H 5600 4250 50  0001 C CNN
	1    5600 4250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5ACDF05A
P 4600 4450
F 0 "#PWR01" H 4600 4200 50  0001 C CNN
F 1 "GND" H 4600 4300 50  0000 C CNN
F 2 "" H 4600 4450 50  0001 C CNN
F 3 "" H 4600 4450 50  0001 C CNN
	1    4600 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5ACDF077
P 5600 4450
F 0 "#PWR02" H 5600 4200 50  0001 C CNN
F 1 "GND" H 5600 4300 50  0000 C CNN
F 2 "" H 5600 4450 50  0001 C CNN
F 3 "" H 5600 4450 50  0001 C CNN
	1    5600 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5ACDF0BB
P 5100 4100
F 0 "#PWR03" H 5100 3850 50  0001 C CNN
F 1 "GND" H 5100 3950 50  0000 C CNN
F 2 "" H 5100 4100 50  0001 C CNN
F 3 "" H 5100 4100 50  0001 C CNN
	1    5100 4100
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5ACDF22B
P 7100 4800
F 0 "R1" V 7180 4800 50  0000 C CNN
F 1 "180" V 7100 4800 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 7030 4800 50  0001 C CNN
F 3 "" H 7100 4800 50  0001 C CNN
	1    7100 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 3500 4600 4100
Wire Wire Line
	4600 3750 4800 3750
Connection ~ 4600 3750
Wire Wire Line
	5400 3750 5850 3750
Wire Wire Line
	5600 3750 5600 4100
Wire Wire Line
	4600 4400 4600 4450
Wire Wire Line
	5600 4400 5600 4450
Wire Wire Line
	5100 4050 5100 4100
Connection ~ 5600 3750
Wire Wire Line
	7500 4800 7250 4800
Wire Wire Line
	7800 4300 7800 4600
Connection ~ 7800 4350
$Comp
L GND #PWR04
U 1 1 5ACDF339
P 7800 5200
F 0 "#PWR04" H 7800 4950 50  0001 C CNN
F 1 "GND" H 7800 5050 50  0000 C CNN
F 2 "" H 7800 5200 50  0001 C CNN
F 3 "" H 7800 5200 50  0001 C CNN
	1    7800 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 5000 7800 5200
Wire Wire Line
	6950 4800 6400 4800
$Comp
L Conn_01x02 J1
U 1 1 5ACDFDEB
P 9000 3750
F 0 "J1" H 9000 3850 50  0000 C CNN
F 1 "SUNON FAN" H 9000 3550 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 9000 3750 50  0001 C CNN
F 3 "" H 9000 3750 50  0001 C CNN
	1    9000 3750
	1    0    0    -1  
$EndComp
Text GLabel 8700 3750 0    60   Input ~ 0
Fan+
Wire Wire Line
	8800 3750 8700 3750
Text GLabel 8700 3850 0    60   Input ~ 0
Fan-
Wire Wire Line
	8800 3850 8700 3850
Text GLabel 5850 3750 2    60   Input ~ 0
Fan+
Text GLabel 7800 4300 1    60   Input ~ 0
Fan-
$Comp
L +24V #PWR05
U 1 1 5ACE0202
P 4600 3500
F 0 "#PWR05" H 4600 3350 50  0001 C CNN
F 1 "+24V" H 4600 3640 50  0000 C CNN
F 2 "" H 4600 3500 50  0001 C CNN
F 3 "" H 4600 3500 50  0001 C CNN
	1    4600 3500
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q1
U 1 1 5ACE03AB
P 7700 4800
F 0 "Q1" H 7900 4850 50  0000 L CNN
F 1 "CPH3448" H 7900 4750 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 7900 4900 50  0001 C CNN
F 3 "" H 7700 4800 50  0001 C CNN
	1    7700 4800
	1    0    0    -1  
$EndComp
Text GLabel 6400 4800 0    60   Input ~ 0
Controller
$EndSCHEMATC
