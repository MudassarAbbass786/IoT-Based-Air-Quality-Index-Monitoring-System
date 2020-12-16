# IoT-Based-Air-Quality-Index-Monitoring-System
Since better air quality is very much important for healthy environment. Therefore, to control the air pollution an accurate monitoring of the air quality is very much important. So, a good air quality monitoring system can help us to aware the public as well as can give recommendations to the policy makers to provide guidelines to industrialists and to the public. The proposed project “Real Time IoT Based Air Quality Monitoring System” is just about the analysis of air quality on the basis of the data acquired by the help of different gas, particulate matter, humidity and temperature sensors. The sensors will be interfaced with the microcontroller to achieve the data of some dangerous air pollutants like Carbon Monoxide(CO), Carbon Dioxide(CO2), Nitrogen Dioxide(NO2), Sulphur Dioxide(SO2) and Particulate Matter(PM) along with Humidity and Temperature in the air.The proposed project aims to collect data through various sensors, process the data using Arduino based microcontroller (Arduino MKR WAN 1310), then acquired information is transmitted to IoT enabled ThingSpeak Cloud via LoRaWAN protocol. In the cloud, the data is processed to provide information of the overall air quality in terms of the concentration of the impurities and the humidity along with temperature. Finally, air quality information is shared and analysed on smartphone/web using IoT based ThingSpeak platform. The system acquires data through Gas sensors (MG811, MQ-7, 2SH12, MICS-6814), Temperature and Humidity sensor (SHT11 or DHT22) and also the sensor (SDS011 or PMS5003) can be used to detect the particulate matter PM1.0, PM2.5, PM10 (the complex mixture includes both organic and inorganic particles, such as dust, pollen, soot, smoke, and liquid droplets in air). The overall focus of the project will be to identify and to evaluate the real time accurate saturation of these major pollutants present in the atmosphere.
The proposed system would focus on the following harmful pollutants emitted into the atmosphere by different activities are:
1. Carbon Monoxide (MQ-7)
2. Carbon dioxide (MG811 Sensor Module)
3. Sulphur Dioxide (2SH12 Sensor Module)
4. Nitrogen Dioxide (MICS-6814)
5. NH3 Gas Sensor Module (MQ137)
6. Ozone Gas Sensor MQ131
7. Air Quality Sensor MQ2
8. Particulate Matter (SDS011 or PMS5003 or DSM501A)
Along with:
9. Temperature (SHT11 or DHT22)
10. Humidity (SHT11 or DHT22)

..........................................................................Work Done Till Now.....................................................................................

Following Are The  Sensors That Has Been Interfaced With Arduino/WeMOS Ssuccessfully Up Till Now To Collect The Data From The Environment For Further Analysis:

No.1:
************************************************************** DHT11(Temperature & Humidity Sensor) *****************************************************************************

The Circuit Diagram Has Been Given In The Above Section With Filename “Wemosd1_DHT11_Schematic”.
The Hardware Demo Has Been Given In The Above Section With Filename “HardwareDHT11”.
The Arduino Code Also Has Been Given With Filename “Runable_DHT11_Thinkspeak”.
The Results Are Also Shown On The ThingSpeak Platform With Filename “DHT11_Results”.

No.2:
****************************************************************** MQ-7( Carbon Monoxide) ***************************************************************************************

The Circuit Diagram Has Been Given In The Above Section With Filename “CircuitDiagramMQ7”.
The Hardware Demo Has Been Given In The Above Section With Filename “HardwareMQ7”.
The Arduino Code Also Has Been Given With Filename “MQ7Code”.
The Results Are Also Shown On The Serial Monitor With Filename “ResultsMQ7”.

No.3:
****************************************************************** DSM501A( PM1.0 & PM2.5) **************************************************************************************

The Circuit Diagram Has Been Given In The Above Section With Filename “CircuitDiagramDSM501A”.
The Hardware Demo Has Been Given In The Above Section With Filename “HardwareDSM501A”.
The Arduino Code Also Has Been Given With Filename “DSM501ACode”.
The Results Are Also Shown On The Serial Monitor With Filename “ResultsDSM501A”.




