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
LIBS:Jespers_library
LIBS:Inverter-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Modular Inverter Phase"
Date "2018-04-13"
Rev "1.0"
Comp "Appendix A.1.2"
Comment1 "Two level inverter with DC-Link capacitor bank"
Comment2 "Designed for <45VDC input, and up to 355A peak output current"
Comment3 "A custom gate driver board designed for this application is used"
Comment4 ""
$EndDescr
$Comp
L IPT012N08N5 Q2
U 1 1 5AC5CF7F
P 6750 2400
F 0 "Q2" H 7000 2450 50  0000 L CNN
F 1 "IPT012N08N5" V 7050 1850 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:Infineon_PG-HSOF-8-1" H 7000 2550 50  0001 L CNN
F 3 "" H 6750 2400 50  0000 C CNN
	1    6750 2400
	1    0    0    -1  
$EndComp
$Comp
L D_Small D4
U 1 1 5AC5CF86
P 6600 3000
F 0 "D4" H 6550 3080 50  0000 L CNN
F 1 "FDLL4148" H 6450 2920 50  0000 L CNN
F 2 "Diodes_SMD:D_MiniMELF" V 6600 3000 50  0001 C CNN
F 3 "" V 6600 3000 50  0001 C CNN
	1    6600 3000
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5AC5CF8D
P 6600 2650
F 0 "R4" V 6680 2650 50  0000 C CNN
F 1 "100k" V 6600 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 6530 2650 50  0001 C CNN
F 3 "" H 6600 2650 50  0001 C CNN
	1    6600 2650
	0    1    1    0   
$EndComp
$Comp
L D_Zener D2
U 1 1 5AC5CF94
P 6350 2800
F 0 "D2" H 6350 2900 50  0000 C CNN
F 1 "ZMY10-GS08" H 6350 2700 50  0000 C CNN
F 2 "Diodes_SMD:D_MELF" H 6350 2800 50  0001 C CNN
F 3 "" H 6350 2800 50  0001 C CNN
	1    6350 2800
	0    1    -1   0   
$EndComp
Text Label 5750 2050 0    60   ~ 0
+DC_link
$Comp
L IPT012N08N5 Q1
U 1 1 5AC5E92E
P 5250 2400
F 0 "Q1" H 5500 2450 50  0000 L CNN
F 1 "IPT012N08N5" V 5550 1850 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:Infineon_PG-HSOF-8-1" H 5500 2550 50  0001 L CNN
F 3 "" H 5250 2400 50  0000 C CNN
	1    5250 2400
	1    0    0    -1  
$EndComp
$Comp
L D_Small D3
U 1 1 5AC5E934
P 5100 3000
F 0 "D3" H 5050 3080 50  0000 L CNN
F 1 "FDLL4148" H 4950 2920 50  0000 L CNN
F 2 "Diodes_SMD:D_MiniMELF" V 5100 3000 50  0001 C CNN
F 3 "" V 5100 3000 50  0001 C CNN
	1    5100 3000
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5AC5E93A
P 5100 2650
F 0 "R3" V 5180 2650 50  0000 C CNN
F 1 "100k" V 5100 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5030 2650 50  0001 C CNN
F 3 "" H 5100 2650 50  0001 C CNN
	1    5100 2650
	0    1    1    0   
$EndComp
$Comp
L D_Zener D1
U 1 1 5AC5E940
P 4850 2800
F 0 "D1" H 4850 2900 50  0000 C CNN
F 1 "ZMY10-GS08" H 4850 2700 50  0000 C CNN
F 2 "Diodes_SMD:D_MELF" H 4850 2800 50  0001 C CNN
F 3 "" H 4850 2800 50  0001 C CNN
	1    4850 2800
	0    1    -1   0   
$EndComp
$Comp
L cu_bar U1
U 1 1 5AC5FE5B
P 7350 2050
F 0 "U1" H 7350 2200 60  0000 C CNN
F 1 "+DC_link" H 7350 1900 60  0000 C CNN
F 2 "Jespers_footprints:cu_bar_long" H 7350 2050 60  0001 C CNN
F 3 "" H 7350 2050 60  0001 C CNN
	1    7350 2050
	1    0    0    -1  
$EndComp
Text Label 5750 3200 0    60   ~ 0
Phase_A
$Comp
L cu_bar U2
U 1 1 5AC60712
P 7350 3200
F 0 "U2" H 7350 3350 60  0000 C CNN
F 1 "Phase_A" H 7350 3050 60  0000 C CNN
F 2 "Jespers_footprints:cu_bar" H 7350 3200 60  0001 C CNN
F 3 "" H 7350 3200 60  0001 C CNN
	1    7350 3200
	1    0    0    -1  
$EndComp
$Comp
L cu_bar U3
U 1 1 5AC60797
P 7350 4350
F 0 "U3" H 7350 4500 60  0000 C CNN
F 1 "-DC_link" H 7350 4200 60  0000 C CNN
F 2 "Jespers_footprints:cu_bar_long" H 7350 4350 60  0001 C CNN
F 3 "" H 7350 4350 60  0001 C CNN
	1    7350 4350
	1    0    0    -1  
$EndComp
$Comp
L IPT012N08N5 Q4
U 1 1 5AC68B96
P 6750 3550
F 0 "Q4" H 7000 3600 50  0000 L CNN
F 1 "IPT012N08N5" V 7050 3000 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:Infineon_PG-HSOF-8-1" H 7000 3700 50  0001 L CNN
F 3 "" H 6750 3550 50  0000 C CNN
	1    6750 3550
	1    0    0    -1  
$EndComp
$Comp
L D_Small D8
U 1 1 5AC68B9C
P 6600 4150
F 0 "D8" H 6550 4230 50  0000 L CNN
F 1 "FDLL4148" H 6450 4070 50  0000 L CNN
F 2 "Diodes_SMD:D_MiniMELF" V 6600 4150 50  0001 C CNN
F 3 "" V 6600 4150 50  0001 C CNN
	1    6600 4150
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 5AC68BA2
P 6600 3800
F 0 "R8" V 6680 3800 50  0000 C CNN
F 1 "100k" V 6600 3800 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 6530 3800 50  0001 C CNN
F 3 "" H 6600 3800 50  0001 C CNN
	1    6600 3800
	0    1    1    0   
$EndComp
$Comp
L D_Zener D6
U 1 1 5AC68BA8
P 6350 3950
F 0 "D6" H 6350 4050 50  0000 C CNN
F 1 "ZMY10-GS08" H 6350 3850 50  0000 C CNN
F 2 "Diodes_SMD:D_MELF" H 6350 3950 50  0001 C CNN
F 3 "" H 6350 3950 50  0001 C CNN
	1    6350 3950
	0    1    -1   0   
$EndComp
$Comp
L R R6
U 1 1 5AC68BAE
P 6150 3550
F 0 "R6" V 6230 3550 50  0000 C CNN
F 1 "2.7" V 6150 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 6080 3550 50  0001 C CNN
F 3 "" H 6150 3550 50  0001 C CNN
	1    6150 3550
	0    1    1    0   
$EndComp
$Comp
L IPT012N08N5 Q3
U 1 1 5AC68BB5
P 5250 3550
F 0 "Q3" H 5500 3600 50  0000 L CNN
F 1 "IPT012N08N5" V 5550 3000 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:Infineon_PG-HSOF-8-1" H 5500 3700 50  0001 L CNN
F 3 "" H 5250 3550 50  0000 C CNN
	1    5250 3550
	1    0    0    -1  
$EndComp
$Comp
L D_Small D7
U 1 1 5AC68BBB
P 5100 4150
F 0 "D7" H 5050 4230 50  0000 L CNN
F 1 "FDLL4148" H 4950 4070 50  0000 L CNN
F 2 "Diodes_SMD:D_MiniMELF" V 5100 4150 50  0001 C CNN
F 3 "" V 5100 4150 50  0001 C CNN
	1    5100 4150
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 5AC68BC1
P 5100 3800
F 0 "R7" V 5180 3800 50  0000 C CNN
F 1 "100k" V 5100 3800 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5030 3800 50  0001 C CNN
F 3 "" H 5100 3800 50  0001 C CNN
	1    5100 3800
	0    1    1    0   
$EndComp
$Comp
L D_Zener D5
U 1 1 5AC68BC7
P 4850 3950
F 0 "D5" H 4850 4050 50  0000 C CNN
F 1 "ZMY10-GS08" H 4850 3850 50  0000 C CNN
F 2 "Diodes_SMD:D_MELF" H 4850 3950 50  0001 C CNN
F 3 "" H 4850 3950 50  0001 C CNN
	1    4850 3950
	0    1    -1   0   
$EndComp
Text GLabel 5950 3550 0    60   Input ~ 0
G_L2A
$Comp
L R R5
U 1 1 5AC68BCF
P 4650 3550
F 0 "R5" V 4730 3550 50  0000 C CNN
F 1 "2.7" V 4650 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 4580 3550 50  0001 C CNN
F 3 "" H 4650 3550 50  0001 C CNN
	1    4650 3550
	0    1    1    0   
$EndComp
Text Label 5750 4350 0    60   ~ 0
-DC_link
Text Notes 4100 1750 0    60   ~ 0
Phase leg
$Comp
L Gate_drive_board U4
U 1 1 5AC78158
P 2350 2650
F 0 "U4" H 2350 3300 60  0000 C CNN
F 1 "Gate_drive_board" H 2350 2000 60  0000 C CNN
F 2 "Jespers_footprints:Gate_driver_example" H 2400 2650 60  0001 C CNN
F 3 "" H 2400 2650 60  0001 C CNN
	1    2350 2650
	1    0    0    -1  
$EndComp
Text GLabel 4450 3550 0    60   Input ~ 0
G_L1A
$Comp
L R R1
U 1 1 5AC79955
P 4650 2400
F 0 "R1" V 4730 2400 50  0000 C CNN
F 1 "2.7" V 4650 2400 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 4580 2400 50  0001 C CNN
F 3 "" H 4650 2400 50  0001 C CNN
	1    4650 2400
	0    1    1    0   
$EndComp
Text GLabel 4450 2400 0    60   Input ~ 0
G_H1A
$Comp
L R R2
U 1 1 5AC79A54
P 6150 2400
F 0 "R2" V 6230 2400 50  0000 C CNN
F 1 "2.7" V 6150 2400 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 6080 2400 50  0001 C CNN
F 3 "" H 6150 2400 50  0001 C CNN
	1    6150 2400
	0    1    1    0   
$EndComp
Text GLabel 3350 2150 2    60   Input ~ 0
G_H1A
Text GLabel 3350 2750 2    60   Input ~ 0
G_L1A
Text GLabel 3350 2950 2    60   Input ~ 0
G_L2A
Text GLabel 3350 2350 2    60   Input ~ 0
G_H2A
Text Label 3350 2550 0    60   ~ 0
Phase_A
Text Label 3350 3150 0    60   ~ 0
-DC_link
Text Notes 1600 2600 2    60   ~ 0
Phase\nsignals\nand\nsupply
$Comp
L CP C1
U 1 1 5AC7CCD5
P 8300 2300
F 0 "C1" H 8325 2400 50  0000 L CNN
F 1 "56u" H 8325 2200 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 8338 2150 50  0001 C CNN
F 3 "" H 8300 2300 50  0001 C CNN
	1    8300 2300
	1    0    0    -1  
$EndComp
Text Label 8050 2000 0    60   ~ 0
+DC_link
$Comp
L CP C2
U 1 1 5AC7DBDC
P 8600 2300
F 0 "C2" H 8625 2400 50  0000 L CNN
F 1 "56u" H 8625 2200 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 8638 2150 50  0001 C CNN
F 3 "" H 8600 2300 50  0001 C CNN
	1    8600 2300
	1    0    0    -1  
$EndComp
$Comp
L CP C3
U 1 1 5AC7DC40
P 8900 2300
F 0 "C3" H 8925 2400 50  0000 L CNN
F 1 "56u" H 8925 2200 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 8938 2150 50  0001 C CNN
F 3 "" H 8900 2300 50  0001 C CNN
	1    8900 2300
	1    0    0    -1  
$EndComp
$Comp
L CP C4
U 1 1 5AC7DC4A
P 9200 2300
F 0 "C4" H 9225 2400 50  0000 L CNN
F 1 "56u" H 9225 2200 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 9238 2150 50  0001 C CNN
F 3 "" H 9200 2300 50  0001 C CNN
	1    9200 2300
	1    0    0    -1  
$EndComp
$Comp
L CP C5
U 1 1 5AC7DC94
P 9500 2300
F 0 "C5" H 9525 2400 50  0000 L CNN
F 1 "56u" H 9525 2200 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 9538 2150 50  0001 C CNN
F 3 "" H 9500 2300 50  0001 C CNN
	1    9500 2300
	1    0    0    -1  
$EndComp
$Comp
L CP C6
U 1 1 5AC7DC9E
P 9800 2300
F 0 "C6" H 9825 2400 50  0000 L CNN
F 1 "56u" H 9825 2200 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 9838 2150 50  0001 C CNN
F 3 "" H 9800 2300 50  0001 C CNN
	1    9800 2300
	1    0    0    -1  
$EndComp
$Comp
L CP C7
U 1 1 5AC7E032
P 8300 3000
F 0 "C7" H 8325 3100 50  0000 L CNN
F 1 "56u" H 8325 2900 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 8338 2850 50  0001 C CNN
F 3 "" H 8300 3000 50  0001 C CNN
	1    8300 3000
	1    0    0    -1  
$EndComp
$Comp
L CP C8
U 1 1 5AC7E03C
P 8600 3000
F 0 "C8" H 8625 3100 50  0000 L CNN
F 1 "56u" H 8625 2900 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 8638 2850 50  0001 C CNN
F 3 "" H 8600 3000 50  0001 C CNN
	1    8600 3000
	1    0    0    -1  
$EndComp
$Comp
L CP C9
U 1 1 5AC7E046
P 8900 3000
F 0 "C9" H 8925 3100 50  0000 L CNN
F 1 "56u" H 8925 2900 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 8938 2850 50  0001 C CNN
F 3 "" H 8900 3000 50  0001 C CNN
	1    8900 3000
	1    0    0    -1  
$EndComp
$Comp
L CP C10
U 1 1 5AC7E050
P 9200 3000
F 0 "C10" H 9225 3100 50  0000 L CNN
F 1 "56u" H 9225 2900 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 9238 2850 50  0001 C CNN
F 3 "" H 9200 3000 50  0001 C CNN
	1    9200 3000
	1    0    0    -1  
$EndComp
$Comp
L CP C11
U 1 1 5AC7E05A
P 9500 3000
F 0 "C11" H 9525 3100 50  0000 L CNN
F 1 "56u" H 9525 2900 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 9538 2850 50  0001 C CNN
F 3 "" H 9500 3000 50  0001 C CNN
	1    9500 3000
	1    0    0    -1  
$EndComp
$Comp
L CP C12
U 1 1 5AC7E064
P 9800 3000
F 0 "C12" H 9825 3100 50  0000 L CNN
F 1 "56u" H 9825 2900 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_10x10.5" H 9838 2850 50  0001 C CNN
F 3 "" H 9800 3000 50  0001 C CNN
	1    9800 3000
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 5ACCBC08
P 8300 3700
F 0 "C13" H 8325 3800 50  0000 L CNN
F 1 "100n" H 8325 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 8338 3550 50  0001 C CNN
F 3 "" H 8300 3700 50  0001 C CNN
	1    8300 3700
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 5ACCBD28
P 8600 3700
F 0 "C14" H 8625 3800 50  0000 L CNN
F 1 "100n" H 8625 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 8638 3550 50  0001 C CNN
F 3 "" H 8600 3700 50  0001 C CNN
	1    8600 3700
	1    0    0    -1  
$EndComp
$Comp
L C C15
U 1 1 5ACCBDB0
P 8900 3700
F 0 "C15" H 8925 3800 50  0000 L CNN
F 1 "100n" H 8925 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 8938 3550 50  0001 C CNN
F 3 "" H 8900 3700 50  0001 C CNN
	1    8900 3700
	1    0    0    -1  
$EndComp
$Comp
L C C16
U 1 1 5ACCBDB6
P 9200 3700
F 0 "C16" H 9225 3800 50  0000 L CNN
F 1 "100n" H 9225 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 9238 3550 50  0001 C CNN
F 3 "" H 9200 3700 50  0001 C CNN
	1    9200 3700
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 5ACCBE1C
P 9500 3700
F 0 "C17" H 9525 3800 50  0000 L CNN
F 1 "100n" H 9525 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 9538 3550 50  0001 C CNN
F 3 "" H 9500 3700 50  0001 C CNN
	1    9500 3700
	1    0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 5ACCBE22
P 9800 3700
F 0 "C18" H 9825 3800 50  0000 L CNN
F 1 "100n" H 9825 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 9838 3550 50  0001 C CNN
F 3 "" H 9800 3700 50  0001 C CNN
	1    9800 3700
	1    0    0    -1  
$EndComp
Text Label 10050 4100 2    60   ~ 0
-DC_link
Text GLabel 5950 2400 0    60   Input ~ 0
G_H2A
Text Notes 8000 1750 0    60   ~ 0
DC-Link Cap. bank
Text Notes 1500 1750 0    60   ~ 0
Gate Driver daughter board
Wire Wire Line
	6500 3000 6350 3000
Wire Wire Line
	6350 3000 6350 2950
Wire Wire Line
	5350 2050 6950 2050
Connection ~ 6850 2050
Wire Wire Line
	6850 2600 6850 3350
Wire Wire Line
	6850 2650 6750 2650
Wire Wire Line
	6850 3000 6700 3000
Connection ~ 6850 2650
Wire Wire Line
	6300 2400 6550 2400
Wire Wire Line
	6450 2400 6450 2650
Wire Wire Line
	6350 2650 6350 2400
Connection ~ 6450 2400
Connection ~ 6350 2400
Wire Wire Line
	5000 3000 4850 3000
Wire Wire Line
	4850 3000 4850 2950
Wire Wire Line
	5350 2600 5350 3350
Wire Wire Line
	5350 2650 5250 2650
Wire Wire Line
	5350 3000 5200 3000
Connection ~ 5350 2650
Wire Wire Line
	4800 2400 5050 2400
Wire Wire Line
	4950 2400 4950 2650
Wire Wire Line
	4850 2650 4850 2400
Connection ~ 4950 2400
Connection ~ 4850 2400
Wire Wire Line
	5350 2200 5350 2050
Wire Wire Line
	6850 2050 6850 2200
Wire Wire Line
	5350 3200 6950 3200
Connection ~ 6850 3000
Connection ~ 5350 3000
Connection ~ 6850 3200
Connection ~ 5350 3200
Wire Wire Line
	6500 4150 6350 4150
Wire Wire Line
	6350 4150 6350 4100
Wire Wire Line
	6850 3750 6850 4350
Wire Wire Line
	6850 3800 6750 3800
Wire Wire Line
	6850 4150 6700 4150
Connection ~ 6850 3800
Wire Wire Line
	6300 3550 6550 3550
Wire Wire Line
	6450 3550 6450 3800
Wire Wire Line
	6350 3800 6350 3550
Connection ~ 6450 3550
Connection ~ 6350 3550
Wire Wire Line
	5000 4150 4850 4150
Wire Wire Line
	4850 4150 4850 4100
Wire Wire Line
	5350 3750 5350 4350
Wire Wire Line
	5350 3800 5250 3800
Wire Wire Line
	5350 4150 5200 4150
Connection ~ 5350 3800
Wire Wire Line
	4800 3550 5050 3550
Wire Wire Line
	4950 3550 4950 3800
Wire Wire Line
	4850 3800 4850 3550
Connection ~ 4950 3550
Connection ~ 4850 3550
Wire Wire Line
	4450 3550 4500 3550
Wire Wire Line
	5350 4350 6950 4350
Connection ~ 6850 4150
Connection ~ 5350 4150
Connection ~ 6850 4350
Wire Wire Line
	5950 3550 6000 3550
Wire Notes Line
	7600 1800 4100 1800
Wire Notes Line
	4100 1800 4100 1850
Wire Notes Line
	7600 1800 7600 1850
Wire Wire Line
	4450 2400 4500 2400
Wire Wire Line
	5950 2400 6000 2400
Wire Wire Line
	3350 2150 3200 2150
Wire Wire Line
	3200 2350 3350 2350
Wire Wire Line
	3200 2550 3350 2550
Wire Wire Line
	3200 2750 3350 2750
Wire Wire Line
	3200 2950 3350 2950
Wire Wire Line
	3200 3150 3350 3150
Wire Notes Line
	1700 2250 1650 2250
Wire Notes Line
	1650 2250 1650 2400
Wire Notes Line
	1650 2400 1700 2400
Wire Wire Line
	8300 2150 8300 2100
Connection ~ 8300 2100
Wire Wire Line
	8300 2500 8300 2450
Wire Wire Line
	8600 2100 8600 2150
Connection ~ 8600 2100
Connection ~ 8600 2500
Wire Wire Line
	8600 2500 8600 2450
Wire Wire Line
	8900 2100 8900 2150
Connection ~ 8900 2100
Connection ~ 8900 2500
Wire Wire Line
	8900 2500 8900 2450
Wire Wire Line
	9200 2100 9200 2150
Connection ~ 9200 2100
Connection ~ 9200 2500
Wire Wire Line
	9200 2500 9200 2450
Wire Wire Line
	9500 2100 9500 2150
Connection ~ 9500 2100
Connection ~ 9500 2500
Wire Wire Line
	9500 2500 9500 2450
Wire Wire Line
	9800 2100 9800 2150
Connection ~ 9800 2100
Connection ~ 9800 2500
Wire Wire Line
	9800 2500 9800 2450
Wire Wire Line
	8300 2850 8300 2800
Connection ~ 8300 2800
Wire Wire Line
	8300 3200 8300 3150
Wire Wire Line
	8600 2800 8600 2850
Connection ~ 8600 2800
Connection ~ 8600 3200
Wire Wire Line
	8600 3200 8600 3150
Wire Wire Line
	8900 2800 8900 2850
Connection ~ 8900 2800
Connection ~ 8900 3200
Wire Wire Line
	8900 3200 8900 3150
Wire Wire Line
	9200 2800 9200 2850
Connection ~ 9200 2800
Connection ~ 9200 3200
Wire Wire Line
	9200 3200 9200 3150
Wire Wire Line
	9500 2800 9500 2850
Connection ~ 9500 2800
Connection ~ 9500 3200
Wire Wire Line
	9500 3200 9500 3150
Wire Wire Line
	9800 2800 9800 2850
Connection ~ 9800 3200
Wire Wire Line
	9800 3200 9800 3150
Wire Wire Line
	8050 2000 8050 3500
Wire Wire Line
	8050 2100 9800 2100
Wire Wire Line
	8050 2800 9800 2800
Connection ~ 8050 2100
Wire Wire Line
	8300 3200 10100 3200
Wire Wire Line
	8300 2500 10100 2500
Connection ~ 10100 3200
Wire Wire Line
	8300 3550 8300 3500
Connection ~ 8300 3500
Wire Wire Line
	8600 3500 8600 3550
Connection ~ 8600 3500
Wire Wire Line
	8900 3500 8900 3550
Connection ~ 8900 3500
Wire Wire Line
	9200 3500 9200 3550
Connection ~ 9200 3500
Wire Wire Line
	9500 3500 9500 3550
Connection ~ 9500 3500
Wire Wire Line
	9800 3500 9800 3550
Wire Wire Line
	8050 3500 9800 3500
Connection ~ 8050 2800
Wire Wire Line
	8300 3900 8300 3850
Connection ~ 8600 3900
Wire Wire Line
	8600 3900 8600 3850
Connection ~ 8900 3900
Wire Wire Line
	8900 3900 8900 3850
Connection ~ 9200 3900
Wire Wire Line
	9200 3900 9200 3850
Connection ~ 9500 3900
Wire Wire Line
	9500 3900 9500 3850
Connection ~ 9800 3900
Wire Wire Line
	9800 3900 9800 3850
Wire Wire Line
	10100 3900 8300 3900
Wire Wire Line
	10100 2500 10100 4100
Wire Wire Line
	10100 4100 10050 4100
Connection ~ 10100 3900
Wire Notes Line
	10150 1800 8000 1800
Wire Notes Line
	8000 1800 8000 1850
Wire Notes Line
	10150 1800 10150 1850
Wire Notes Line
	3700 1800 1500 1800
Wire Notes Line
	1500 1800 1500 1850
Wire Notes Line
	3700 1800 3700 1850
$EndSCHEMATC
