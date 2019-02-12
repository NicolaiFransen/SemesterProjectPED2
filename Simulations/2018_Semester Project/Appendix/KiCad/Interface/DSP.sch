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
LIBS:interface-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "Interface board"
Date "2018-05-27"
Rev "1.0"
Comp "Appendix A.1.5"
Comment1 "Connector for a Texas Instruments Picolo F28075 ControlCard"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 5600 4950
NoConn ~ 5600 5050
NoConn ~ 5600 5150
NoConn ~ 5600 5250
NoConn ~ 5600 5350
NoConn ~ 5600 5450
NoConn ~ 5600 5550
NoConn ~ 5600 5650
NoConn ~ 5600 2150
NoConn ~ 5600 2050
NoConn ~ 5600 1950
NoConn ~ 5600 1650
NoConn ~ 5600 1550
NoConn ~ 5600 1450
NoConn ~ 5600 1350
$Comp
L F28075 U6
U 1 1 5AD49F21
P 5200 4200
F 0 "U6" H 5200 7400 60  0000 C CNN
F 1 "MicroCon_socket" H 5200 950 60  0000 C CNN
F 2 "Kart_interface:HSEC8-160-01-L-DV-A" H 5100 5400 60  0001 C CNN
F 3 "" H 5100 5400 60  0001 C CNN
	1    5200 4200
	1    0    0    -1  
$EndComp
Text HLabel 5850 4550 2    60   Input ~ 0
EncA_sig
Text HLabel 5850 4650 2    60   Input ~ 0
EncB_sig
Text HLabel 5850 4850 2    60   Input ~ 0
EncZ_sig
Text HLabel 5850 1850 2    60   Input ~ 0
Ped_sig_Bl
Text HLabel 4600 1650 0    60   Input ~ 0
CurA_sig
Text HLabel 5850 1750 2    60   Input ~ 0
CurB_sig
Text HLabel 5850 2400 2    60   Input ~ 0
CurC_sig
Text HLabel 4600 3650 0    60   Input ~ 0
PWM1_sig
Text HLabel 4600 3750 0    60   Input ~ 0
PWM2_sig
Text HLabel 4600 3850 0    60   Input ~ 0
PWM3_sig
Text HLabel 5850 2500 2    60   Input ~ 0
Vol_sig
$Comp
L GNDS #PWR056
U 1 1 5AE36E30
P 5850 2250
F 0 "#PWR056" H 5850 2000 50  0001 C CNN
F 1 "GNDS" H 5850 2100 50  0000 C CNN
F 2 "" H 5850 2250 50  0001 C CNN
F 3 "" H 5850 2250 50  0001 C CNN
	1    5850 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5850 1850 5600 1850
Wire Wire Line
	5600 2250 5850 2250
Wire Wire Line
	4600 1650 4800 1650
Wire Wire Line
	5600 1750 5850 1750
$Comp
L GNDS #PWR057
U 1 1 5AE36E74
P 4600 2150
F 0 "#PWR057" H 4600 1900 50  0001 C CNN
F 1 "GNDS" H 4600 2000 50  0000 C CNN
F 2 "" H 4600 2150 50  0001 C CNN
F 3 "" H 4600 2150 50  0001 C CNN
	1    4600 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 2150 4800 2150
$Comp
L GNDS #PWR058
U 1 1 5AE36E93
P 5850 3050
F 0 "#PWR058" H 5850 2800 50  0001 C CNN
F 1 "GNDS" H 5850 2900 50  0000 C CNN
F 2 "" H 5850 3050 50  0001 C CNN
F 3 "" H 5850 3050 50  0001 C CNN
	1    5850 3050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5600 3050 5850 3050
$Comp
L GNDS #PWR059
U 1 1 5AE36EB1
P 5850 3450
F 0 "#PWR059" H 5850 3200 50  0001 C CNN
F 1 "GNDS" H 5950 3300 50  0000 C CNN
F 2 "" H 5850 3450 50  0001 C CNN
F 3 "" H 5850 3450 50  0001 C CNN
	1    5850 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5600 3450 5850 3450
Wire Wire Line
	5600 2350 5750 2350
Wire Wire Line
	5750 2350 5750 2400
Wire Wire Line
	5750 2400 5850 2400
Wire Wire Line
	5600 2450 5750 2450
Wire Wire Line
	5750 2500 5850 2500
Wire Wire Line
	5750 2450 5750 2500
Wire Wire Line
	4600 3650 4800 3650
Wire Wire Line
	4600 3850 4800 3850
$Comp
L +5V #PWR060
U 1 1 5AE37807
P 5900 3550
F 0 "#PWR060" H 5900 3400 50  0001 C CNN
F 1 "+5V" H 5900 3700 50  0000 C CNN
F 2 "" H 5900 3550 50  0001 C CNN
F 3 "" H 5900 3550 50  0001 C CNN
	1    5900 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	5900 3550 5600 3550
Text HLabel 5850 4150 2    60   Input ~ 0
ENB_sig
Wire Wire Line
	5600 4150 5850 4150
Wire Wire Line
	5600 4550 5850 4550
Wire Wire Line
	5600 4850 5850 4850
Wire Wire Line
	5600 4650 5850 4650
NoConn ~ 5600 5750
NoConn ~ 5600 5850
NoConn ~ 5600 5950
NoConn ~ 5600 6050
NoConn ~ 5600 6150
NoConn ~ 5600 6250
NoConn ~ 5600 6350
NoConn ~ 5600 6450
NoConn ~ 5600 6550
NoConn ~ 5600 6650
NoConn ~ 5600 6750
NoConn ~ 5600 6850
NoConn ~ 5600 6950
NoConn ~ 5600 7050
NoConn ~ 5600 7150
NoConn ~ 4800 6450
NoConn ~ 4800 6550
NoConn ~ 4800 6650
NoConn ~ 4800 6750
NoConn ~ 4800 6850
NoConn ~ 4800 6950
NoConn ~ 4800 7050
NoConn ~ 4800 7150
NoConn ~ 4800 5650
NoConn ~ 4800 5750
NoConn ~ 4800 5850
NoConn ~ 4800 5950
NoConn ~ 4800 6050
NoConn ~ 4800 6150
NoConn ~ 4800 6250
NoConn ~ 4800 6350
NoConn ~ 4800 4850
NoConn ~ 4800 4950
NoConn ~ 4800 5050
NoConn ~ 4800 5150
NoConn ~ 4800 5250
NoConn ~ 4800 5350
NoConn ~ 4800 5450
NoConn ~ 4800 5550
NoConn ~ 4800 4050
NoConn ~ 4800 4150
NoConn ~ 4800 4250
NoConn ~ 4800 4350
NoConn ~ 4800 4450
NoConn ~ 4800 4550
NoConn ~ 4800 4650
NoConn ~ 4800 4750
NoConn ~ 4800 2850
NoConn ~ 4800 2950
NoConn ~ 4800 3050
NoConn ~ 4800 3150
NoConn ~ 4800 3250
NoConn ~ 4800 3350
NoConn ~ 4800 3450
NoConn ~ 4800 3550
NoConn ~ 4800 2050
NoConn ~ 4800 2250
NoConn ~ 4800 2350
NoConn ~ 4800 2450
NoConn ~ 4800 2550
NoConn ~ 4800 2650
NoConn ~ 4800 2750
NoConn ~ 4800 1250
NoConn ~ 4800 1350
NoConn ~ 4800 1450
NoConn ~ 4800 1550
NoConn ~ 4800 1750
NoConn ~ 4800 1850
NoConn ~ 4800 1950
NoConn ~ 5600 1250
NoConn ~ 5600 2550
NoConn ~ 5600 2650
NoConn ~ 5600 2750
NoConn ~ 5600 2850
NoConn ~ 5600 2950
NoConn ~ 5600 3150
NoConn ~ 5600 3250
NoConn ~ 5600 3350
NoConn ~ 5600 3750
NoConn ~ 5600 3850
NoConn ~ 5600 3950
NoConn ~ 5600 4050
NoConn ~ 5600 4250
NoConn ~ 5600 4350
NoConn ~ 5600 4450
NoConn ~ 5600 4750
NoConn ~ 4800 3750
NoConn ~ 4800 3950
Wire Wire Line
	4800 3750 4600 3750
$Comp
L GNDS #PWR061
U 1 1 5AE1C88D
P 5850 3650
F 0 "#PWR061" H 5850 3400 50  0001 C CNN
F 1 "GNDS" H 5850 3500 50  0000 C CNN
F 2 "" H 5850 3650 50  0001 C CNN
F 3 "" H 5850 3650 50  0001 C CNN
	1    5850 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5850 3650 5600 3650
$EndSCHEMATC
