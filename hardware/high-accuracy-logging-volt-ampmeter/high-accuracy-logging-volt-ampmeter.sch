EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "High-accuracy logging volt/amp meter"
Date "2021-02-04"
Rev "v1.0"
Comp "Brecht Van Eeckhoudt"
Comment1 "kicad.brechtve.be"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L BrechtVE_Aesthetics:Symbol_OSHW-Logo_11.4x12mm G1
U 1 1 5E4BD295
P 10950 6400
F 0 "G1" H 10950 6195 60  0001 C CNN
F 1 "Symbol_OSHW-Logo_11.4x12mm" H 10950 6605 60  0001 C CNN
F 2 "BrechtVE_Aesthetics:OSHW-Logo_5.7x6mm_SolderMask" H 10950 6400 50  0001 C CNN
F 3 "" H 10950 6400 50  0001 C CNN
	1    10950 6400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J14
U 1 1 5FC6E1FB
P 9050 3750
F 0 "J14" H 9050 4050 50  0000 C CNN
F 1 "UART Out" H 9050 3350 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B6B-XH-A_1x06_P2.50mm_Vertical" H 9050 3750 50  0001 C CNN
F 3 "~" H 9050 3750 50  0001 C CNN
	1    9050 3750
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J5
U 1 1 5FC57C54
P 3100 6700
F 0 "J5" H 3100 6900 50  0000 C CNN
F 1 "USB" H 3100 6400 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B4B-XH-A_1x04_P2.50mm_Vertical" H 3100 6700 50  0001 C CNN
F 3 "~" H 3100 6700 50  0001 C CNN
	1    3100 6700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J6
U 1 1 5FDD58F7
P 3200 3650
F 0 "J6" H 3300 3700 50  0000 L CNN
F 1 "~RESET" H 3300 3600 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3200 3650 50  0001 C CNN
F 3 "~" H 3200 3650 50  0001 C CNN
	1    3200 3650
	1    0    0    -1  
$EndComp
Text Label 1550 4050 2    50   ~ 0
USB_DM
Text Label 1550 4150 2    50   ~ 0
USB_DP
Text Label 2900 6700 2    50   ~ 0
USB_DP
Text Label 2900 6800 2    50   ~ 0
USB_DM
Text Label 2900 6900 2    50   ~ 0
GND
Text Label 1550 3850 2    50   ~ 0
TXD1_3V3
Text Label 1550 3950 2    50   ~ 0
RXD1_3V3
Text Label 2750 3450 0    50   ~ 0
GND
Text Label 2750 3550 0    50   ~ 0
3V3
Text Label 1550 5250 2    50   ~ 0
3V3
Text Label 2750 4650 0    50   ~ 0
TXD2_3V3
Text Label 2750 4550 0    50   ~ 0
RXD2_3V3
Text Label 2750 3750 0    50   ~ 0
RXD3_3V3
Text Label 2750 3850 0    50   ~ 0
TXD3_3V3
Text Label 2000 2150 2    50   ~ 0
TXD2_3V3
Text Label 10300 3650 2    50   ~ 0
TXD1_3V3
Text Label 10850 3750 2    50   ~ 0
RXD1_3V3
Text Label 9650 3950 2    50   ~ 0
GND
Text Label 1550 5150 2    50   ~ 0
GND
Text Label 9650 4050 2    50   ~ 0
GND
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 5FEB9AC1
P 1250 4350
F 0 "J2" H 1350 4400 50  0000 L CNN
F 1 "SWO" H 1350 4300 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1250 4350 50  0001 C CNN
F 3 "~" H 1250 4350 50  0001 C CNN
	1    1250 4350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1450 4350 1550 4350
Wire Wire Line
	2750 3650 3000 3650
Text Label 1550 4650 2    50   ~ 0
SCL1_3V3
Text Label 1550 4750 2    50   ~ 0
SDA1_3V3
Text Label 2900 6600 2    50   ~ 0
VUSB
$Comp
L Connector_Generic:Conn_01x03 J13
U 1 1 5FF2419E
P 7750 5350
F 0 "J13" H 7750 5550 50  0000 C CNN
F 1 "Switch" H 7750 5150 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B3B-XH-A_1x03_P2.50mm_Vertical" H 7750 5350 50  0001 C CNN
F 3 "~" H 7750 5350 50  0001 C CNN
	1    7750 5350
	1    0    0    -1  
$EndComp
Text Label 9900 1250 2    50   ~ 0
SCL1_3V3
Text Label 9900 1950 2    50   ~ 0
SCL1_3V3
Text Label 9900 2050 2    50   ~ 0
3V3
Text Label 9900 1350 2    50   ~ 0
3V3
Text Label 9900 1450 2    50   ~ 0
GND
Text Label 9900 2150 2    50   ~ 0
GND
Text Label 9900 1850 2    50   ~ 0
SDA1_3V3
Text Label 9900 1150 2    50   ~ 0
SDA1_3V3
$Comp
L high-accuracy-logging-volt-ampmeter:1.3"-128x64-I2C-OLED U2
U 1 1 5FDE3379
P 10300 1300
F 0 "U2" V 10350 1100 50  0000 R CNN
F 1 "1.3\"-128x64" V 10250 1100 50  0000 R CNN
F 2 "high-accuracy-logging-volt-ampmeter:1.3INCH-128x64-I2C-OLED-NoHoles" H 10250 1300 50  0001 C CNN
F 3 "" H 10250 1300 50  0001 C CNN
	1    10300 1300
	0    -1   -1   0   
$EndComp
$Comp
L high-accuracy-logging-volt-ampmeter:STM32F103 U1
U 1 1 5FDE6F27
P 2150 4350
F 0 "U1" H 2150 5615 50  0000 C CNN
F 1 "STM32F103" H 2150 5524 50  0000 C CNN
F 2 "high-accuracy-logging-volt-ampmeter:STM32F103" H 2150 4350 50  0001 C CNN
F 3 "" H 2150 4350 50  0001 C CNN
	1    2150 4350
	1    0    0    -1  
$EndComp
$Comp
L high-accuracy-logging-volt-ampmeter:1.3"-128x64-I2C-OLED U3
U 1 1 5FE0CF4C
P 10300 2000
F 0 "U3" V 10350 1800 50  0000 R CNN
F 1 "1.3\"-128x64" V 10250 1800 50  0000 R CNN
F 2 "high-accuracy-logging-volt-ampmeter:1.3INCH-128x64-I2C-OLED-NoHoles" H 10250 2000 50  0001 C CNN
F 3 "" H 10250 2000 50  0001 C CNN
	1    10300 2000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R20
U 1 1 5FE28C8E
P 8650 1200
F 0 "R20" H 8700 1250 50  0000 L CNN
F 1 "10 kΩ" H 8700 1150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 1200 50  0001 C CNN
F 3 "~" H 8650 1200 50  0001 C CNN
	1    8650 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R21
U 1 1 5FE28F6C
P 8650 1650
F 0 "R21" H 8700 1700 50  0000 L CNN
F 1 "10 kΩ" H 8700 1600 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 1650 50  0001 C CNN
F 3 "~" H 8650 1650 50  0001 C CNN
	1    8650 1650
	1    0    0    -1  
$EndComp
Text Label 9050 1050 2    50   ~ 0
3V3
Text Label 9050 1500 2    50   ~ 0
3V3
Text Label 9050 1350 2    50   ~ 0
SDA1_3V3
Text Label 9050 1800 2    50   ~ 0
SCL1_3V3
$Comp
L Device:R_Small R25
U 1 1 5FE2FB7A
P 9850 3650
F 0 "R25" V 9650 3650 50  0000 C CNN
F 1 "100 Ω" V 9750 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9850 3650 50  0001 C CNN
F 3 "~" H 9850 3650 50  0001 C CNN
	1    9850 3650
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R27
U 1 1 5FE30BC5
P 10400 3600
F 0 "R27" H 10450 3650 50  0000 L CNN
F 1 "10 kΩ" H 10450 3550 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 10400 3600 50  0001 C CNN
F 3 "~" H 10400 3600 50  0001 C CNN
	1    10400 3600
	1    0    0    -1  
$EndComp
Text Label 10600 3450 2    50   ~ 0
3V3
$Comp
L Device:R_Small R26
U 1 1 5FE36D4F
P 9850 3750
F 0 "R26" V 9950 3750 50  0000 C CNN
F 1 "100 Ω" V 10050 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9850 3750 50  0001 C CNN
F 3 "~" H 9850 3750 50  0001 C CNN
	1    9850 3750
	0    -1   1    0   
$EndComp
$Comp
L Transistor_FET:2N7002 Q4
U 1 1 5FE654D6
P 9300 5350
F 0 "Q4" H 9500 5400 50  0000 L CNN
F 1 "2N7002-7-F" H 9500 5300 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 9500 5275 50  0001 L CIN
F 3 "https://www.mouser.be/datasheet/2/115/2N7002-1591994.pdf" H 9300 5350 50  0001 L CNN
	1    9300 5350
	-1   0    0    -1  
$EndComp
Text Label 9400 5050 2    50   ~ 0
3V3
$Comp
L Device:R_Small R3
U 1 1 5FE9918D
P 2350 1200
F 0 "R3" H 2400 1250 50  0000 L CNN
F 1 "1 kΩ" H 2400 1150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2350 1200 50  0001 C CNN
F 3 "~" H 2350 1200 50  0001 C CNN
	1    2350 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 5FE9DD34
P 2350 1500
F 0 "R4" H 2400 1550 50  0000 L CNN
F 1 "2 kΩ" H 2400 1450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2350 1500 50  0001 C CNN
F 3 "~" H 2350 1500 50  0001 C CNN
	1    2350 1500
	1    0    0    -1  
$EndComp
Text Label 2750 1650 2    50   ~ 0
GND
Wire Wire Line
	2350 1400 2350 1350
Text Label 2750 1050 2    50   ~ 0
RXD2_5V
Text Label 2750 1350 2    50   ~ 0
RXD2_3V3
$Comp
L Device:R_Small R9
U 1 1 5FEA9D37
P 5050 1200
F 0 "R9" H 5100 1250 50  0000 L CNN
F 1 "1 kΩ" H 5100 1150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5050 1200 50  0001 C CNN
F 3 "~" H 5050 1200 50  0001 C CNN
	1    5050 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R10
U 1 1 5FEA9D3D
P 5050 1500
F 0 "R10" H 5100 1550 50  0000 L CNN
F 1 "2 kΩ" H 5100 1450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5050 1500 50  0001 C CNN
F 3 "~" H 5050 1500 50  0001 C CNN
	1    5050 1500
	1    0    0    -1  
$EndComp
Text Label 5450 1650 2    50   ~ 0
GND
Wire Wire Line
	5050 1400 5050 1350
Text Label 5450 1050 2    50   ~ 0
RXD3_5V
Text Label 5450 1350 2    50   ~ 0
RXD3_3V3
$Comp
L Transistor_FET:2N7002 Q1
U 1 1 5FEADD85
P 1350 1850
F 0 "Q1" H 1550 1900 50  0000 L CNN
F 1 "2N7002-7-F" H 1550 1800 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 1550 1775 50  0001 L CIN
F 3 "https://www.mouser.be/datasheet/2/115/2N7002-1591994.pdf" H 1350 1850 50  0001 L CNN
	1    1350 1850
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5FECADDE
P 1600 2000
F 0 "R2" H 1650 2050 50  0000 L CNN
F 1 "10 kΩ" H 1650 1950 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1600 2000 50  0001 C CNN
F 3 "~" H 1600 2000 50  0001 C CNN
	1    1600 2000
	1    0    0    -1  
$EndComp
Text Label 1600 1600 2    50   ~ 0
TXD2_5V
Text Label 4700 2150 2    50   ~ 0
TXD3_3V3
$Comp
L Device:R_Small R5
U 1 1 5FF21AA7
P 3950 1450
F 0 "R5" H 4000 1500 50  0000 L CNN
F 1 "10 kΩ" H 4000 1400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3950 1450 50  0001 C CNN
F 3 "~" H 3950 1450 50  0001 C CNN
	1    3950 1450
	1    0    0    -1  
$EndComp
Text Label 4300 1600 2    50   ~ 0
TXD3_5V
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 5FF360CD
P 1250 1050
F 0 "J1" V 1300 1150 50  0000 L CNN
F 1 "5Vin-Voltage" V 1200 1150 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1250 1050 50  0001 C CNN
F 3 "~" H 1250 1050 50  0001 C CNN
	1    1250 1050
	0    1    -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J8
U 1 1 5FF38C19
P 3950 1050
F 0 "J8" V 4000 1150 50  0000 L CNN
F 1 "5Vin-Current" V 3900 1150 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3950 1050 50  0001 C CNN
F 3 "~" H 3950 1050 50  0001 C CNN
	1    3950 1050
	0    1    -1   0   
$EndComp
Wire Wire Line
	9200 5550 9200 5600
Wire Wire Line
	9750 3650 9250 3650
Wire Wire Line
	9750 3750 9250 3750
$Comp
L Connector_Generic:Conn_01x02 J12
U 1 1 5FFD795F
P 6450 3350
F 0 "J12" H 6450 3450 50  0000 C CNN
F 1 "Relay" H 6450 3150 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 6450 3350 50  0001 C CNN
F 3 "~" H 6450 3350 50  0001 C CNN
	1    6450 3350
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 60007248
P 1650 6700
F 0 "J3" H 1650 6900 50  0000 C CNN
F 1 "Vin/batt/out" H 1650 6400 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B4B-XH-A_1x04_P2.50mm_Vertical" H 1650 6700 50  0001 C CNN
F 3 "~" H 1650 6700 50  0001 C CNN
	1    1650 6700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J11
U 1 1 5FDF576F
P 5950 6700
F 0 "J11" H 5950 6900 50  0000 C CNN
F 1 "GPIO" H 5950 6400 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B4B-XH-A_1x04_P2.50mm_Vertical" H 5950 6700 50  0001 C CNN
F 3 "~" H 5950 6700 50  0001 C CNN
	1    5950 6700
	1    0    0    -1  
$EndComp
Text Label 1550 4950 2    50   ~ 0
DTR
Text Label 9650 3550 2    50   ~ 0
DTR
Text Label 5750 6900 2    50   ~ 0
3V3
Text Label 5750 6800 2    50   ~ 0
GND
Text Label 1550 4550 2    50   ~ 0
ENC-Key
Text Label 2750 5150 0    50   ~ 0
ENC-S2
Text Label 2750 4350 0    50   ~ 0
ENC-S1
Text Label 7550 5250 2    50   ~ 0
SW0
Text Label 7550 5450 2    50   ~ 0
SW1
Text Label 2750 4850 0    50   ~ 0
SW0
Text Label 2750 4750 0    50   ~ 0
SW1
Text Label 6950 4000 2    50   ~ 0
GND
$Comp
L Device:R_Small R17
U 1 1 5FE1DBFF
P 7100 3900
F 0 "R17" H 7150 3950 50  0000 L CNN
F 1 "10 kΩ" H 7150 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7100 3900 50  0001 C CNN
F 3 "~" H 7100 3900 50  0001 C CNN
	1    7100 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R23
U 1 1 5FE1FA44
P 9650 5200
F 0 "R23" H 9700 5250 50  0000 L CNN
F 1 "10 kΩ" H 9700 5150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9650 5200 50  0001 C CNN
F 3 "~" H 9650 5200 50  0001 C CNN
	1    9650 5200
	1    0    0    -1  
$EndComp
Connection ~ 9650 5350
Wire Wire Line
	9650 5350 9500 5350
Text Label 7300 4050 2    50   ~ 0
GND
Wire Wire Line
	7050 3750 7100 3750
Text Label 7900 3750 2    50   ~ 0
RELAY
Text Label 1550 3750 2    50   ~ 0
RELAY
$Comp
L Device:R_Small R14
U 1 1 5FE9685F
P 6500 5200
F 0 "R14" H 6550 5150 50  0000 L CNN
F 1 "10 kΩ" H 6550 5250 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6500 5200 50  0001 C CNN
F 3 "~" H 6500 5200 50  0001 C CNN
	1    6500 5200
	1    0    0    1   
$EndComp
$Comp
L Device:R_Small R11
U 1 1 5FE980E8
P 5950 5200
F 0 "R11" H 6000 5250 50  0000 L CNN
F 1 "10 kΩ" H 6000 5150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5950 5200 50  0001 C CNN
F 3 "~" H 5950 5200 50  0001 C CNN
	1    5950 5200
	1    0    0    -1  
$EndComp
Text Label 6750 5050 2    50   ~ 0
3V3
Text Label 6200 5050 2    50   ~ 0
3V3
$Comp
L Device:Buzzer BZ1
U 1 1 5FEE9E5C
P 4650 5200
F 0 "BZ1" H 4800 5250 50  0000 L CNN
F 1 "Buzzer" H 4800 5150 50  0000 L CNN
F 2 "Buzzer_Beeper:Buzzer_12x9.5RM7.6" V 4625 5300 50  0001 C CNN
F 3 "~" V 4625 5300 50  0001 C CNN
	1    4650 5200
	1    0    0    -1  
$EndComp
Text Label 4550 5300 2    50   ~ 0
GND
Text Label 1550 3450 2    50   ~ 0
BUZZER
Text Label 4550 5100 2    50   ~ 0
BUZZER
$Comp
L Device:C_Small C1
U 1 1 5FDFDD30
P 5950 5500
F 0 "C1" H 6050 5450 50  0000 L CNN
F 1 "100 nF" H 6050 5550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5950 5500 50  0001 C CNN
F 3 "~" H 5950 5500 50  0001 C CNN
	1    5950 5500
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5FE17E0C
P 6500 5500
F 0 "C2" H 6600 5550 50  0000 L CNN
F 1 "100 nF" H 6600 5450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6500 5500 50  0001 C CNN
F 3 "~" H 6500 5500 50  0001 C CNN
	1    6500 5500
	1    0    0    -1  
$EndComp
Text Label 6750 5650 2    50   ~ 0
GND
Text Label 6200 5650 2    50   ~ 0
GND
$Comp
L Device:R_Small R19
U 1 1 5FE37BEA
P 7550 3750
F 0 "R19" V 7650 3750 50  0000 C CNN
F 1 "100 Ω" V 7750 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7550 3750 50  0001 C CNN
F 3 "~" H 7550 3750 50  0001 C CNN
	1    7550 3750
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R24
U 1 1 5FE45E31
P 9800 5350
F 0 "R24" V 9900 5350 50  0000 C CNN
F 1 "100 Ω" V 10000 5350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9800 5350 50  0001 C CNN
F 3 "~" H 9800 5350 50  0001 C CNN
	1    9800 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	9700 5350 9650 5350
$Comp
L Device:R_Small R18
U 1 1 5FDFE0BD
P 7250 5350
F 0 "R18" V 7350 5350 50  0000 C CNN
F 1 "1 kΩ" V 7450 5350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7250 5350 50  0001 C CNN
F 3 "~" H 7250 5350 50  0001 C CNN
	1    7250 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	10450 5350 9900 5350
$Comp
L Device:R_Small R22
U 1 1 5FF2C590
P 9300 3400
F 0 "R22" H 9350 3450 50  0000 L CNN
F 1 "10 kΩ" H 9350 3350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9300 3400 50  0001 C CNN
F 3 "~" H 9300 3400 50  0001 C CNN
	1    9300 3400
	1    0    0    -1  
$EndComp
Text Label 9500 3250 2    50   ~ 0
3V3
Text Label 9850 5050 2    50   ~ 0
3V3
Text Label 5750 6600 2    50   ~ 0
GPIO1
Text Label 5750 6700 2    50   ~ 0
GPIO2
Text Label 2750 4250 0    50   ~ 0
GPIO1
Text Label 2750 4150 0    50   ~ 0
GPIO2
$Comp
L Device:R_Small R7
U 1 1 5FFDF0DF
P 4550 3400
F 0 "R7" H 4600 3450 50  0000 L CNN
F 1 "10 kΩ" H 4600 3350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4550 3400 50  0001 C CNN
F 3 "~" H 4550 3400 50  0001 C CNN
	1    4550 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R8
U 1 1 5FFDF0E5
P 4550 3700
F 0 "R8" H 4600 3750 50  0000 L CNN
F 1 "20 kΩ" H 4600 3650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4550 3700 50  0001 C CNN
F 3 "~" H 4550 3700 50  0001 C CNN
	1    4550 3700
	1    0    0    -1  
$EndComp
Text Label 4750 3850 2    50   ~ 0
GND
Wire Wire Line
	4550 3600 4550 3550
Text Label 4750 3550 2    50   ~ 0
ADC
Text Label 2750 4050 0    50   ~ 0
ADC
NoConn ~ 1550 3550
NoConn ~ 1550 3650
NoConn ~ 1550 3350
NoConn ~ 1550 4250
NoConn ~ 1550 4450
NoConn ~ 2750 4950
Text Label 4700 1850 2    50   ~ 0
3V3
Text Label 2000 1850 2    50   ~ 0
3V3
$Comp
L Device:R_Small R12
U 1 1 5FE59959
P 6400 1200
F 0 "R12" H 6450 1250 50  0000 L CNN
F 1 "1 kΩ" H 6450 1150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6400 1200 50  0001 C CNN
F 3 "~" H 6400 1200 50  0001 C CNN
	1    6400 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R13
U 1 1 5FE5995F
P 6400 1500
F 0 "R13" H 6450 1550 50  0000 L CNN
F 1 "2 kΩ" H 6450 1450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6400 1500 50  0001 C CNN
F 3 "~" H 6400 1500 50  0001 C CNN
	1    6400 1500
	1    0    0    -1  
$EndComp
Text Label 6750 1650 2    50   ~ 0
GND
Wire Wire Line
	6400 1400 6400 1350
$Comp
L Device:R_Small R15
U 1 1 5FE59969
P 7050 1200
F 0 "R15" H 7100 1250 50  0000 L CNN
F 1 "1 kΩ" H 7100 1150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7050 1200 50  0001 C CNN
F 3 "~" H 7050 1200 50  0001 C CNN
	1    7050 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R16
U 1 1 5FE5996F
P 7050 1500
F 0 "R16" H 7100 1550 50  0000 L CNN
F 1 "2 kΩ" H 7100 1450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7050 1500 50  0001 C CNN
F 3 "~" H 7050 1500 50  0001 C CNN
	1    7050 1500
	1    0    0    -1  
$EndComp
Text Label 7400 1650 2    50   ~ 0
GND
Wire Wire Line
	7050 1400 7050 1350
Text Label 1600 1300 2    50   ~ 0
V-5Vin
Text Label 4300 1300 2    50   ~ 0
A-5Vin
Text Label 6750 1050 2    50   ~ 0
V-5Vin
Text Label 7400 1050 2    50   ~ 0
A-5Vin
Text Label 2750 3950 0    50   ~ 0
A-ENin
Text Label 7400 1350 2    50   ~ 0
A-ENin
Text Label 2750 4450 0    50   ~ 0
V-ENin
Text Label 6750 1350 2    50   ~ 0
V-ENin
Wire Wire Line
	5050 1100 5050 1050
Wire Wire Line
	5050 1050 5450 1050
Wire Wire Line
	5050 1350 5450 1350
Connection ~ 5050 1350
Wire Wire Line
	5050 1350 5050 1300
Wire Wire Line
	5050 1600 5050 1650
Wire Wire Line
	5050 1650 5450 1650
Wire Wire Line
	2350 1350 2750 1350
Connection ~ 2350 1350
Wire Wire Line
	2350 1350 2350 1300
Wire Wire Line
	2350 1600 2350 1650
Wire Wire Line
	2350 1650 2750 1650
Wire Wire Line
	2350 1100 2350 1050
Wire Wire Line
	2350 1050 2750 1050
Wire Wire Line
	6400 1100 6400 1050
Wire Wire Line
	6400 1050 6750 1050
Wire Wire Line
	6400 1600 6400 1650
Wire Wire Line
	6400 1650 6750 1650
Wire Wire Line
	6400 1350 6750 1350
Connection ~ 6400 1350
Wire Wire Line
	6400 1350 6400 1300
Wire Wire Line
	7050 1100 7050 1050
Wire Wire Line
	7050 1050 7400 1050
Wire Wire Line
	7050 1350 7400 1350
Connection ~ 7050 1350
Wire Wire Line
	7050 1350 7050 1300
Wire Wire Line
	7050 1600 7050 1650
Wire Wire Line
	7050 1650 7400 1650
$Comp
L Device:R_Small R1
U 1 1 5FE25FD9
P 1250 1450
F 0 "R1" H 1300 1400 50  0000 L CNN
F 1 "10 kΩ" H 1300 1500 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1250 1450 50  0001 C CNN
F 3 "~" H 1250 1450 50  0001 C CNN
	1    1250 1450
	1    0    0    1   
$EndComp
Wire Wire Line
	1250 1250 1250 1300
Wire Wire Line
	1250 1300 1600 1300
Connection ~ 1250 1300
Wire Wire Line
	1250 1300 1250 1350
Wire Wire Line
	3950 1250 3950 1300
Wire Wire Line
	3950 1300 4300 1300
Connection ~ 3950 1300
Wire Wire Line
	3950 1300 3950 1350
$Comp
L Device:R_Small R6
U 1 1 5FE27C02
P 4300 2000
F 0 "R6" H 4350 1950 50  0000 L CNN
F 1 "10 kΩ" H 4350 2050 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4300 2000 50  0001 C CNN
F 3 "~" H 4300 2000 50  0001 C CNN
	1    4300 2000
	1    0    0    1   
$EndComp
Wire Wire Line
	4550 3300 4550 3250
Wire Wire Line
	4550 3250 4750 3250
Wire Wire Line
	4550 3550 4750 3550
Connection ~ 4550 3550
Wire Wire Line
	4550 3550 4550 3500
Wire Wire Line
	4550 3800 4550 3850
Wire Wire Line
	4550 3850 4750 3850
Text Label 9650 3850 2    50   ~ 0
UART1-3V3
Text Label 1550 4850 2    50   ~ 0
UART1-ENout
Text Label 10450 5350 2    50   ~ 0
UART1-ENout
Text Label 9650 5600 2    50   ~ 0
UART1-3V3
Wire Wire Line
	9200 5150 9200 5050
Wire Wire Line
	9200 5050 9400 5050
Wire Wire Line
	9200 5600 9650 5600
Wire Wire Line
	9650 5300 9650 5350
Wire Wire Line
	9650 5100 9650 5050
Wire Wire Line
	9650 5050 9850 5050
Wire Wire Line
	9250 3550 9300 3550
Wire Wire Line
	9300 3550 9300 3500
Connection ~ 9300 3550
Wire Wire Line
	9300 3550 9650 3550
Wire Wire Line
	9300 3300 9300 3250
Wire Wire Line
	9300 3250 9500 3250
Wire Wire Line
	9250 3850 9650 3850
Wire Wire Line
	9250 3950 9650 3950
Wire Wire Line
	9250 4050 9650 4050
Text Notes 8950 3585 2    50   ~ 0
DTR (~RESET)
Text Notes 8950 4085 2    50   ~ 0
GND
Text Notes 8950 3985 2    50   ~ 0
CTS (GND)
Text Notes 8950 3885 2    50   ~ 0
3V3
Text Notes 8950 3785 2    50   ~ 0
RXD 3V3
Text Notes 8950 3685 2    50   ~ 0
TXD 3V3
Wire Wire Line
	9950 3750 10400 3750
Wire Wire Line
	9950 3650 10300 3650
Wire Wire Line
	10400 3700 10400 3750
Connection ~ 10400 3750
Wire Wire Line
	10400 3750 10850 3750
Wire Wire Line
	10400 3500 10400 3450
Wire Wire Line
	10400 3450 10600 3450
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 5FDF1B91
P 5500 2000
F 0 "J4" H 5500 2200 50  0000 C CNN
F 1 "BY56W Current" H 5500 1800 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5500 2000 50  0001 C CNN
F 3 "~" H 5500 2000 50  0001 C CNN
	1    5500 2000
	1    0    0    -1  
$EndComp
Text Label 5300 2100 2    50   ~ 0
TXD3_5V
Text Label 5300 2000 2    50   ~ 0
GND
Text Label 5300 1900 2    50   ~ 0
RXD3_5V
Text Label 1450 6900 2    50   ~ 0
VUSB
Text Label 1450 6800 2    50   ~ 0
Vbatt
Text Label 1450 6600 2    50   ~ 0
GND
Text Label 4400 6850 2    50   ~ 0
ENC-S1
Text Label 4400 6750 2    50   ~ 0
ENC-S2
Text Label 4400 6650 2    50   ~ 0
ENC-Key
Text Label 4400 6950 2    50   ~ 0
GND
Text Label 4400 6550 2    50   ~ 0
3V3
$Comp
L Connector_Generic:Conn_01x05 J9
U 1 1 5FF321A1
P 4600 6750
F 0 "J9" H 4600 7050 50  0000 C CNN
F 1 "Encoder" H 4600 6450 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B5B-XH-A_1x05_P2.50mm_Vertical" H 4600 6750 50  0001 C CNN
F 3 "~" H 4600 6750 50  0001 C CNN
	1    4600 6750
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7002 Q3
U 1 1 6001812A
P 6850 3750
F 0 "Q3" H 7050 3800 50  0000 L CNN
F 1 "2N7002-7-F" H 7050 3700 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 7050 3675 50  0001 L CIN
F 3 "https://www.mouser.be/datasheet/2/115/2N7002-1591994.pdf" H 6850 3750 50  0001 L CNN
	1    6850 3750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7100 4000 7100 4050
Wire Wire Line
	7100 4050 7300 4050
Wire Wire Line
	7100 3800 7100 3750
Wire Wire Line
	7100 3750 7450 3750
Connection ~ 7100 3750
Wire Wire Line
	6750 4000 6950 4000
Wire Wire Line
	6750 3950 6750 4000
Wire Wire Line
	7650 3750 7900 3750
Wire Wire Line
	8650 1100 8650 1050
Wire Wire Line
	8650 1050 9050 1050
Wire Wire Line
	8650 1300 8650 1350
Wire Wire Line
	8650 1350 9050 1350
Wire Wire Line
	8650 1550 8650 1500
Wire Wire Line
	8650 1500 9050 1500
Wire Wire Line
	8650 1750 8650 1800
Wire Wire Line
	8650 1800 9050 1800
Text Label 6200 5350 2    50   ~ 0
SW0
Wire Wire Line
	5950 5100 5950 5050
Wire Wire Line
	5950 5050 6200 5050
Wire Wire Line
	5950 5300 5950 5350
Wire Wire Line
	5950 5350 6200 5350
Connection ~ 5950 5350
Wire Wire Line
	5950 5350 5950 5400
Wire Wire Line
	5950 5600 5950 5650
Wire Wire Line
	5950 5650 6200 5650
Text Label 6750 5350 2    50   ~ 0
SW1
Wire Wire Line
	6500 5100 6500 5050
Wire Wire Line
	6500 5050 6750 5050
Wire Wire Line
	6500 5300 6500 5350
Wire Wire Line
	6500 5350 6750 5350
Connection ~ 6500 5350
Wire Wire Line
	6500 5350 6500 5400
Wire Wire Line
	6500 5600 6500 5650
Wire Wire Line
	6500 5650 6750 5650
Text Label 7000 5350 0    50   ~ 0
GND
Wire Wire Line
	7350 5350 7550 5350
Wire Wire Line
	7150 5350 7000 5350
Text Label 1450 6700 2    50   ~ 0
3V3
NoConn ~ 2750 3350
NoConn ~ 1550 5050
Wire Wire Line
	3950 1650 3950 1600
Wire Wire Line
	3950 1600 4300 1600
Connection ~ 3950 1600
Wire Wire Line
	3950 1600 3950 1550
$Comp
L Transistor_FET:2N7002 Q2
U 1 1 5FF21AA1
P 4050 1850
F 0 "Q2" H 4250 1900 50  0000 L CNN
F 1 "2N7002-7-F" H 4250 1800 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 4250 1775 50  0001 L CIN
F 3 "https://www.mouser.be/datasheet/2/115/2N7002-1591994.pdf" H 4050 1850 50  0001 L CNN
	1    4050 1850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3950 2150 4300 2150
Wire Wire Line
	3950 2050 3950 2150
Wire Wire Line
	4300 2100 4300 2150
Connection ~ 4300 2150
Wire Wire Line
	4300 2150 4700 2150
Wire Wire Line
	4250 1850 4300 1850
Wire Wire Line
	4300 1850 4300 1900
Wire Wire Line
	4300 1850 4700 1850
Connection ~ 4300 1850
Wire Wire Line
	1250 1550 1250 1600
Wire Wire Line
	1250 1600 1600 1600
Connection ~ 1250 1600
Wire Wire Line
	1250 1600 1250 1650
Wire Wire Line
	1550 1850 1600 1850
Wire Wire Line
	1600 1850 1600 1900
Wire Wire Line
	1600 1850 2000 1850
Connection ~ 1600 1850
Wire Wire Line
	1250 2050 1250 2150
Wire Wire Line
	1250 2150 1600 2150
Wire Wire Line
	1600 2150 1600 2100
Connection ~ 1600 2150
Wire Wire Line
	1600 2150 2000 2150
Text Notes 6350 3380 2    50   ~ 0
Relay+
Text Notes 6350 3480 2    50   ~ 0
Relay-
Text Notes 1300 6700 2    50   ~ 0
VIN
Text Notes 1200 800  0    50   ~ 0
UART Voltage Level Translation (Voltage Meter)
Text Notes 3900 800  0    50   ~ 0
UART Voltage Level Translation (Current Meter)
Text Notes 6200 800  0    50   ~ 0
Voltage/Current Meter Status Indication
Text Notes 9200 3050 0    50   ~ 0
External UART Header
Text Notes 8750 4800 0    50   ~ 0
External UART Header (Supply Voltage Switching)
Text Notes 6700 3050 0    50   ~ 0
Relay Contact
Text Notes 6100 4800 0    50   ~ 0
SPDT (ON)-OFF-(ON) Switch & Filtering
Text Notes 8450 800  0    50   ~ 0
I2C Pull-up Resistors
Text Notes 9900 800  0    50   ~ 0
I2C OLED Displays
Text Notes 4150 3050 0    50   ~ 0
Battery Voltage Measurement
Text Notes 1250 6300 0    50   ~ 0
Power In/Out
Text Notes 2450 6300 0    50   ~ 0
External USB Connection
Text Notes 4150 6300 0    50   ~ 0
Rotary Encoder
Text Notes 5500 6300 0    50   ~ 0
External GPIO
Text Label 6950 3250 2    50   ~ 0
3V3
Text Notes 6100 4250 0    50   ~ 10
NOTE:
Wire Wire Line
	6750 3450 6750 3550
Wire Wire Line
	6650 3450 6750 3450
Wire Wire Line
	6650 3350 6750 3350
Wire Wire Line
	6750 3350 6750 3250
Wire Wire Line
	6750 3250 6950 3250
Text Notes 6350 4250 0    50   ~ 0
Put Diode & Boost-circuit near Relay
Text Label 4750 3250 2    50   ~ 0
Vbatt
Text Label 3000 5350 2    50   ~ 0
GND
$Comp
L Connector_Generic:Conn_01x02 J7
U 1 1 5FE9A6DD
P 3200 5250
F 0 "J7" H 3280 5242 50  0000 L CNN
F 1 "3V-Coincell" H 3280 5151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3200 5250 50  0001 C CNN
F 3 "~" H 3200 5250 50  0001 C CNN
	1    3200 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 5250 3000 5250
Text Notes 2700 5600 0    50   ~ 0
VB: 1.8-3.6 V\n    max 2.2 µA
NoConn ~ 2750 5050
$Comp
L Connector_Generic:Conn_01x03 J10
U 1 1 5FDFDD40
P 2850 2000
F 0 "J10" H 2850 2200 50  0000 C CNN
F 1 "BY56W Voltage" H 2850 1800 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2850 2000 50  0001 C CNN
F 3 "~" H 2850 2000 50  0001 C CNN
	1    2850 2000
	1    0    0    -1  
$EndComp
Text Label 2650 2100 2    50   ~ 0
TXD2_5V
Text Label 2650 2000 2    50   ~ 0
GND
Text Label 2650 1900 2    50   ~ 0
RXD2_5V
$EndSCHEMATC
