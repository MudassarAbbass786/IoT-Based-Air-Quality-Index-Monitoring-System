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
*******************************************************************DHT11(Temperature & Humidity)*********************************************************************************
The Circuit Diagram Has Been Given In The Above Section With Filename “Wemosd1_DHT11_Schematic”. The Arduino Code Also Has Been Given With Filename “Runable_DHT11_Thinkspeak”. The Results Are Also Shown On The ThingSpeak Platform With Filename “DHT11_Results”.
WeMos Code In Arduino IDE:

#include <ESP8266WiFi.h>         // This library provides ESP8266 specific Wi-Fi routines that we are calling to connect to the network.
#include "DHTesp.h"              // Through this liberary,we can have access to the functionalities needed to get temperature measurements
DHTesp dht;                      // Global Variable


String apiWritekey = "OGM5SBZRG4N2EV0Y";   // Api key is used to write your sensor vlaues onto the thingspeak channel
const char* ssid = "Malik";           // the name of the WiFi network you want to connect to
const char* password = "12345678" ;       // password of router

const char* server = "api.thingspeak.com";  // this is the thingspeak address  
float resolution=3.3/1023;                  // 3.3 is the supply volt  & 1023 is max analog read value 
WiFiClient client;                          // client that will be contacting the host (server)

void setup() {
  Serial.begin(115200);                   // Sets the data rate in bits per second (baud) for serial data transmission
  WiFi.disconnect();                      // Temperarely Disconnects the WiFi shield from the current network.
  delay(10);                              // 0.01s delay
  WiFi.begin(ssid, password);             // Initializes the WiFi library's network settings and provides the current status.
  Serial.println();                       // Prints data to the serial port as human-readable ASCII text
  Serial.println();
  Serial.print("Connecting to ");       
  Serial.println(ssid);           
  WiFi.begin(ssid, password);
  dht.setup(D5, DHTesp::DHT11);           // for DHT11 Connect DHT sensor to D5
    while (WiFi.status() != WL_CONNECTED) // The while() loop will keep looping as long as WiFi.status() is other than WL_CONNECTED (connection to router). The loop will exit only if the status changes to WL_CONNECTED.
    {
    delay(500);
    Serial.print(".");
  
    }}

void loop() {
    
  float h = dht.getHumidity();           // read humidity values from sensor
  float t = dht.getTemperature();        // read temperature values from sensor
  if (client.connect(server,80))         // Connects to a specified IP address and port. The return value indicates success or failure. "184.106.153.149" or api.thingspeak.com
  {
    String tsData = apiWritekey;         // store API write key in variable tsData
    tsData +="&field1=";                 // upload data into field 1 
    tsData += String(t);                 // upload temperature values into field 1
    tsData +="&field3=";                 // upload data into field 3 
    tsData += String(h);                 // upload humidity values into field 3
    tsData += "\r\n\r\n";                // \n is a newline and \r is a carriage return (i.e. move the cursor to the left)

    

    client.print("POST /update HTTP/1.1\n");      // client command for thigspeak
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    
    client.print(tsData.length());  // check the length of API key
    client.print("\n\n");
    client.print(tsData);
    
    Serial.print("{\"Humidity\": ");   // print the humidity values to serial monitor
    Serial.print(h);
    Serial.print("\"Temperature\": "); //  // print the Temperature values to serial monitor
    Serial.print(t);
    Serial.print("}\n");
    delay(1000);                      // delay of 1 second
    Serial.println("uploaded to Thingspeak server....");  // print "uploaded to Thingspeak server...." at serial monitor
  }
  
 

  Serial.println("Waiting to upload next reading...");   // print "Waiting to upload next reading..." at serial monitor
  Serial.println();
  delay(15000);                                         // delay for next reading
}

No.2:
*******************************************************************DHT11(Temperature & Humidity)*********************************************************************************

 

