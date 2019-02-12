EESchema Schematic File Version 4
LIBS:Gate_drive-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Gate driver"
Date "2018-05-20"
Rev "1.0"
Comp "Appendix A.1.3"
Comment1 "Half bridge gate driver designed for the Modular Inverter Phase board"
Comment2 "Isolated outputs of +15, -8.7V relative to either high or low VSS."
Comment3 "Peak source/sink currents of 15A."
Comment4 "Internal signal inverter for PWM and programmed deadtime of 1µs"
$EndDescr
$Comp
L GND #PWR01
U 1 1 5ACAE59E
P 1350 1450
F 0 "#PWR01" H 1350 1200 50  0001 C CNN
F 1 "GND" H 1350 1300 50  0000 C CNN
F 2 "" H 1350 1450 50  0001 C CNN
F 3 "" H 1350 1450 50  0001 C CNN
	1    1350 1450
	1    0    0    -1  
$EndComp
Text Label 850  900  0    60   ~ 0
PWM
Text Label 850  800  0    60   ~ 0
ENABLE
Text Label 2400 3450 2    60   ~ 0
ENABLE
$Comp
L C C12
U 1 1 5ACAE5A7
P 3900 3500
F 0 "C12" H 3925 3600 50  0000 L CNN
F 1 "2.2n" H 3925 3400 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 3938 3350 50  0001 C CNN
F 3 "" H 3900 3500 50  0001 C CNN
	1    3900 3500
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5ACAE5AE
P 3650 3500
F 0 "R5" V 3730 3500 50  0000 C CNN
F 1 "100k" V 3650 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 3580 3500 50  0001 C CNN
F 3 "" H 3650 3500 50  0001 C CNN
	1    3650 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5ACAE5B5
P 3650 3700
F 0 "#PWR02" H 3650 3450 50  0001 C CNN
F 1 "GND" H 3650 3550 50  0000 C CNN
F 2 "" H 3650 3700 50  0001 C CNN
F 3 "" H 3650 3700 50  0001 C CNN
	1    3650 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5ACAE5BB
P 3900 3700
F 0 "#PWR03" H 3900 3450 50  0001 C CNN
F 1 "GND" H 3900 3550 50  0000 C CNN
F 2 "" H 3900 3700 50  0001 C CNN
F 3 "" H 3900 3700 50  0001 C CNN
	1    3900 3700
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 5ACAE5C1
P 3900 2700
F 0 "C11" H 3925 2800 50  0000 L CNN
F 1 "100n" H 3925 2600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 3938 2550 50  0001 C CNN
F 3 "" H 3900 2700 50  0001 C CNN
	1    3900 2700
	1    0    0    -1  
$EndComp
Text Label 2250 2000 2    60   ~ 0
PWM
$Comp
L R R3
U 1 1 5ACAE5CF
P 3100 2800
F 0 "R3" V 3180 2800 50  0000 C CNN
F 1 "100k" V 3100 2800 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 3030 2800 50  0001 C CNN
F 3 "" H 3100 2800 50  0001 C CNN
	1    3100 2800
	1    0    0    -1  
$EndComp
$Comp
L PHPT60415NY Q4
U 1 1 5ACAE602
P 8450 3550
F 0 "Q4" H 8650 3625 50  0000 L CNN
F 1 "PHPT60415NY" H 8650 3550 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-669_LFPAK" H 8650 3475 50  0001 L CIN
F 3 "" H 8450 3550 50  0000 L CNN
	1    8450 3550
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 5ACAE625
P 7950 3850
F 0 "R6" V 8030 3850 50  0000 C CNN
F 1 "1" V 7950 3850 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 7880 3850 50  0001 C CNN
F 3 "" H 7950 3850 50  0001 C CNN
	1    7950 3850
	0    1    1    0   
$EndComp
$Comp
L PHPT60415PY Q5
U 1 1 5ACAE63A
P 8450 4150
F 0 "Q5" H 8650 4225 50  0000 L CNN
F 1 "PHPT60415PY" H 8650 4150 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-669_LFPAK" H 8650 4075 50  0001 L CIN
F 3 "" H 8450 4150 50  0000 L CNN
	1    8450 4150
	1    0    0    1   
$EndComp
$Comp
L C C14
U 1 1 5ACAE641
P 7150 3550
F 0 "C14" H 7175 3650 50  0000 L CNN
F 1 "4.7u" H 7175 3450 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7188 3400 50  0001 C CNN
F 3 "" H 7150 3550 50  0001 C CNN
	1    7150 3550
	1    0    0    -1  
$EndComp
$Comp
L C C15
U 1 1 5ACAE648
P 7400 3550
F 0 "C15" H 7425 3650 50  0000 L CNN
F 1 "100n" H 7425 3450 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7438 3400 50  0001 C CNN
F 3 "" H 7400 3550 50  0001 C CNN
	1    7400 3550
	1    0    0    -1  
$EndComp
$Comp
L C C16
U 1 1 5ACAE64F
P 7150 4200
F 0 "C16" H 7175 4300 50  0000 L CNN
F 1 "4.7u" H 7175 4100 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7188 4050 50  0001 C CNN
F 3 "" H 7150 4200 50  0001 C CNN
	1    7150 4200
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 5ACAE656
P 7400 4200
F 0 "C17" H 7425 4300 50  0000 L CNN
F 1 "100n" H 7425 4100 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7438 4050 50  0001 C CNN
F 3 "" H 7400 4200 50  0001 C CNN
	1    7400 4200
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 5ACAE65D
P 6900 3550
F 0 "C13" H 6925 3650 50  0000 L CNN
F 1 "10u" H 6925 3450 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 6938 3400 50  0001 C CNN
F 3 "" H 6900 3550 50  0001 C CNN
	1    6900 3550
	1    0    0    -1  
$EndComp
$Comp
L UCC20520 U3
U 1 1 5ACAE6A5
P 5050 3000
F 0 "U3" H 5050 3850 60  0000 C CNN
F 1 "UCC20520" H 5050 2150 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-16W_7.5x10.3mm_Pitch1.27mm" H 5050 2050 60  0001 C CNN
F 3 "" H 5050 3100 60  0001 C CNN
	1    5050 3000
	1    0    0    -1  
$EndComp
Text Label 3650 3300 0    60   ~ 0
DT
$Comp
L GND #PWR04
U 1 1 5ACAE6C8
P 4200 5200
F 0 "#PWR04" H 4200 4950 50  0001 C CNN
F 1 "GND" H 4200 5050 50  0000 C CNN
F 2 "" H 4200 5200 50  0001 C CNN
F 3 "" H 4200 5200 50  0001 C CNN
	1    4200 5200
	1    0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 5ACAE6CE
P 4200 4950
F 0 "C18" H 4225 5050 50  0000 L CNN
F 1 "100n" H 4225 4850 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 4238 4800 50  0001 C CNN
F 3 "" H 4200 4950 50  0001 C CNN
	1    4200 4950
	1    0    0    -1  
$EndComp
Text Label 6000 4800 2    60   ~ 0
+15V:B
Text Label 6000 5100 2    60   ~ 0
-8.7V:B
$Comp
L +24V #PWR05
U 1 1 5ACAE6D9
P 1350 950
F 0 "#PWR05" H 1350 800 50  0001 C CNN
F 1 "+24V" H 1350 1090 50  0000 C CNN
F 2 "" H 1350 950 50  0001 C CNN
F 3 "" H 1350 950 50  0001 C CNN
	1    1350 950 
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR06
U 1 1 5ACAE6E5
P 4200 4700
F 0 "#PWR06" H 4200 4550 50  0001 C CNN
F 1 "+24V" H 4200 4840 50  0000 C CNN
F 2 "" H 4200 4700 50  0001 C CNN
F 3 "" H 4200 4700 50  0001 C CNN
	1    4200 4700
	1    0    0    -1  
$EndComp
$Comp
L L78L15_SOT89 U1
U 1 1 5ACAE6EB
P 2850 900
F 0 "U1" H 2700 1025 50  0000 C CNN
F 1 "L78L15ABUTR" H 2825 1025 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-89-3" H 2850 1100 50  0001 C CIN
F 3 "" H 2850 850 50  0001 C CNN
	1    2850 900 
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5ACAE6F2
P 3450 1100
F 0 "C3" H 3475 1200 50  0000 L CNN
F 1 "100n" H 3475 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 3488 950 50  0001 C CNN
F 3 "" H 3450 1100 50  0001 C CNN
	1    3450 1100
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5ACAE6F9
P 2200 1100
F 0 "C2" H 2225 1200 50  0000 L CNN
F 1 "330n" H 2225 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 2238 950 50  0001 C CNN
F 3 "" H 2200 1100 50  0001 C CNN
	1    2200 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5ACAE700
P 2200 1300
F 0 "#PWR07" H 2200 1050 50  0001 C CNN
F 1 "GND" H 2200 1150 50  0000 C CNN
F 2 "" H 2200 1300 50  0001 C CNN
F 3 "" H 2200 1300 50  0001 C CNN
	1    2200 1300
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5ACAE706
P 1350 1200
F 0 "C4" H 1375 1300 50  0000 L CNN
F 1 "10u" H 1375 1100 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 1388 1050 50  0001 C CNN
F 3 "" H 1350 1200 50  0001 C CNN
	1    1350 1200
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR08
U 1 1 5ACAE70D
P 2200 850
F 0 "#PWR08" H 2200 700 50  0001 C CNN
F 1 "+24V" H 2200 990 50  0000 C CNN
F 2 "" H 2200 850 50  0001 C CNN
F 3 "" H 2200 850 50  0001 C CNN
	1    2200 850 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5ACAE713
P 3450 1350
F 0 "#PWR09" H 3450 1100 50  0001 C CNN
F 1 "GND" H 3450 1200 50  0000 C CNN
F 2 "" H 3450 1350 50  0001 C CNN
F 3 "" H 3450 1350 50  0001 C CNN
	1    3450 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5ACAE719
P 2850 1350
F 0 "#PWR010" H 2850 1100 50  0001 C CNN
F 1 "GND" H 2850 1200 50  0000 C CNN
F 2 "" H 2850 1350 50  0001 C CNN
F 3 "" H 2850 1350 50  0001 C CNN
	1    2850 1350
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J1
U 1 1 5ACAE71F
P 550 900
F 0 "J1" H 550 1100 50  0000 C CNN
F 1 "Inputs" H 550 600 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-04_04x2.54mm_Straight" H 550 900 50  0001 C CNN
F 3 "" H 550 900 50  0001 C CNN
	1    550  900 
	-1   0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5ACAE726
P 2600 2000
F 0 "R1" V 2680 2000 50  0000 C CNN
F 1 "47" V 2600 2000 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 2530 2000 50  0001 C CNN
F 3 "" H 2600 2000 50  0001 C CNN
	1    2600 2000
	0    1    1    0   
$EndComp
$Comp
L C C8
U 1 1 5ACAE72D
P 2800 2200
F 0 "C8" H 2825 2300 50  0000 L CNN
F 1 "33p" H 2825 2100 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 2838 2050 50  0001 C CNN
F 3 "" H 2800 2200 50  0001 C CNN
	1    2800 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 5ACAE734
P 2800 2400
F 0 "#PWR011" H 2800 2150 50  0001 C CNN
F 1 "GND" H 2800 2250 50  0000 C CNN
F 2 "" H 2800 2400 50  0001 C CNN
F 3 "" H 2800 2400 50  0001 C CNN
	1    2800 2400
	1    0    0    -1  
$EndComp
$Comp
L BC846B Q3
U 1 1 5ACAE824
P 3000 3450
F 0 "Q3" H 3200 3525 50  0000 L CNN
F 1 "BC846A" H 3200 3450 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3200 3375 50  0001 L CIN
F 3 "" H 3000 3450 50  0000 L CNN
	1    3000 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5ACAE82B
P 3100 3700
F 0 "#PWR012" H 3100 3450 50  0001 C CNN
F 1 "GND" H 3100 3550 50  0000 C CNN
F 2 "" H 3100 3700 50  0001 C CNN
F 3 "" H 3100 3700 50  0001 C CNN
	1    3100 3700
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5ACAE833
P 2600 3450
F 0 "R4" V 2680 3450 50  0000 C CNN
F 1 "5k6" V 2600 3450 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 2530 3450 50  0001 C CNN
F 3 "" H 2600 3450 50  0001 C CNN
	1    2600 3450
	0    1    1    0   
$EndComp
Text Label 9250 3850 0    60   ~ 0
Gate:B
Text Label 9250 4550 0    60   ~ 0
VSS:B
$Comp
L Conn_01x01 J4
U 1 1 5AC9F3C8
P 9800 3850
F 0 "J4" H 9800 3950 50  0000 C CNN
F 1 "Gate:B" H 9800 3750 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_2x_1-2mmDrill" H 9800 3850 50  0001 C CNN
F 3 "" H 9800 3850 50  0001 C CNN
	1    9800 3850
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x01 J5
U 1 1 5AC9F3CE
P 9800 4550
F 0 "J5" H 9800 4650 50  0000 C CNN
F 1 "VSS:B" H 9800 4450 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_1-2mmDrill" H 9800 4550 50  0001 C CNN
F 3 "" H 9800 4550 50  0001 C CNN
	1    9800 4550
	1    0    0    -1  
$EndComp
$Comp
L +15V #PWR013
U 1 1 5ACA369F
P 3450 850
F 0 "#PWR013" H 3450 700 50  0001 C CNN
F 1 "+15V" H 3450 990 50  0000 C CNN
F 2 "" H 3450 850 50  0001 C CNN
F 3 "" H 3450 850 50  0001 C CNN
	1    3450 850 
	1    0    0    -1  
$EndComp
$Comp
L +15V #PWR014
U 1 1 5ACA4147
P 3900 2400
F 0 "#PWR014" H 3900 2250 50  0001 C CNN
F 1 "+15V" H 3900 2540 50  0000 C CNN
F 2 "" H 3900 2400 50  0001 C CNN
F 3 "" H 3900 2400 50  0001 C CNN
	1    3900 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 5ACA458D
P 3900 2900
F 0 "#PWR015" H 3900 2650 50  0001 C CNN
F 1 "GND" H 3900 2750 50  0000 C CNN
F 2 "" H 3900 2900 50  0001 C CNN
F 3 "" H 3900 2900 50  0001 C CNN
	1    3900 2900
	1    0    0    -1  
$EndComp
Text Notes 3550 4050 0    60   ~ 12
Dead time
Text Notes 2450 1800 0    60   ~ 0
LPF: 100MHz
$Comp
L GND #PWR016
U 1 1 5ACBB2AA
P 4200 1300
F 0 "#PWR016" H 4200 1050 50  0001 C CNN
F 1 "GND" H 4200 1150 50  0000 C CNN
F 2 "" H 4200 1300 50  0001 C CNN
F 3 "" H 4200 1300 50  0001 C CNN
	1    4200 1300
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5ACBB2B0
P 4200 1050
F 0 "C1" H 4225 1150 50  0000 L CNN
F 1 "100n" H 4225 950 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 4238 900 50  0001 C CNN
F 3 "" H 4200 1050 50  0001 C CNN
	1    4200 1050
	1    0    0    -1  
$EndComp
Text Label 6000 900  2    60   ~ 0
+15V:A
Text Label 6000 1200 2    60   ~ 0
-8.7V:A
$Comp
L +24V #PWR017
U 1 1 5ACBB2B8
P 4200 800
F 0 "#PWR017" H 4200 650 50  0001 C CNN
F 1 "+24V" H 4200 940 50  0000 C CNN
F 2 "" H 4200 800 50  0001 C CNN
F 3 "" H 4200 800 50  0001 C CNN
	1    4200 800 
	1    0    0    -1  
$EndComp
$Comp
L PHPT60415NY Q1
U 1 1 5ACBD514
P 8450 1850
F 0 "Q1" H 8650 1925 50  0000 L CNN
F 1 "PHPT60415NY" H 8650 1850 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-669_LFPAK" H 8650 1775 50  0001 L CIN
F 3 "" H 8450 1850 50  0000 L CNN
	1    8450 1850
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5ACBD51A
P 7950 2150
F 0 "R2" V 8030 2150 50  0000 C CNN
F 1 "1" V 7950 2150 50  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 7880 2150 50  0001 C CNN
F 3 "" H 7950 2150 50  0001 C CNN
	1    7950 2150
	0    1    1    0   
$EndComp
$Comp
L PHPT60415PY Q2
U 1 1 5ACBD520
P 8450 2450
F 0 "Q2" H 8650 2525 50  0000 L CNN
F 1 "PHPT60415PY" H 8650 2450 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-669_LFPAK" H 8650 2375 50  0001 L CIN
F 3 "" H 8450 2450 50  0000 L CNN
	1    8450 2450
	1    0    0    1   
$EndComp
$Comp
L C C6
U 1 1 5ACBD526
P 7150 1850
F 0 "C6" H 7175 1950 50  0000 L CNN
F 1 "4.7u" H 7175 1750 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7188 1700 50  0001 C CNN
F 3 "" H 7150 1850 50  0001 C CNN
	1    7150 1850
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 5ACBD52C
P 7400 1850
F 0 "C7" H 7425 1950 50  0000 L CNN
F 1 "100n" H 7425 1750 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7438 1700 50  0001 C CNN
F 3 "" H 7400 1850 50  0001 C CNN
	1    7400 1850
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5ACBD532
P 7150 2500
F 0 "C9" H 7175 2600 50  0000 L CNN
F 1 "4.7u" H 7175 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7188 2350 50  0001 C CNN
F 3 "" H 7150 2500 50  0001 C CNN
	1    7150 2500
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 5ACBD538
P 7400 2500
F 0 "C10" H 7425 2600 50  0000 L CNN
F 1 "100n" H 7425 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7438 2350 50  0001 C CNN
F 3 "" H 7400 2500 50  0001 C CNN
	1    7400 2500
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5ACBD53E
P 6900 1850
F 0 "C5" H 6925 1950 50  0000 L CNN
F 1 "10u" H 6925 1750 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 6938 1700 50  0001 C CNN
F 3 "" H 6900 1850 50  0001 C CNN
	1    6900 1850
	1    0    0    -1  
$EndComp
Text Label 9250 2150 0    60   ~ 0
Gate:A
Text Label 9250 2850 0    60   ~ 0
VSS:A
$Comp
L Conn_01x01 J2
U 1 1 5ACBD546
P 9800 2150
F 0 "J2" H 9800 2250 50  0000 C CNN
F 1 "Gate:A" H 9800 2050 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_2x_1-2mmDrill" H 9800 2150 50  0001 C CNN
F 3 "" H 9800 2150 50  0001 C CNN
	1    9800 2150
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x01 J3
U 1 1 5ACBD54C
P 9800 2850
F 0 "J3" H 9800 2950 50  0000 C CNN
F 1 "VSS:A" H 9800 2750 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_1-2mmDrill" H 9800 2850 50  0001 C CNN
F 3 "" H 9800 2850 50  0001 C CNN
	1    9800 2850
	1    0    0    -1  
$EndComp
Text Label 6000 1050 2    60   ~ 0
VSS:A
Text Label 6000 4950 2    60   ~ 0
VSS:B
$Comp
L MGJ2D241509SC U2
U 1 1 5ACC63D4
P 5050 1050
F 0 "U2" H 5050 1300 60  0000 C CNN
F 1 "MGJ2D241509SC" H 5050 800 60  0000 C CNN
F 2 "Jespers_footprints:SIL_MGJ2" H 5050 700 60  0001 C CNN
F 3 "" H 5050 1550 60  0001 C CNN
	1    5050 1050
	1    0    0    -1  
$EndComp
$Comp
L MGJ2D241509SC U4
U 1 1 5ACC645E
P 5050 4950
F 0 "U4" H 5050 5200 60  0000 C CNN
F 1 "MGJ2D241509SC" H 5050 4700 60  0000 C CNN
F 2 "Jespers_footprints:SIL_MGJ2" H 5050 4600 60  0001 C CNN
F 3 "" H 5050 5450 60  0001 C CNN
	1    5050 4950
	1    0    0    -1  
$EndComp
Text Notes 450  550  0    60   ~ 12
Input connector
Text Notes 2050 550  0    60   ~ 12
Logic supply regulation
Text Notes 4100 550  0    60   ~ 12
Driver Ch. A supply
Text Notes 4100 4450 0    60   ~ 12
Driver Ch. B supply
Text Notes 7800 1450 0    60   ~ 12
Driver A amplification
Text Notes 7800 3150 0    60   ~ 12
Driver B amplification
Text Notes 4400 2000 0    60   ~ 12
Half bridge driver
Wire Wire Line
	850  900  750  900 
Wire Wire Line
	850  800  750  800 
Wire Wire Line
	3150 900  3450 900 
Wire Wire Line
	3650 3300 3900 3300
Wire Wire Line
	3900 3300 3900 3350
Wire Wire Line
	3650 3700 3650 3650
Wire Wire Line
	3900 3700 3900 3650
Wire Wire Line
	4450 2300 4200 2300
Wire Wire Line
	4200 2000 4200 2300
Wire Wire Line
	2750 2000 2800 2000
Wire Wire Line
	3100 2950 3100 3100
Wire Wire Line
	8450 3800 8450 3850
Wire Wire Line
	8550 3800 8550 3850
Connection ~ 8550 3850
Wire Wire Line
	8650 3800 8650 3850
Connection ~ 8650 3850
Connection ~ 8450 3850
Wire Wire Line
	8200 4150 8250 4150
Wire Wire Line
	8200 3550 8200 3850
Wire Wire Line
	8200 3550 8250 3550
Wire Wire Line
	8100 3850 8200 3850
Connection ~ 8200 3850
Wire Wire Line
	5650 3500 6600 3500
Wire Wire Line
	6600 3500 6600 3850
Wire Wire Line
	8550 3300 8550 3350
Wire Wire Line
	6600 3850 7800 3850
Wire Wire Line
	5650 3300 6100 3300
Wire Wire Line
	6300 4400 6900 4400
Wire Wire Line
	8550 4400 8550 4350
Wire Wire Line
	7700 4000 7700 4550
Wire Wire Line
	7150 4000 7400 4000
Wire Wire Line
	7150 3700 7150 4000
Wire Wire Line
	7400 3700 7400 4000
Connection ~ 7400 4000
Connection ~ 7150 4000
Wire Wire Line
	7150 4350 7150 4400
Connection ~ 7150 4400
Wire Wire Line
	7400 4350 7400 4400
Connection ~ 7400 4400
Wire Wire Line
	7150 3400 7150 3300
Connection ~ 7150 3300
Wire Wire Line
	7400 3400 7400 3300
Connection ~ 7400 3300
Wire Wire Line
	6900 3400 6900 3300
Connection ~ 6900 3300
Wire Wire Line
	6900 3700 6900 4400
Connection ~ 6900 4400
Wire Wire Line
	6300 3700 6300 4400
Wire Wire Line
	6300 3700 5650 3700
Connection ~ 6300 4400
Wire Wire Line
	6200 4550 7700 4550
Wire Wire Line
	5650 4800 6100 4800
Wire Wire Line
	6100 4800 6100 3300
Connection ~ 6100 3300
Wire Wire Line
	4200 5100 4200 5150
Wire Wire Line
	4200 5150 4450 5150
Wire Wire Line
	4450 4750 4200 4750
Wire Wire Line
	4200 4700 4200 4750
Connection ~ 4200 5150
Connection ~ 4200 4750
Wire Wire Line
	3450 850  3450 900 
Connection ~ 3450 900 
Wire Wire Line
	2200 1300 2200 1250
Wire Wire Line
	2200 850  2200 900 
Connection ~ 2200 900 
Wire Wire Line
	3450 1350 3450 1250
Wire Wire Line
	2850 1350 2850 1200
Wire Wire Line
	1200 1100 750  1100
Wire Wire Line
	750  1000 1350 1000
Wire Wire Line
	2800 2050 2800 2000
Connection ~ 2800 2000
Wire Wire Line
	2800 2400 2800 2350
Wire Wire Line
	2250 2000 2450 2000
Wire Wire Line
	3100 3700 3100 3650
Wire Wire Line
	2800 3450 2750 3450
Wire Wire Line
	2400 3450 2450 3450
Wire Wire Line
	3100 2500 3100 2650
Connection ~ 3100 3100
Wire Wire Line
	8450 3850 8550 3850
Wire Wire Line
	4450 5150 4450 5100
Wire Wire Line
	4450 4800 4450 4750
Connection ~ 3900 3300
Wire Wire Line
	3650 3300 3650 3350
Wire Wire Line
	3900 2850 3900 2900
Wire Wire Line
	4200 2700 4450 2700
Wire Wire Line
	4200 2500 4200 2700
Wire Wire Line
	3100 2500 3900 2500
Wire Wire Line
	3900 2400 3900 2500
Connection ~ 3900 2500
Wire Wire Line
	3900 2900 4450 2900
Connection ~ 3900 2900
Wire Wire Line
	4200 3700 4450 3700
Wire Wire Line
	3100 3100 4450 3100
Connection ~ 4200 2700
Wire Wire Line
	6300 5100 5650 5100
Wire Wire Line
	5650 1050 6200 1050
Wire Wire Line
	5650 900  6300 900 
Wire Wire Line
	4200 1200 4200 1250
Wire Wire Line
	4200 1250 4450 1250
Wire Wire Line
	4450 850  4200 850 
Wire Wire Line
	4200 800  4200 850 
Connection ~ 4200 1250
Connection ~ 4200 850 
Wire Wire Line
	4450 1250 4450 1200
Wire Wire Line
	4450 900  4450 850 
Wire Wire Line
	6100 1200 5650 1200
Wire Wire Line
	8450 2100 8450 2150
Wire Wire Line
	8550 2100 8550 2150
Connection ~ 8550 2150
Wire Wire Line
	8650 2100 8650 2150
Connection ~ 8650 2150
Connection ~ 8450 2150
Wire Wire Line
	8200 2450 8250 2450
Wire Wire Line
	8200 1850 8200 2150
Wire Wire Line
	8200 1850 8250 1850
Wire Wire Line
	8100 2150 8200 2150
Connection ~ 8200 2150
Wire Wire Line
	5650 2500 6600 2500
Wire Wire Line
	6600 2500 6600 2150
Wire Wire Line
	8550 1600 8550 1650
Wire Wire Line
	6600 2150 7800 2150
Wire Wire Line
	6300 1600 6900 1600
Wire Wire Line
	5650 2700 6100 2700
Wire Wire Line
	8550 2700 8550 2650
Wire Wire Line
	7700 2300 7700 2850
Wire Wire Line
	7150 2300 7400 2300
Wire Wire Line
	7150 2000 7150 2300
Wire Wire Line
	7400 2000 7400 2300
Connection ~ 7400 2300
Connection ~ 7150 2300
Wire Wire Line
	7150 2650 7150 2700
Connection ~ 7150 2700
Wire Wire Line
	7400 2650 7400 2700
Connection ~ 7400 2700
Wire Wire Line
	7150 1700 7150 1600
Connection ~ 7150 1600
Wire Wire Line
	7400 1700 7400 1600
Connection ~ 7400 1600
Wire Wire Line
	6900 1600 6900 1700
Connection ~ 6900 1600
Wire Wire Line
	6900 2000 6900 2700
Connection ~ 6900 2700
Wire Wire Line
	6200 2850 7700 2850
Wire Wire Line
	8450 2150 8550 2150
Wire Wire Line
	6300 900  6300 1600
Wire Wire Line
	6300 2300 5650 2300
Connection ~ 7700 2850
Connection ~ 7700 4550
Connection ~ 6300 1600
Wire Wire Line
	6100 1200 6100 2700
Connection ~ 6100 2700
Wire Wire Line
	6200 1050 6200 2850
Wire Notes Line
	450  650  450  600 
Wire Notes Line
	450  600  1550 600 
Wire Notes Line
	1550 600  1550 650 
Wire Notes Line
	2050 650  2050 600 
Wire Notes Line
	2050 600  3650 600 
Wire Notes Line
	3650 600  3650 650 
Wire Notes Line
	4100 650  4100 600 
Wire Notes Line
	4100 600  6000 600 
Wire Notes Line
	6000 600  6000 650 
Wire Notes Line
	4100 4550 4100 4500
Wire Notes Line
	4100 4500 6000 4500
Wire Notes Line
	6000 4500 6000 4550
Wire Notes Line
	3500 3900 3500 3950
Wire Notes Line
	3500 3950 4100 3950
Wire Notes Line
	4100 3950 4100 3900
Wire Notes Line
	2450 1900 2450 1850
Wire Notes Line
	2450 1850 2950 1850
Wire Notes Line
	2950 1850 2950 1900
Wire Notes Line
	7800 1550 7800 1500
Wire Notes Line
	7800 1500 9200 1500
Wire Notes Line
	9200 1500 9200 1550
Wire Notes Line
	7800 3250 7800 3200
Wire Notes Line
	7800 3200 9200 3200
Wire Notes Line
	9200 3200 9200 3250
Wire Notes Line
	4400 2100 4400 2050
Wire Notes Line
	4400 2050 5800 2050
Wire Notes Line
	5800 2050 5800 2100
Wire Wire Line
	6200 4550 6200 4950
Wire Wire Line
	6200 4950 5650 4950
Wire Wire Line
	2200 900  2550 900 
Wire Wire Line
	1350 950  1350 1000
Connection ~ 1350 1000
Wire Wire Line
	1350 1350 1350 1400
Wire Wire Line
	1350 1400 1200 1400
Wire Wire Line
	1200 1400 1200 1100
Connection ~ 1350 1400
Text Notes 2050 4050 0    60   ~ 12
Signal inverter:
Wire Notes Line
	2050 3900 2050 3950
Wire Notes Line
	2050 3950 3350 3950
Wire Notes Line
	3350 3950 3350 3900
Text Notes 3550 4150 0    60   ~ 0
0.1µs/10kΩ
Text Notes 2050 4150 0    60   ~ 0
Default: Disable
Wire Wire Line
	8550 3850 8550 3900
Wire Wire Line
	8550 3850 8650 3850
Wire Wire Line
	8650 3850 8650 3900
Wire Wire Line
	8650 3850 9600 3850
Wire Wire Line
	8450 3850 8450 3900
Wire Wire Line
	8200 3850 8200 4150
Wire Wire Line
	7400 4000 7700 4000
Wire Wire Line
	7400 4000 7400 4050
Wire Wire Line
	7150 4000 7150 4050
Wire Wire Line
	7150 4400 7400 4400
Wire Wire Line
	7400 4400 8550 4400
Wire Wire Line
	7150 3300 7400 3300
Wire Wire Line
	7400 3300 8550 3300
Wire Wire Line
	6900 3300 7150 3300
Wire Wire Line
	6900 4400 7150 4400
Wire Wire Line
	6300 4400 6300 5100
Wire Wire Line
	6100 3300 6900 3300
Wire Wire Line
	4200 5150 4200 5200
Wire Wire Line
	4200 4750 4200 4800
Wire Wire Line
	3450 900  3450 950 
Wire Wire Line
	2200 900  2200 950 
Wire Wire Line
	2800 2000 4200 2000
Wire Wire Line
	3100 3100 3100 3250
Wire Wire Line
	3900 3300 4450 3300
Wire Wire Line
	3900 2500 4200 2500
Wire Wire Line
	3900 2500 3900 2550
Wire Wire Line
	4200 2700 4200 3700
Wire Wire Line
	4200 1250 4200 1300
Wire Wire Line
	4200 850  4200 900 
Wire Wire Line
	8550 2150 8550 2200
Wire Wire Line
	8550 2150 8650 2150
Wire Wire Line
	8650 2150 8650 2200
Wire Wire Line
	8650 2150 9600 2150
Wire Wire Line
	8450 2150 8450 2200
Wire Wire Line
	8200 2150 8200 2450
Wire Wire Line
	7400 2300 7700 2300
Wire Wire Line
	7400 2300 7400 2350
Wire Wire Line
	7150 2300 7150 2350
Wire Wire Line
	7150 2700 7400 2700
Wire Wire Line
	7400 2700 8550 2700
Wire Wire Line
	7150 1600 7400 1600
Wire Wire Line
	7400 1600 8550 1600
Wire Wire Line
	6900 1600 7150 1600
Wire Wire Line
	6900 2700 7150 2700
Wire Wire Line
	7700 2850 9600 2850
Wire Wire Line
	7700 4550 9600 4550
Wire Wire Line
	6300 1600 6300 2300
Wire Wire Line
	6100 2700 6900 2700
Wire Wire Line
	1350 1000 1350 1050
Wire Wire Line
	1350 1400 1350 1450
$EndSCHEMATC
