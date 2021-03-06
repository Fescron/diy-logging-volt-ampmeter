EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 8268 11693 portrait
encoding utf-8
Sheet 1 1
Title "Wiring Diagram - DIY Logging Volt/Ampmeter"
Date "2021-12-12"
Rev "v1.1"
Comp "Brecht Van Eeckhoudt"
Comment1 "logger.brechtve.be"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 6050 950  0    50   Input ~ 0
V+
Text GLabel 6050 1100 0    50   Input ~ 0
V-
Text GLabel 4650 1500 2    50   Input ~ 0
VIN
Text GLabel 4650 1600 2    50   Input ~ 0
GND
Text GLabel 4650 950  2    50   Input ~ 0
TTL-TX
Text GLabel 4650 1050 2    50   Input ~ 0
GND
Text GLabel 4650 1150 2    50   Input ~ 0
TTL-RX
Text GLabel 4650 1350 2    50   Input ~ 0
RS232-5Vout
Text GLabel 6050 2000 0    50   Input ~ 0
I+
Text GLabel 6050 2150 0    50   Input ~ 0
I-
Text GLabel 4650 2550 2    50   Input ~ 0
VIN
Text GLabel 4650 2650 2    50   Input ~ 0
GND
Text GLabel 4650 2000 2    50   Input ~ 0
TTL-TX
Text GLabel 4650 2100 2    50   Input ~ 0
GND
Text GLabel 4650 2200 2    50   Input ~ 0
TTL-RX
Text GLabel 4650 2400 2    50   Input ~ 0
RS232-5Vout
Text Notes 5200 1200 0    50   ~ 10
BY56W 50V\nmeter
Text Notes 5200 2250 0    50   ~ 10
BY56W 5A\nmeter
$Comp
L Connector:Screw_Terminal_01x01 J?
U 1 1 61310EBF
P 7200 950
F 0 "J?" H 7280 992 50  0001 L CNN
F 1 "RED" H 7280 946 50  0000 L CNN
F 2 "" H 7200 950 50  0001 C CNN
F 3 "~" H 7200 950 50  0001 C CNN
	1    7200 950 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x01 J?
U 1 1 613113EA
P 7200 1100
F 0 "J?" H 7280 1142 50  0001 L CNN
F 1 "BLACK" H 7280 1096 50  0000 L CNN
F 2 "" H 7200 1100 50  0001 C CNN
F 3 "~" H 7200 1100 50  0001 C CNN
	1    7200 1100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x01 J?
U 1 1 6131181C
P 7200 2000
F 0 "J?" H 7280 2042 50  0001 L CNN
F 1 "YELLOW" H 7280 1996 50  0000 L CNN
F 2 "" H 7200 2000 50  0001 C CNN
F 3 "~" H 7200 2000 50  0001 C CNN
	1    7200 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x01 J?
U 1 1 61311D47
P 7200 2350
F 0 "J?" H 7280 2392 50  0001 L CNN
F 1 "BLUE" H 7280 2346 50  0000 L CNN
F 2 "" H 7200 2350 50  0001 C CNN
F 3 "~" H 7200 2350 50  0001 C CNN
	1    7200 2350
	1    0    0    -1  
$EndComp
$Comp
L Relay:DIPxx-1Cxx-51x K?
U 1 1 61315F21
P 6600 2550
F 0 "K?" H 7030 2596 50  0001 L CNN
F 1 "5V" V 6150 2550 50  0000 C CNN
F 2 "Relay_THT:Relay_StandexMeder_DIP_LowProfile" H 7050 2500 50  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_DIP.pdf" H 6600 2550 50  0001 C CNN
	1    6600 2550
	0    -1   -1   0   
$EndComp
$Comp
L Device:Fuse_Small F?
U 1 1 6131ACC4
P 6600 2000
F 0 "F?" H 6600 2185 50  0001 C CNN
F 1 "5A (5x10mm)" H 6600 2093 50  0000 C CNN
F 2 "" H 6600 2000 50  0001 C CNN
F 3 "~" H 6600 2000 50  0001 C CNN
	1    6600 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_PMOS_GSD Q?
U 1 1 6131B67A
P 1700 4300
F 0 "Q?" H 1905 4254 50  0001 L CNN
F 1 "PMOS" H 1550 4150 50  0000 L CNN
F 2 "" H 1900 4400 50  0001 C CNN
F 3 "~" H 1700 4300 50  0001 C CNN
	1    1700 4300
	1    0    0    1   
$EndComp
$Comp
L Switch:SW_SPDT SW?
U 1 1 6131CEB5
P 6700 4300
F 0 "SW?" H 6700 4585 50  0001 C CNN
F 1 "TOGGLE 50V" H 6700 4493 50  0000 C CNN
F 2 "" H 6700 4300 50  0001 C CNN
F 3 "~" H 6700 4300 50  0001 C CNN
	1    6700 4300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPDT_MSM SW?
U 1 1 6131EC45
P 3750 6450
F 0 "SW?" H 3750 6735 50  0001 C CNN
F 1 "TOGGLE UP/DOWN" H 4250 6450 50  0000 C CNN
F 2 "" H 3750 6450 50  0001 C CNN
F 3 "~" H 3750 6450 50  0001 C CNN
	1    3750 6450
	1    0    0    -1  
$EndComp
$Comp
L Converter_DCDC:OKI-78SR-3.3_1.5-W36-C U?
U 1 1 61325ABC
P 5850 3150
F 0 "U?" H 5850 3392 50  0001 C CNN
F 1 "DC/DC 5V out" H 5850 3301 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_muRata_OKI-78SR_Vertical" H 5900 2900 50  0001 L CIN
F 3 "https://power.murata.com/data/power/oki-78sr.pdf" H 5850 3150 50  0001 C CNN
	1    5850 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 950  7000 950 
Wire Wire Line
	6050 1100 7000 1100
Wire Wire Line
	6050 2000 6500 2000
Wire Wire Line
	6700 2000 7000 2000
Wire Wire Line
	6050 2150 6200 2150
Wire Wire Line
	6200 2150 6200 2450
Wire Wire Line
	6200 2450 6300 2450
Wire Wire Line
	6900 2350 7000 2350
$Comp
L Device:D_Small_ALT D?
U 1 1 6131A654
P 6600 3150
F 0 "D?" H 6600 3357 50  0001 C CNN
F 1 "1N4007" H 6600 3266 50  0000 C CNN
F 2 "" V 6600 3150 50  0001 C CNN
F 3 "~" V 6600 3150 50  0001 C CNN
	1    6600 3150
	1    0    0    1   
$EndComp
Wire Wire Line
	6700 3150 6950 3150
Wire Wire Line
	6950 3150 6950 2750
Wire Wire Line
	6950 2750 6900 2750
Wire Wire Line
	6300 2750 6250 2750
Wire Wire Line
	6250 2750 6250 3150
Wire Wire Line
	6500 3150 6250 3150
Wire Wire Line
	6150 3150 6250 3150
Connection ~ 6250 3150
Wire Wire Line
	5850 3450 5850 3500
Wire Wire Line
	5850 3500 6950 3500
Wire Wire Line
	6950 3500 6950 3150
Connection ~ 6950 3150
Connection ~ 5850 3500
$Comp
L Connector:USB_C_Receptacle_USB2.0 J?
U 1 1 61351EDE
P 1350 1500
F 0 "J?" H 1457 2367 50  0001 C CNN
F 1 "USB_C_Receptacle_USB2.0" H 1457 2275 50  0001 C CNN
F 2 "" H 1500 1500 50  0001 C CNN
F 3 "https://www.usb.org/sites/default/files/documents/usb_type-c.zip" H 1500 1500 50  0001 C CNN
	1    1350 1500
	1    0    0    -1  
$EndComp
Wire Notes Line width 12
	4650 850  6050 850 
Wire Notes Line width 12
	6050 850  6050 1700
Wire Notes Line width 12
	6050 1700 4650 1700
Wire Notes Line width 12
	4650 1700 4650 850 
Wire Notes Line width 12
	4650 1900 6050 1900
Wire Notes Line width 12
	6050 1900 6050 2750
Wire Notes Line width 12
	6050 2750 4650 2750
Wire Notes Line width 12
	4650 2750 4650 1900
$Comp
L Converter_DCDC:OKI-78SR-3.3_1.5-W36-C U?
U 1 1 6136A3A0
P 5550 6850
F 0 "U?" H 5550 7092 50  0001 C CNN
F 1 "DC/DC 3.3V out" H 5550 7001 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_muRata_OKI-78SR_Vertical" H 5600 6600 50  0001 L CIN
F 3 "https://power.murata.com/data/power/oki-78sr.pdf" H 5550 6850 50  0001 C CNN
	1    5550 6850
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 61319B09
P 1450 4150
F 0 "R?" H 1509 4196 50  0001 L CNN
F 1 "10 k??" H 1150 4150 50  0000 L CNN
F 2 "" H 1450 4150 50  0001 C CNN
F 3 "~" H 1450 4150 50  0001 C CNN
	1    1450 4150
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPDT SW?
U 1 1 6136D6E6
P 6700 6600
F 0 "SW?" H 6700 6885 50  0001 C CNN
F 1 "TOGGLE MCU" H 6700 6793 50  0000 C CNN
F 2 "" H 6700 6600 50  0001 C CNN
F 3 "~" H 6700 6600 50  0001 C CNN
	1    6700 6600
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPDT SW?
U 1 1 6136FA78
P 6700 8250
F 0 "SW?" H 6700 8535 50  0001 C CNN
F 1 "TOGGLE MCU" H 6700 8443 50  0001 C CNN
F 2 "" H 6700 8250 50  0001 C CNN
F 3 "~" H 6700 8250 50  0001 C CNN
	1    6700 8250
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPDT SW?
U 1 1 6136FE84
P 6700 7850
F 0 "SW?" H 6700 8135 50  0001 C CNN
F 1 "TOGGLE MCU" H 6700 8043 50  0001 C CNN
F 2 "" H 6700 7850 50  0001 C CNN
F 3 "~" H 6700 7850 50  0001 C CNN
	1    6700 7850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6137BC92
P 1300 4300
F 0 "R?" H 1359 4346 50  0001 L CNN
F 1 "100 ??" V 1200 4300 50  0000 C CNN
F 2 "" H 1300 4300 50  0001 C CNN
F 3 "~" H 1300 4300 50  0001 C CNN
	1    1300 4300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1500 4300 1450 4300
Wire Wire Line
	1450 4250 1450 4300
Connection ~ 1450 4300
Wire Wire Line
	1450 4300 1400 4300
Wire Wire Line
	1450 4050 1450 4000
Wire Wire Line
	1450 4000 1800 4000
Wire Wire Line
	1800 4000 1800 4100
$Comp
L Device:Battery_Cell BT?
U 1 1 61396A68
P 2450 3300
F 0 "BT?" H 2568 3396 50  0001 L CNN
F 1 "2x 18650 parallel" H 2568 3350 50  0000 L CNN
F 2 "" V 2450 3360 50  0001 C CNN
F 3 "~" V 2450 3360 50  0001 C CNN
	1    2450 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_Small_ALT D?
U 1 1 61398C08
P 1100 3050
F 0 "D?" H 1100 3285 50  0001 C CNN
F 1 "RED" V 1100 3300 50  0000 R CNN
F 2 "" V 1100 3050 50  0001 C CNN
F 3 "~" V 1100 3050 50  0001 C CNN
	1    1100 3050
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED_Small_ALT D?
U 1 1 6139910C
P 1100 3450
F 0 "D?" H 1100 3685 50  0001 C CNN
F 1 "GREEN" V 1100 3800 50  0000 R CNN
F 2 "" V 1100 3450 50  0001 C CNN
F 3 "~" V 1100 3450 50  0001 C CNN
	1    1100 3450
	0    -1   -1   0   
$EndComp
Text GLabel 2250 3050 0    50   Input ~ 0
B+
Text GLabel 2250 3450 0    50   Input ~ 0
B-
Wire Wire Line
	2450 3100 2450 3050
Wire Wire Line
	2450 3050 2250 3050
Wire Wire Line
	2450 3400 2450 3450
Wire Wire Line
	2450 3450 2250 3450
Text GLabel 1250 2900 2    50   Input ~ 0
CHRG+
Text GLabel 1250 3200 2    50   Input ~ 0
CHRG-
Text GLabel 1250 3300 2    50   Input ~ 0
DONE+
Text GLabel 1250 3600 2    50   Input ~ 0
DONE-
Text GLabel 1800 2800 3    50   Input ~ 0
VUSB
Text GLabel 2250 2900 0    50   Input ~ 0
V+
Text GLabel 2250 3600 0    50   Input ~ 0
V-
Wire Wire Line
	1250 2900 1100 2900
Wire Wire Line
	1100 2900 1100 2950
Wire Wire Line
	1250 3200 1100 3200
Wire Wire Line
	1100 3200 1100 3150
Wire Wire Line
	1250 3300 1100 3300
Wire Wire Line
	1100 3300 1100 3350
Wire Wire Line
	1100 3600 1100 3550
Wire Wire Line
	1100 3600 1250 3600
Wire Notes Line width 12
	1250 2800 2250 2800
Wire Notes Line width 12
	2250 2800 2250 3700
Wire Notes Line width 12
	2250 3700 1250 3700
Wire Notes Line width 12
	1250 3700 1250 2800
Text Notes 1650 3450 0    50   ~ 10
Battery \ncharging &\nprotection\nboard
Text GLabel 4650 4300 2    50   Input ~ 0
VBAT
Text GLabel 4650 4400 2    50   Input ~ 0
GND
$Comp
L Device:R_Small R?
U 1 1 613EF4A2
P 2100 1100
F 0 "R?" H 2159 1146 50  0001 L CNN
F 1 "5.1 k??" V 2200 1100 50  0000 C CNN
F 2 "" H 2100 1100 50  0001 C CNN
F 3 "~" H 2100 1100 50  0001 C CNN
	1    2100 1100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 613F0005
P 2100 1200
F 0 "R?" H 2159 1246 50  0001 L CNN
F 1 "5.1 k??" V 2000 1200 50  0000 C CNN
F 2 "" H 2100 1200 50  0001 C CNN
F 3 "~" H 2100 1200 50  0001 C CNN
	1    2100 1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1950 1100 2000 1100
Wire Wire Line
	1950 1200 2000 1200
Wire Wire Line
	2200 1100 2300 1100
Wire Wire Line
	2300 1100 2300 1150
Wire Wire Line
	2300 1200 2200 1200
Wire Wire Line
	1950 1400 2000 1400
Wire Wire Line
	2000 1400 2000 1450
Wire Wire Line
	2000 1500 1950 1500
Wire Wire Line
	1950 1600 2000 1600
Wire Wire Line
	2000 1600 2000 1650
Wire Wire Line
	2000 1700 1950 1700
NoConn ~ 1950 2000
NoConn ~ 1950 2100
NoConn ~ 1050 2400
Connection ~ 2000 1450
Wire Wire Line
	2000 1450 2000 1500
Connection ~ 2000 1650
Wire Wire Line
	2000 1650 2000 1700
Wire Wire Line
	1350 2400 1350 2450
$Comp
L Connector_Generic:Conn_01x06 J?
U 1 1 614284F4
P 4000 7100
F 0 "J?" H 4080 7092 50  0001 L CNN
F 1 "PROGRAMMING" H 3800 7400 50  0000 C CNN
F 2 "" H 4000 7100 50  0001 C CNN
F 3 "~" H 4000 7100 50  0001 C CNN
	1    4000 7100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 61429415
P 1250 6350
F 0 "J?" H 1330 6342 50  0001 L CNN
F 1 "GPIO" H 1200 6550 50  0000 C CNN
F 2 "" H 1250 6350 50  0001 C CNN
F 3 "~" H 1250 6350 50  0001 C CNN
	1    1250 6350
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J?
U 1 1 61429E01
P 950 7650
F 0 "J?" H 1030 7642 50  0001 L CNN
F 1 "OPENLOG" H 850 7950 50  0000 C CNN
F 2 "" H 950 7650 50  0001 C CNN
F 3 "~" H 950 7650 50  0001 C CNN
	1    950  7650
	-1   0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT?
U 1 1 6142C89A
P 3700 8050
F 0 "BT?" H 3818 8146 50  0001 L CNN
F 1 "Coincell" H 3800 8100 50  0000 L CNN
F 2 "" V 3700 8110 50  0001 C CNN
F 3 "~" V 3700 8110 50  0001 C CNN
	1    3700 8050
	1    0    0    -1  
$EndComp
Text GLabel 5900 4300 0    50   Input ~ 0
VSYS
Wire Wire Line
	5900 4300 6500 4300
Wire Wire Line
	5850 4600 6950 4600
Wire Wire Line
	6950 4600 6950 4400
Wire Wire Line
	6950 4400 6900 4400
NoConn ~ 6900 4200
$Comp
L Converter_DCDC:OKI-78SR-3.3_1.5-W36-C U?
U 1 1 613694F0
P 5550 4600
F 0 "U?" H 5550 4842 50  0001 C CNN
F 1 "DC/DC 5V out" H 5550 4751 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_muRata_OKI-78SR_Vertical" H 5600 4350 50  0001 L CIN
F 3 "https://power.murata.com/data/power/oki-78sr.pdf" H 5550 4600 50  0001 C CNN
	1    5550 4600
	-1   0    0    -1  
$EndComp
Text GLabel 5900 5100 0    50   Input ~ 0
5Vout-50V
Text GLabel 5900 5200 0    50   Input ~ 0
GND
$Comp
L Switch:SW_SPDT SW?
U 1 1 6149559D
P 6700 5450
F 0 "SW?" H 6700 5735 50  0001 C CNN
F 1 "TOGGLE 5A" H 6700 5643 50  0000 C CNN
F 2 "" H 6700 5450 50  0001 C CNN
F 3 "~" H 6700 5450 50  0001 C CNN
	1    6700 5450
	1    0    0    -1  
$EndComp
Text GLabel 5900 5450 0    50   Input ~ 0
VSYS
Wire Wire Line
	5900 5450 6500 5450
Wire Wire Line
	5850 5750 6950 5750
Wire Wire Line
	6950 5750 6950 5550
Wire Wire Line
	6950 5550 6900 5550
NoConn ~ 6900 5350
$Comp
L Converter_DCDC:OKI-78SR-3.3_1.5-W36-C U?
U 1 1 614955A9
P 5550 5750
F 0 "U?" H 5550 5992 50  0001 C CNN
F 1 "DC/DC 5V out" H 5550 5901 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_muRata_OKI-78SR_Vertical" H 5600 5500 50  0001 L CIN
F 3 "https://power.murata.com/data/power/oki-78sr.pdf" H 5550 5750 50  0001 C CNN
	1    5550 5750
	-1   0    0    -1  
$EndComp
Text GLabel 5900 6250 0    50   Input ~ 0
5Vout-5A
Text GLabel 5900 6350 0    50   Input ~ 0
GND
Text GLabel 5200 4600 0    50   Input ~ 0
5Vout-50V
Text GLabel 5000 4950 0    50   Input ~ 0
GND
Text GLabel 5000 6100 0    50   Input ~ 0
GND
Text GLabel 5200 5750 0    50   Input ~ 0
5Vout-5A
Wire Wire Line
	5550 6050 5550 6100
Wire Wire Line
	5550 6100 5250 6100
Wire Wire Line
	5200 5750 5250 5750
Wire Wire Line
	5200 4600 5250 4600
Wire Wire Line
	5550 4900 5550 4950
Wire Wire Line
	5550 4950 5250 4950
Text GLabel 5900 6600 0    50   Input ~ 0
VSYS
NoConn ~ 6900 6500
NoConn ~ 6900 7750
NoConn ~ 6900 8150
Wire Wire Line
	5900 6600 6500 6600
Wire Wire Line
	6900 6700 6950 6700
Wire Wire Line
	6950 6700 6950 6850
Wire Wire Line
	6950 6850 5850 6850
Wire Wire Line
	5900 5100 6350 5100
Wire Wire Line
	5900 5200 6350 5200
Wire Wire Line
	5900 6250 6350 6250
Wire Wire Line
	5900 6350 6350 6350
Text Label 6350 5100 2    50   ~ 0
50V-VIN
Text Label 6350 5200 2    50   ~ 0
50V-GND2
Text Label 6350 6250 2    50   ~ 0
5A-VIN
Text Label 6350 6350 2    50   ~ 0
5A-GND2
Wire Wire Line
	4650 1500 4200 1500
Wire Wire Line
	4650 1600 4200 1600
Text Label 4200 1500 0    50   ~ 0
50V-VIN
Text Label 4200 1600 0    50   ~ 0
50V-GND2
Wire Wire Line
	4650 2650 4200 2650
Wire Wire Line
	4650 2550 4200 2550
Text Label 4200 2550 0    50   ~ 0
5A-VIN
Text Label 4200 2650 0    50   ~ 0
5A-GND2
Text GLabel 5000 7200 0    50   Input ~ 0
GND
Text GLabel 5200 6850 0    50   Input ~ 0
3V3out-MCU
Text GLabel 5900 7350 0    50   Input ~ 0
3V3out-MCU
Text GLabel 5900 7450 0    50   Input ~ 0
GND
Wire Wire Line
	5900 7350 6350 7350
Wire Wire Line
	5900 7450 6350 7450
Wire Wire Line
	5550 7150 5550 7200
Wire Wire Line
	5550 7200 5250 7200
Wire Wire Line
	5250 6850 5200 6850
Text GLabel 5900 7650 0    50   Input ~ 0
VBAT
Wire Notes Line
	6700 6500 6700 8300
Wire Wire Line
	5900 7650 6350 7650
Text Notes 4850 6550 0    50   ~ 10
Power\nconversion\nboard
Text Label 6350 7350 2    50   ~ 0
MCU-VIN
Text Label 6350 7450 2    50   ~ 0
MCU-GND
Text Label 6350 7650 2    50   ~ 0
MCU-VBAT
Wire Notes Line width 12
	4650 4200 5900 4200
Wire Notes Line width 12
	5900 4200 5900 8650
Wire Notes Line width 12
	5900 8650 4650 8650
Wire Notes Line width 12
	4650 8650 4650 4200
Wire Wire Line
	4650 1350 4200 1350
Wire Wire Line
	4650 1150 4200 1150
Wire Wire Line
	4650 1050 4200 1050
Wire Wire Line
	4650 950  4200 950 
Wire Wire Line
	4650 2000 4200 2000
Wire Wire Line
	4650 2100 4200 2100
Wire Wire Line
	4650 2200 4200 2200
Wire Wire Line
	4650 2400 4200 2400
Text Label 4200 1350 0    50   ~ 0
50V-5Vout
Text Label 4200 2400 0    50   ~ 0
5A-5Vout
Wire Wire Line
	6500 7850 6050 7850
Text Label 6050 7850 0    50   ~ 0
50V-5Vout
Wire Wire Line
	6500 8250 6050 8250
Text Label 6050 8250 0    50   ~ 0
5A-5Vout
Wire Wire Line
	6900 7950 7500 7950
Wire Wire Line
	6900 8350 7500 8350
Text Label 4200 950  0    50   ~ 0
50V-TX
Text Label 4200 1050 0    50   ~ 0
50V-GND1
Text Label 4200 1150 0    50   ~ 0
50V-RX
Text Label 4200 2000 0    50   ~ 0
5A-TX
Text Label 4200 2100 0    50   ~ 0
5A-GND1
Text Label 4200 2200 0    50   ~ 0
5A-RX
Wire Wire Line
	2250 2900 2700 2900
Text Label 2700 2900 2    50   ~ 0
BATTout+
Wire Wire Line
	2250 3600 2700 3600
Text Label 2700 3600 2    50   ~ 0
BATTout-
Wire Wire Line
	4650 4300 4200 4300
Text Label 4200 4300 0    50   ~ 0
BATTout+
Wire Wire Line
	4650 4400 4200 4400
Text Label 4200 4400 0    50   ~ 0
BATTout-
Text Label 7500 7950 2    50   ~ 0
50V-5Vout-MCU
Text Label 7500 8350 2    50   ~ 0
5A-5Vout-MCU
Wire Wire Line
	5550 3150 5100 3150
Text Label 5100 3150 0    50   ~ 0
VRELAY
Wire Wire Line
	5100 3500 5850 3500
Text Label 5100 3500 0    50   ~ 0
RELAY-GND-SW
Wire Wire Line
	1800 2800 1800 2700
Wire Wire Line
	1800 2700 2250 2700
Text Label 2250 2700 2    50   ~ 0
VUSB-CHR
Text GLabel 1400 6750 0    50   Input ~ 0
3V3
Text GLabel 1400 6850 0    50   Input ~ 0
KEY
Text GLabel 1400 6950 0    50   Input ~ 0
S2
Text GLabel 1400 7050 0    50   Input ~ 0
S1
Text GLabel 1400 7150 0    50   Input ~ 0
GND
Wire Notes Line
	1400 6650 1400 7250
Wire Notes Line
	1400 7250 850  7250
Wire Notes Line
	850  7250 850  6650
Wire Notes Line
	850  6650 1400 6650
Text Notes 900  7000 0    50   ~ 10
Rotary\nencoder
Wire Notes Line width 12
	900  650  2450 650 
Wire Notes Line width 12
	2450 650  2450 2500
Wire Notes Line width 12
	2450 2500 900  2500
Wire Notes Line width 12
	900  2500 900  650 
Text Notes 1300 750  0    50   ~ 10
USB Type C Breakout
Wire Wire Line
	1950 900  2900 900 
Wire Wire Line
	2000 1450 2900 1450
Wire Wire Line
	2000 1650 2900 1650
Wire Wire Line
	1350 2450 2350 2450
Wire Wire Line
	2300 1150 2350 1150
Wire Wire Line
	2350 1150 2350 2450
Connection ~ 2300 1150
Wire Wire Line
	2300 1150 2300 1200
Connection ~ 2350 2450
Wire Wire Line
	2350 2450 2900 2450
Text Label 2900 900  2    50   ~ 0
VUSB
Text Label 2900 1450 2    50   ~ 0
USB-D-
Text Label 2900 1650 2    50   ~ 0
USB-D+
Text Label 2900 2450 2    50   ~ 0
USB-GND
Text Notes 6250 2750 0    50   ~ 0
+
Text Notes 6900 2750 0    50   ~ 0
-
Text GLabel 1650 5250 2    50   Input ~ 0
GND
Text GLabel 1650 5350 2    50   Input ~ 0
3V3
Text GLabel 1650 5450 2    50   Input ~ 0
VBAT
Text GLabel 1650 5550 2    50   Input ~ 0
VUSB
Text Notes 1900 5300 0    50   ~ 0
1
Text Notes 1900 5400 0    50   ~ 0
2
Text Notes 1900 5500 0    50   ~ 0
3
Text Notes 1900 5600 0    50   ~ 0
4
Wire Wire Line
	1650 5250 1200 5250
Text Label 1200 5250 0    50   ~ 0
MCU-GND
Wire Wire Line
	1650 5350 1200 5350
Text Label 1200 5350 0    50   ~ 0
MCU-VIN
Wire Wire Line
	1650 5450 1200 5450
Text Label 1200 5450 0    50   ~ 0
MCU-VBAT
Wire Wire Line
	1650 5550 1200 5550
Text Label 1200 5550 0    50   ~ 0
VUSB-POW
Text GLabel 1650 5750 2    50   Input ~ 0
VUSB
Text GLabel 1650 5850 2    50   Input ~ 0
D+_PA12
Text GLabel 1650 5950 2    50   Input ~ 0
D-_PA11
Text GLabel 1650 6050 2    50   Input ~ 0
GND
Text Notes 2050 5800 0    50   ~ 0
1
Text Notes 2050 5900 0    50   ~ 0
2
Text Notes 2050 6000 0    50   ~ 0
3
Text Notes 2050 6100 0    50   ~ 0
4
Wire Wire Line
	1650 5750 1200 5750
Wire Wire Line
	1650 5850 1200 5850
Wire Wire Line
	1650 5950 1200 5950
Wire Wire Line
	1650 6050 1200 6050
Text Label 1200 5750 0    50   ~ 0
VUSB
Text Label 1200 5950 0    50   ~ 0
USB-D-
Text Label 1200 5850 0    50   ~ 0
USB-D+
Text Label 1200 6050 0    50   ~ 0
USB-GND
Text GLabel 1650 6350 2    50   Input ~ 0
GPIO2_PA5
Text GLabel 1650 6450 2    50   Input ~ 0
GND
Text GLabel 1650 6550 2    50   Input ~ 0
3V3
Text Notes 1900 6500 0    50   ~ 0
3
Text Notes 1900 6600 0    50   ~ 0
4
Text Notes 2050 6500 0    50   ~ 0
J11
Text Notes 2200 6300 0    50   ~ 10
3
Text Notes 2200 6400 0    50   ~ 10
4
Wire Wire Line
	1450 6250 1650 6250
Wire Wire Line
	1450 6350 1650 6350
Wire Wire Line
	1450 6450 1650 6450
Wire Wire Line
	1450 6550 1650 6550
Text GLabel 1650 6750 2    50   Input ~ 0
3V3
Text GLabel 1650 7150 2    50   Input ~ 0
GND
Wire Bus Line
	2000 5200 2000 5600
Wire Bus Line
	2150 5700 2150 6100
Wire Bus Line
	2300 6200 2300 6400
Wire Bus Line
	2000 6400 2000 6600
Text GLabel 1650 6850 2    50   Input ~ 0
KEY_PB5
Text GLabel 1650 6950 2    50   Input ~ 0
S2_PA6
Text GLabel 1650 7050 2    50   Input ~ 0
S1_PA7
Text Notes 2100 6900 0    50   ~ 0
2
Text Notes 2100 6800 0    50   ~ 0
1
Text Notes 2100 7200 0    50   ~ 0
5
Wire Bus Line
	2200 6700 2200 6900
Wire Bus Line
	2200 7100 2200 7200
Text Notes 2000 7000 0    50   ~ 10
1
Text Notes 2000 7100 0    50   ~ 10
2
Wire Bus Line
	2100 6900 2100 7100
Wire Wire Line
	1400 6750 1650 6750
Wire Wire Line
	1650 6850 1400 6850
Wire Wire Line
	1400 6950 1650 6950
Wire Wire Line
	1650 7050 1400 7050
Wire Wire Line
	1650 7150 1400 7150
Text GLabel 1650 6250 2    50   Input ~ 0
GPIO1_PC13
Text GLabel 1650 7450 2    50   Input ~ 0
DTR_PB9
Text GLabel 1650 7550 2    50   Input ~ 0
TXD1_PA9
Text GLabel 1650 7650 2    50   Input ~ 0
RXD1_PA10
Text GLabel 1650 7850 2    50   Input ~ 0
GND
Text GLabel 1650 7950 2    50   Input ~ 0
GND
Text GLabel 1650 7750 2    50   Input ~ 0
UART1_3V3
Wire Wire Line
	1650 7750 1600 7750
NoConn ~ 1600 7750
Text Notes 2100 4400 0    50   ~ 10
! Wrong MOSFET circuit on PCB v1.0\n  so UART1-ENout/PB8 is unused !\n! Added bodge-PCB and used PB14 instead !
Text Notes 2150 7500 0    50   ~ 0
1
Text Notes 2150 7600 0    50   ~ 0
2
Text Notes 2150 7700 0    50   ~ 0
3
Text Notes 2150 7800 0    50   ~ 0
4
Text Notes 2150 7900 0    50   ~ 0
5
Text Notes 2150 8000 0    50   ~ 0
6
Wire Bus Line
	2250 7400 2250 8000
Text Notes 850  7450 2    50   ~ 0
~RST
Text Notes 850  7850 2    50   ~ 0
CTS
Wire Wire Line
	1150 7450 1650 7450
Wire Wire Line
	1650 7550 1150 7550
Wire Wire Line
	1650 7650 1150 7650
Wire Wire Line
	1150 7850 1650 7850
Wire Wire Line
	1150 7950 1650 7950
Wire Wire Line
	1150 7750 1450 7750
Text Label 1450 7750 2    50   ~ 0
LOG_3V3
Wire Wire Line
	1800 4500 1800 4600
Wire Wire Line
	1800 4600 2400 4600
Text Label 2400 4600 2    50   ~ 0
LOG_3V3
Text GLabel 1650 8150 2    50   Input ~ 0
3V3
Text GLabel 1650 8250 2    50   Input ~ 0
PB14
Wire Wire Line
	1800 4000 2400 4000
Connection ~ 1800 4000
Wire Wire Line
	1200 4300 1150 4300
Wire Wire Line
	1150 4300 1150 4700
Wire Wire Line
	1150 4700 2400 4700
Wire Wire Line
	1650 8150 1200 8150
Wire Wire Line
	1650 8250 1200 8250
Text Label 1200 8150 0    50   ~ 0
BODGE_3V3
Text Label 1200 8250 0    50   ~ 0
BODGE_GND
Text Label 2400 4000 2    50   ~ 0
BODGE_3V3
Text Label 2400 4700 2    50   ~ 0
BODGE_GND
Text Notes 1450 4650 0    50   ~ 10
PMOS\nbodge\nPCB
Text GLabel 3450 5250 0    50   Input ~ 0
5Vin-50V
Text GLabel 3450 5800 0    50   Input ~ 0
5Vin-5A
Wire Wire Line
	3450 5250 4100 5250
Wire Wire Line
	3450 5800 4100 5800
Text Label 4100 5250 2    50   ~ 0
50V-5Vout-MCU
Text Label 4100 5800 2    50   ~ 0
5A-5Vout-MCU
Text Notes 2950 5300 0    50   ~ 0
1
Text Notes 3000 5850 0    50   ~ 0
1
Wire Bus Line
	2900 5200 2900 5300
Wire Bus Line
	2950 5750 2950 5850
Text Notes 2300 7500 0    50   ~ 0
J14
Text Notes 2250 7200 0    50   ~ 0
J9
Text Notes 2150 7000 0    50   ~ 10
J11
Text Notes 2250 6800 0    50   ~ 0
J9
Text Notes 2350 6300 0    50   ~ 10
J9
Text Notes 2200 5800 0    50   ~ 0
J5
Text GLabel 3450 5400 0    50   Input ~ 0
RXD2_PA3
Text GLabel 3450 5500 0    50   Input ~ 0
GND
Text GLabel 3450 5600 0    50   Input ~ 0
TXD2_PA2
Text Notes 2950 5450 0    50   ~ 0
1
Text Notes 2950 5550 0    50   ~ 0
2
Text Notes 2950 5650 0    50   ~ 0
3
Wire Bus Line
	2900 5350 2900 5650
Wire Wire Line
	3450 5600 4100 5600
Wire Wire Line
	3450 5500 4100 5500
Wire Wire Line
	3450 5400 4100 5400
Text Label 4100 5400 2    50   ~ 0
50V-TX
Text Label 4100 5500 2    50   ~ 0
50V-GND1
Text Label 4100 5600 2    50   ~ 0
50V-RX
Text GLabel 3450 5950 0    50   Input ~ 0
RXD3_PB11
Text GLabel 3450 6050 0    50   Input ~ 0
GND
Text GLabel 3450 6150 0    50   Input ~ 0
TXD3_PB10
Text Notes 2900 6000 0    50   ~ 0
1
Text Notes 2900 6100 0    50   ~ 0
2
Text Notes 2900 6200 0    50   ~ 0
3
Wire Bus Line
	2850 5900 2850 6200
Wire Wire Line
	3450 6150 4100 6150
Wire Wire Line
	3450 6050 4100 6050
Wire Wire Line
	3450 5950 4100 5950
Text Label 4100 5950 2    50   ~ 0
5A-TX
Text Label 4100 6050 2    50   ~ 0
5A-GND1
Text Label 4100 6150 2    50   ~ 0
5A-RX
Text GLabel 3450 6350 0    50   Input ~ 0
SW0_PA0
Text GLabel 3450 6450 0    50   Input ~ 0
GND-1k??
Text GLabel 3450 6550 0    50   Input ~ 0
SW1_PA1
Text Notes 2950 6400 0    50   ~ 0
1
Text Notes 2950 6500 0    50   ~ 0
2
Text Notes 2950 6600 0    50   ~ 0
3
Wire Bus Line
	2900 6300 2900 6600
Text Notes 2050 5300 0    50   ~ 0
J3
Text Notes 2750 5300 0    50   ~ 0
J1
Text Notes 2700 5450 0    50   ~ 0
J10
Text Notes 2700 6000 0    50   ~ 0
J4
Text Notes 2800 5850 0    50   ~ 0
J8
Text Notes 2700 6400 0    50   ~ 0
J13
Wire Wire Line
	3550 6450 3450 6450
Wire Wire Line
	3950 6350 4000 6350
Wire Wire Line
	4000 6350 4000 6250
Wire Wire Line
	4000 6250 3550 6250
Wire Wire Line
	3550 6250 3550 6350
Wire Wire Line
	3550 6350 3450 6350
Wire Wire Line
	3950 6550 4000 6550
Wire Wire Line
	4000 6550 4000 6650
Wire Wire Line
	4000 6650 3550 6650
Wire Wire Line
	3550 6650 3550 6550
Wire Wire Line
	3550 6550 3450 6550
Text Notes 4000 6550 0    50   ~ 0
monostable
Text GLabel 3450 6900 0    50   Input ~ 0
SWO_PB3
Text GLabel 3450 7000 0    50   Input ~ 0
RESET
Text GLabel 3450 7100 0    50   Input ~ 0
3V3
Text GLabel 3450 7200 0    50   Input ~ 0
GND
Text GLabel 3450 7300 0    50   Input ~ 0
SWCLK
Text GLabel 3450 7400 0    50   Input ~ 0
SWDIO
Text Notes 3000 6950 0    50   ~ 0
1
Text Notes 3100 7050 0    50   ~ 0
1
Text Notes 2750 6950 0    50   ~ 0
J24
Text Notes 2900 7050 0    50   ~ 0
J6
Wire Bus Line
	3050 6950 3050 7050
Wire Bus Line
	2950 6850 2950 6950
Wire Wire Line
	3450 6900 3800 6900
Wire Wire Line
	3450 7000 3800 7000
Wire Wire Line
	3450 7100 3800 7100
Wire Wire Line
	3450 7200 3800 7200
Wire Wire Line
	3450 7300 3800 7300
Wire Wire Line
	3450 7400 3800 7400
Text GLabel 3450 7600 0    50   Input ~ 0
RELAY+_3V3
Text GLabel 3450 7700 0    50   Input ~ 0
RELAY-_PA8
Wire Wire Line
	3450 7700 4100 7700
Text Label 4100 7700 2    50   ~ 0
RELAY-GND-SW
Text Notes 2850 7650 0    50   ~ 0
1
Text Notes 2850 7750 0    50   ~ 0
2
Text Notes 2600 7650 0    50   ~ 0
J12
Wire Bus Line
	2800 7550 2800 7750
Text GLabel 3450 7950 0    50   Input ~ 0
VB
Text GLabel 3450 8050 0    50   Input ~ 0
GND
Text Notes 3150 8100 0    50   ~ 0
2
Text Notes 3150 8000 0    50   ~ 0
1
Wire Bus Line
	3100 7900 3100 8100
Text Notes 2950 8000 0    50   ~ 0
J7
Wire Wire Line
	3700 7850 3700 7800
Wire Wire Line
	3700 7800 3550 7800
Wire Wire Line
	3550 7800 3550 7950
Wire Wire Line
	3550 7950 3450 7950
Wire Wire Line
	3700 8150 3700 8200
Wire Wire Line
	3700 8200 3550 8200
Wire Wire Line
	3550 8200 3550 8050
Wire Wire Line
	3550 8050 3450 8050
Text GLabel 2500 8150 0    50   Input ~ 0
PB13
Text GLabel 2500 8250 0    50   Input ~ 0
PB2
Wire Wire Line
	2500 8150 2800 8150
Wire Wire Line
	2500 8250 2800 8250
Text Label 2800 8150 2    50   ~ 0
Buzzer
Text Label 2800 8250 2    50   ~ 0
LED
Text Notes 2050 5150 0    50   ~ 10
STM32F103C8T6 board
Wire Notes Line width 12
	1650 5000 3450 5000
Wire Notes Line width 12
	3450 5000 3450 8350
Wire Notes Line width 12
	3450 8350 1650 8350
Wire Notes Line width 12
	1650 8350 1650 5000
Wire Notes Line width 12
	1950 4800 1050 4800
Wire Notes Line width 12
	1950 3900 1950 4800
Wire Notes Line width 12
	1050 4800 1050 3900
Wire Notes Line width 12
	1050 3900 1950 3900
Text Notes 1700 8500 0    50   ~ 10
! Swapped pins on J9 and J11 (bold text) !
$Comp
L Device:Q_PMOS_GSD Q?
U 1 1 61B61237
P 5200 8000
F 0 "Q?" H 5405 7954 50  0001 L CNN
F 1 "PMOS" V 5100 7850 50  0000 C CNN
F 2 "" H 5400 8100 50  0001 C CNN
F 3 "~" H 5200 8000 50  0001 C CNN
	1    5200 8000
	0    -1   -1   0   
$EndComp
Text GLabel 4950 8200 0    50   Input ~ 0
GND
$Comp
L Device:D_Schottky_Small_ALT D?
U 1 1 61BB67C4
P 5350 8450
F 0 "D?" H 5350 8243 50  0001 C CNN
F 1 "Schottky" H 5350 8550 50  0000 C CNN
F 2 "" V 5350 8450 50  0001 C CNN
F 3 "~" V 5350 8450 50  0001 C CNN
	1    5350 8450
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 61B80E5B
P 5050 8200
F 0 "R?" H 5109 8246 50  0001 L CNN
F 1 "100 k??" V 5150 8200 50  0000 C CNN
F 2 "" H 5050 8200 50  0001 C CNN
F 3 "~" H 5050 8200 50  0001 C CNN
	1    5050 8200
	0    1    1    0   
$EndComp
Text GLabel 4950 8450 0    50   Input ~ 0
VUSB
Wire Wire Line
	5150 8200 5200 8200
Wire Wire Line
	5200 8200 5200 8450
Wire Wire Line
	4950 8450 5200 8450
Connection ~ 5200 8200
Wire Wire Line
	5200 8450 5250 8450
Connection ~ 5200 8450
Wire Wire Line
	5450 8450 5500 8450
Wire Wire Line
	5500 8450 5500 7900
Wire Wire Line
	5500 7900 5400 7900
Wire Wire Line
	5500 7900 5600 7900
Connection ~ 5500 7900
Text GLabel 5600 7900 2    50   Input ~ 0
VSYS
Text GLabel 4650 5100 2    50   Input ~ 0
VUSB
Text GLabel 4650 5200 2    50   Input ~ 0
VUSB
Wire Wire Line
	4650 5100 4200 5100
Wire Wire Line
	4650 5200 4200 5200
Text Label 4200 5100 0    50   ~ 0
VUSB-POW
Text Label 4200 5200 0    50   ~ 0
VUSB-CHR
Text GLabel 4650 5400 2    50   Input ~ 0
VSYS
Wire Wire Line
	4650 5400 4200 5400
Text Label 4200 5400 0    50   ~ 0
VRELAY
NoConn ~ 3450 7600
Wire Wire Line
	4950 7900 5000 7900
Text GLabel 4950 7900 0    50   Input ~ 0
VBAT
Text Notes 4750 7750 0    50   ~ 0
Power Path
$Comp
L Device:C_Small C?
U 1 1 61B7C1D1
P 5250 5900
F 0 "C?" H 5342 5946 50  0001 L CNN
F 1 "10 ??F" H 5150 5900 50  0000 R CNN
F 2 "" H 5250 5900 50  0001 C CNN
F 3 "~" H 5250 5900 50  0001 C CNN
	1    5250 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5750 5250 5800
Connection ~ 5250 5750
Wire Wire Line
	5250 6000 5250 6100
Connection ~ 5250 6100
Wire Wire Line
	5250 6100 5000 6100
$Comp
L Device:C_Small C?
U 1 1 61BBCD4B
P 5250 7000
F 0 "C?" H 5342 7046 50  0001 L CNN
F 1 "10 ??F" H 5150 7000 50  0000 R CNN
F 2 "" H 5250 7000 50  0001 C CNN
F 3 "~" H 5250 7000 50  0001 C CNN
	1    5250 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 6850 5250 6900
Connection ~ 5250 6850
Wire Wire Line
	5250 7100 5250 7200
Connection ~ 5250 7200
Wire Wire Line
	5250 7200 5000 7200
$Comp
L Device:C_Small C?
U 1 1 61C19816
P 5250 4750
F 0 "C?" H 5342 4796 50  0001 L CNN
F 1 "10 ??F" H 5150 4750 50  0000 R CNN
F 2 "" H 5250 4750 50  0001 C CNN
F 3 "~" H 5250 4750 50  0001 C CNN
	1    5250 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4600 5250 4650
Connection ~ 5250 4600
Wire Wire Line
	5250 4850 5250 4950
Connection ~ 5250 4950
Wire Wire Line
	5250 4950 5000 4950
$EndSCHEMATC
