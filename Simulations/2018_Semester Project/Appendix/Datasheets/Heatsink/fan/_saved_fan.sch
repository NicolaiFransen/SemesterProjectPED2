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
LIBS:fan-cache
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
P 3350 3750
F 0 "C1" H 3375 3850 50  0000 L CNN
F 1 "330n" H 3375 3650 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 3388 3600 50  0001 C CNN
F 3 "" H 3350 3750 50  0001 C CNN
	1    3350 3750
	1    0    0    -1  
$EndComp
$Comp
L uA7812 U1
U 1 1 5ACDED0F
P 3850 3250
F 0 "U1" H 3700 3375 50  0000 C CNN
F 1 "TS7812" H 3850 3375 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Horizontal" H 3875 3100 50  0001 L CIN
F 3 "" H 3850 3200 50  0001 C CNN
	1    3850 3250
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5ACDEE4A
P 4350 3750
F 0 "C2" H 4375 3850 50  0000 L CNN
F 1 "100n" H 4375 3650 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 4388 3600 50  0001 C CNN
F 3 "" H 4350 3750 50  0001 C CNN
	1    4350 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5ACDF05A
P 3350 3950
F 0 "#PWR01" H 3350 3700 50  0001 C CNN
F 1 "GND" H 3350 3800 50  0000 C CNN
F 2 "" H 3350 3950 50  0001 C CNN
F 3 "" H 3350 3950 50  0001 C CNN
	1    3350 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5ACDF077
P 4350 3950
F 0 "#PWR02" H 4350 3700 50  0001 C CNN
F 1 "GND" H 4350 3800 50  0000 C CNN
F 2 "" H 4350 3950 50  0001 C CNN
F 3 "" H 4350 3950 50  0001 C CNN
	1    4350 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5ACDF0BB
P 3850 3600
F 0 "#PWR03" H 3850 3350 50  0001 C CNN
F 1 "GND" H 3850 3450 50  0000 C CNN
F 2 "" H 3850 3600 50  0001 C CNN
F 3 "" H 3850 3600 50  0001 C CNN
	1    3850 3600
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5ACDF22B
P 5850 4300
F 0 "R1" V 5930 4300 50  0000 C CNN
F 1 "180" V 5850 4300 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5780 4300 50  0001 C CNN
F 3 "" H 5850 4300 50  0001 C CNN
	1    5850 4300
	0    1    1    0   
$EndComp
Wire Wire Line
	3350 3000 3350 3600
Wire Wire Line
	3350 3250 3550 3250
Connection ~ 3350 3250
Wire Wire Line
	4150 3250 4600 3250
Wire Wire Line
	4350 3250 4350 3600
Wire Wire Line
	3350 3900 3350 3950
Wire Wire Line
	4350 3900 4350 3950
Wire Wire Line
	3850 3550 3850 3600
Connection ~ 4350 3250
Wire Wire Line
	6250 4300 6000 4300
Wire Wire Line
	6550 3800 6550 4100
Connection ~ 6550 3850
$Comp
L GND #PWR04
U 1 1 5ACDF339
P 6550 4700
F 0 "#PWR04" H 6550 4450 50  0001 C CNN
F 1 "GND" H 6550 4550 50  0000 C CNN
F 2 "" H 6550 4700 50  0001 C CNN
F 3 "" H 6550 4700 50  0001 C CNN
	1    6550 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 4500 6550 4700
Wire Wire Line
	5700 4300 5150 4300
$Comp
L Conn_01x02 J1
U 1 1 5ACDFDEB
P 7750 3250
F 0 "J1" H 7750 3350 50  0000 C CNN
F 1 "SUNON FAN" H 7750 3050 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 7750 3250 50  0001 C CNN
F 3 "" H 7750 3250 50  0001 C CNN
	1    7750 3250
	1    0    0    -1  
$EndComp
Text GLabel 7450 3250 0    60   Input ~ 0
Fan+
Wire Wire Line
	7550 3250 7450 3250
Text GLabel 7450 3350 0    60   Input ~ 0
Fan-
Wire Wire Line
	7550 3350 7450 3350
Text GLabel 4600 3250 2    60   Input ~ 0
Fan+
Text GLabel 6550 3800 1    60   Input ~ 0
Fan-
$Comp
L +24V #PWR05
U 1 1 5ACE0202
P 3350 3000
F 0 "#PWR05" H 3350 2850 50  0001 C CNN
F 1 "+24V" H 3350 3140 50  0000 C CNN
F 2 "" H 3350 3000 50  0001 C CNN
F 3 "" H 3350 3000 50  0001 C CNN
	1    3350 3000
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q1
U 1 1 5ACE03AB
P 6450 4300
F 0 "Q1" H 6650 4350 50  0000 L CNN
F 1 "CPH3448" H 6650 4250 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 6650 4400 50  0001 C CNN
F 3 "" H 6450 4300 50  0001 C CNN
	1    6450 4300
	1    0    0    -1  
$EndComp
Text GLabel 5150 4300 0    60   Input ~ 0
Controller
$EndSCHEMATC
