#include "WiFi.h"  // This library provides ESP8266 specific Wi-Fi routines that we are calling to connect to the network.
#include <Adafruit_Sensor.h>
#include "DHT.h"             // Through this liberary,we can have access to the functionalities needed to get temperature measurements
#include <MQ7.h>
#include<DSM501.h>
int a;
#define DHTTYPE DHT11
#define DSM501_PM10 26
#define DSM501_PM25 25

DSM501 dsm501(DSM501_PM10, DSM501_PM25);

#define A_PIN 33
#define VOLTAGE 5

// init MQ7 device
MQ7 mq7(A_PIN, VOLTAGE);

#define DHTPIN 27
DHT dht(DHTPIN, DHTTYPE);

String apiWritekey = "B88FV10HS5DKRPN2";   // Api key is used to write your sensor vlaues onto the thingspeak channel
const char* ssid = "khan";           // the name of the WiFi network you want to connect to
const char* password = "11223344" ;       // password of router

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
  //WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) // The while() loop will keep looping as long as WiFi.status() is other than WL_CONNECTED (connection to router). The loop will exit only if the status changes to WL_CONNECTED.
    {
    delay(500);
    Serial.print(".");
  
    }
     while (!Serial) {
    ; // wait for serial connection
  }

  Serial.println("");   // blank new line

  Serial.println("Calibrating MQ7");
  mq7.calibrate();    // calculates R0
  Serial.println("Calibration done!");
   // Initialize DSM501
  dsm501.begin(MIN_WIN_SPAN);
  dht.begin();
  // wait 60s for DSM501 to warm up
 // for (int i = 1; i <= 60; i++)
  //{
   // delay(1000); // 1s
   // Serial.print(i);
    // Serial.println(" s (wait 60s for DSM501 to warm up)");
  //}
  
    
    }

void loop() {
    dsm501.update();
  float PM1_0 = dsm501.getParticleWeight(0); 
  float PM2_5 = dsm501.getParticleWeight(1);  
  float h = dht.readHumidity();           // read humidity values from sensor
  float t = dht.readTemperature();        // read temperature values from sensor
  float mq = mq7.readPpm();
  if (client.connect(server,80))         // Connects to a specified IP address and port. The return value indicates success or failure. "184.106.153.149" or api.thingspeak.com
  {
    String tsData = apiWritekey;         // store API write key in variable tsData
    tsData +="&field1=";                 // upload data into field 1 
    tsData += String(t);                 // upload temperature values into field 1
    tsData +="&field2=";                 // upload data into field 3 
    tsData += String(h);                 // upload humidity values into field 3
    tsData +="&field3=";
    tsData += String(mq);
    tsData +="&field4=";
    tsData += String(PM1_0);
    tsData +="&field5=";
    tsData += String(PM2_5);
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
    Serial.print("\"Carbon Monoxide\": ");
    Serial.print(mq);
    Serial.print(" ppm");
    Serial.print("\"PM1.0\": ");
    Serial.print(PM1_0);
    Serial.print(" ug/m3");
    Serial.print("\"PM2.5\": ");
    Serial.print(PM2_5);
    Serial.print(" ug/m3");
    Serial.print("}\n");
    delay(1000);                      // delay of 1 second
    Serial.println("uploaded to Thingspeak server....");  // print "uploaded to Thingspeak server...." at serial monitor
  }
 

  Serial.println("Waiting to upload next reading...");   // print "Waiting to upload next reading..." at serial monitor
  Serial.println();
  delay(15000);                                         // delay for next reading
}
