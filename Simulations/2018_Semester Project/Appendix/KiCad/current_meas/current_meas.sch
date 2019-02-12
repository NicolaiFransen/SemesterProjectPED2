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
LIBS:current_meas-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Current measurement board"
Date "2018-05-27"
Rev "1.0"
Comp "Appendix A.1.6"
Comment1 "Current sensor board, using three hall sensor elements from LEM"
Comment2 "The board requires ±15V"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LEM_LA_200_P T1
U 1 1 5AF3F7B8
P 2450 2600
F 0 "T1" H 2450 2650 60  0000 C CNN
F 1 "LEM_LA_200_P" H 2450 3650 60  0000 C CNN
F 2 "Jespers_footprints:LEM_200" H 2450 2650 60  0001 C CNN
F 3 "" H 2450 2650 60  0001 C CNN
	1    2450 2600
	1    0    0    -1  
$EndComp
NoConn ~ 2950 2250
$Comp
L Conn_01x03 J1
U 1 1 5AF41F40
P 4600 4400
F 0 "J1" H 4600 4600 50  0000 C CNN
F 1 "Power" H 4650 4200 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 4600 4400 50  0001 C CNN
F 3 "" H 4600 4400 50  0001 C CNN
	1    4600 4400
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03 J2
U 1 1 5AF41FAB
P 6550 4350
F 0 "J2" H 6550 4550 50  0000 C CNN
F 1 "Signals" H 6600 4150 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 6550 4350 50  0001 C CNN
F 3 "" H 6550 4350 50  0001 C CNN
	1    6550 4350
	1    0    0    -1  
$EndComp
$Comp
L +15V #PWR01
U 1 1 5AF41FF6
P 4350 4050
F 0 "#PWR01" H 4350 3900 50  0001 C CNN
F 1 "+15V" H 4500 4150 50  0000 C CNN
F 2 "" H 4350 4050 50  0001 C CNN
F 3 "" H 4350 4050 50  0001 C CNN
	1    4350 4050
	1    0    0    -1  
$EndComp
$Comp
L GNDS #PWR02
U 1 1 5AF42014
P 4050 4400
F 0 "#PWR02" H 4050 4150 50  0001 C CNN
F 1 "GNDS" H 4050 4250 50  0000 C CNN
F 2 "" H 4050 4400 50  0001 C CNN
F 3 "" H 4050 4400 50  0001 C CNN
	1    4050 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 4300 4400 4300
Wire Wire Line
	4050 4400 4400 4400
$Comp
L -15V #PWR7
U 1 1 5AF420D8
P 4350 4800
F 0 "#PWR7" H 4350 4900 50  0001 C CNN
F 1 "-15V" H 4200 4900 50  0000 C CNN
F 2 "" H 4350 4800 50  0001 C CNN
F 3 "" H 4350 4800 50  0001 C CNN
	1    4350 4800
	-1   0    0    1   
$EndComp
Wire Wire Line
	4350 4500 4400 4500
Text GLabel 6250 4150 0    60   Input ~ 0
Current_A
Text GLabel 6250 4350 0    60   Input ~ 0
Current_B
Text GLabel 6250 4550 0    60   Input ~ 0
Current_C
Wire Wire Line
	6250 4150 6350 4150
Wire Wire Line
	6350 4150 6350 4250
Wire Wire Line
	6250 4350 6350 4350
Wire Wire Line
	6350 4450 6350 4450
Wire Wire Line
	6350 4450 6350 4550
Wire Wire Line
	6350 4550 6250 4550
$Comp
L -15V #PWR4
U 1 1 5AF421E5
P 1800 2700
F 0 "#PWR4" H 1800 2800 50  0001 C CNN
F 1 "-15V" H 1650 2800 50  0000 C CNN
F 2 "" H 1800 2700 50  0001 C CNN
F 3 "" H 1800 2700 50  0001 C CNN
	1    1800 2700
	-1   0    0    1   
$EndComp
$Comp
L +15V #PWR03
U 1 1 5AF42390
P 1800 1550
F 0 "#PWR03" H 1800 1400 50  0001 C CNN
F 1 "+15V" H 1950 1650 50  0000 C CNN
F 2 "" H 1800 1550 50  0001 C CNN
F 3 "" H 1800 1550 50  0001 C CNN
	1    1800 1550
	1    0    0    -1  
$EndComp
Text GLabel 3100 1950 2    60   Input ~ 0
Current_A
Wire Wire Line
	2950 1950 3100 1950
Wire Wire Line
	1500 2250 1500 2350
Connection ~ 1500 1950
Wire Wire Line
	1800 1550 1800 1950
$Comp
L GNDS #PWR04
U 1 1 5AF435F9
P 1500 2700
F 0 "#PWR04" H 1500 2450 50  0001 C CNN
F 1 "GNDS" H 1500 2550 50  0000 C CNN
F 2 "" H 1500 2700 50  0001 C CNN
F 3 "" H 1500 2700 50  0001 C CNN
	1    1500 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2700 1500 2650
Connection ~ 1500 2250
Wire Wire Line
	1800 2700 1800 2250
Connection ~ 1800 2250
$Comp
L C C1
U 1 1 5AF4378C
P 1500 1750
F 0 "C1" H 1525 1850 50  0000 L CNN
F 1 "0.1u" H 1525 1650 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 1538 1600 50  0001 C CNN
F 3 "" H 1500 1750 50  0001 C CNN
	1    1500 1750
	1    0    0    -1  
$EndComp
$Comp
L GNDS #PWR05
U 1 1 5AF43818
P 1500 1500
F 0 "#PWR05" H 1500 1250 50  0001 C CNN
F 1 "GNDS" H 1500 1350 50  0000 C CNN
F 2 "" H 1500 1500 50  0001 C CNN
F 3 "" H 1500 1500 50  0001 C CNN
	1    1500 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	1500 1600 1500 1500
Connection ~ 1800 1950
$Comp
L C C2
U 1 1 5AF44040
P 1500 2500
F 0 "C2" H 1525 2600 50  0000 L CNN
F 1 "0.1u" H 1525 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 1538 2350 50  0001 C CNN
F 3 "" H 1500 2500 50  0001 C CNN
	1    1500 2500
	1    0    0    -1  
$EndComp
NoConn ~ 6050 2250
$Comp
L -15V #PWR11
U 1 1 5AF442C1
P 4900 2700
F 0 "#PWR11" H 4900 2800 50  0001 C CNN
F 1 "-15V" H 4750 2800 50  0000 C CNN
F 2 "" H 4900 2700 50  0001 C CNN
F 3 "" H 4900 2700 50  0001 C CNN
	1    4900 2700
	-1   0    0    1   
$EndComp
$Comp
L +15V #PWR06
U 1 1 5AF442C7
P 4900 1550
F 0 "#PWR06" H 4900 1400 50  0001 C CNN
F 1 "+15V" H 5050 1650 50  0000 C CNN
F 2 "" H 4900 1550 50  0001 C CNN
F 3 "" H 4900 1550 50  0001 C CNN
	1    4900 1550
	1    0    0    -1  
$EndComp
Text GLabel 6200 1950 2    60   Input ~ 0
Current_B
Wire Wire Line
	6050 1950 6200 1950
Wire Wire Line
	4600 2250 4600 2350
Connection ~ 4600 1950
Wire Wire Line
	4900 1550 4900 1950
$Comp
L GNDS #PWR07
U 1 1 5AF442E1
P 4600 2700
F 0 "#PWR07" H 4600 2450 50  0001 C CNN
F 1 "GNDS" H 4600 2550 50  0000 C CNN
F 2 "" H 4600 2700 50  0001 C CNN
F 3 "" H 4600 2700 50  0001 C CNN
	1    4600 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 2700 4600 2650
Connection ~ 4600 2250
Wire Wire Line
	4900 2700 4900 2250
Connection ~ 4900 2250
$Comp
L C C5
U 1 1 5AF442EE
P 4600 1800
F 0 "C5" H 4625 1900 50  0000 L CNN
F 1 "0.1u" H 4625 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4638 1650 50  0001 C CNN
F 3 "" H 4600 1800 50  0001 C CNN
	1    4600 1800
	1    0    0    -1  
$EndComp
$Comp
L GNDS #PWR08
U 1 1 5AF442FA
P 4600 1550
F 0 "#PWR08" H 4600 1300 50  0001 C CNN
F 1 "GNDS" H 4600 1400 50  0000 C CNN
F 2 "" H 4600 1550 50  0001 C CNN
F 3 "" H 4600 1550 50  0001 C CNN
	1    4600 1550
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 1650 4600 1550
Connection ~ 4900 1950
$Comp
L C C6
U 1 1 5AF44309
P 4600 2500
F 0 "C6" H 4625 2600 50  0000 L CNN
F 1 "0.1u" H 4625 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4638 2350 50  0001 C CNN
F 3 "" H 4600 2500 50  0001 C CNN
	1    4600 2500
	1    0    0    -1  
$EndComp
$Comp
L LEM_LA_200_P T3
U 1 1 5AF443CC
P 8850 2550
F 0 "T3" H 8850 2600 60  0000 C CNN
F 1 "LEM_LA_200_P" H 8850 3600 60  0000 C CNN
F 2 "Jespers_footprints:LEM_200" H 8850 2600 60  0001 C CNN
F 3 "" H 8850 2600 60  0001 C CNN
	1    8850 2550
	1    0    0    -1  
$EndComp
NoConn ~ 9350 2200
$Comp
L -15V #PWR15
U 1 1 5AF443D3
P 8200 2650
F 0 "#PWR15" H 8200 2750 50  0001 C CNN
F 1 "-15V" H 8050 2750 50  0000 C CNN
F 2 "" H 8200 2650 50  0001 C CNN
F 3 "" H 8200 2650 50  0001 C CNN
	1    8200 2650
	-1   0    0    1   
$EndComp
$Comp
L +15V #PWR09
U 1 1 5AF443D9
P 8200 1500
F 0 "#PWR09" H 8200 1350 50  0001 C CNN
F 1 "+15V" H 8350 1600 50  0000 C CNN
F 2 "" H 8200 1500 50  0001 C CNN
F 3 "" H 8200 1500 50  0001 C CNN
	1    8200 1500
	1    0    0    -1  
$EndComp
Text GLabel 9500 1900 2    60   Input ~ 0
Current_C
Wire Wire Line
	9350 1900 9500 1900
Wire Wire Line
	7900 2200 7900 2300
Connection ~ 7900 1900
Wire Wire Line
	8200 1500 8200 1900
$Comp
L GNDS #PWR010
U 1 1 5AF443F3
P 7900 2650
F 0 "#PWR010" H 7900 2400 50  0001 C CNN
F 1 "GNDS" H 7900 2500 50  0000 C CNN
F 2 "" H 7900 2650 50  0001 C CNN
F 3 "" H 7900 2650 50  0001 C CNN
	1    7900 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 2650 7900 2600
Connection ~ 7900 2200
Wire Wire Line
	8200 2650 8200 2200
Connection ~ 8200 2200
$Comp
L C C7
U 1 1 5AF44400
P 7900 1750
F 0 "C7" H 7925 1850 50  0000 L CNN
F 1 "0.1u" H 7925 1650 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 7938 1600 50  0001 C CNN
F 3 "" H 7900 1750 50  0001 C CNN
	1    7900 1750
	1    0    0    -1  
$EndComp
$Comp
L GNDS #PWR011
U 1 1 5AF4440C
P 7900 1500
F 0 "#PWR011" H 7900 1250 50  0001 C CNN
F 1 "GNDS" H 7900 1350 50  0000 C CNN
F 2 "" H 7900 1500 50  0001 C CNN
F 3 "" H 7900 1500 50  0001 C CNN
	1    7900 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	7900 1600 7900 1500
Connection ~ 8200 1900
$Comp
L C C8
U 1 1 5AF4441B
P 7900 2450
F 0 "C8" H 7925 2550 50  0000 L CNN
F 1 "0.1u" H 7925 2350 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 7938 2300 50  0001 C CNN
F 3 "" H 7900 2450 50  0001 C CNN
	1    7900 2450
	1    0    0    -1  
$EndComp
$Comp
L CP C3
U 1 1 5AF5D67A
P 4150 4250
F 0 "C3" H 4175 4350 50  0000 L CNN
F 1 "68u" H 4175 4150 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D6.3mm_P2.50mm" H 4188 4100 50  0001 C CNN
F 3 "" H 4150 4250 50  0001 C CNN
	1    4150 4250
	1    0    0    -1  
$EndComp
$Comp
L CP C4
U 1 1 5AF5DF46
P 4150 4550
F 0 "C4" H 4175 4650 50  0000 L CNN
F 1 "68u" H 4175 4450 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D6.3mm_P2.50mm" H 4188 4400 50  0001 C CNN
F 3 "" H 4150 4550 50  0001 C CNN
	1    4150 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1950 1500 1900
Wire Wire Line
	1950 1950 1500 1950
Wire Wire Line
	1500 2250 1950 2250
$Comp
L LEM_LA_200_P T2
U 1 1 5AF442BA
P 5550 2600
F 0 "T2" H 5550 2650 60  0000 C CNN
F 1 "LEM_LA_200_P" H 5550 3650 60  0000 C CNN
F 2 "Jespers_footprints:LEM_200" H 5550 2650 60  0001 C CNN
F 3 "" H 5550 2650 60  0001 C CNN
	1    5550 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 1950 5050 1950
Wire Wire Line
	5050 2250 4600 2250
Wire Wire Line
	8350 1900 7900 1900
Wire Wire Line
	7900 2200 8350 2200
Connection ~ 4150 4400
Wire Wire Line
	4350 4300 4350 4050
Wire Wire Line
	4350 4050 4150 4050
Wire Wire Line
	4150 4050 4150 4100
Wire Wire Line
	4350 4500 4350 4800
Wire Wire Line
	4350 4800 4150 4800
Wire Wire Line
	4150 4800 4150 4700
Connection ~ 4350 4800
Connection ~ 4350 4050
$EndSCHEMATC
