#include <ESP8266WiFi.h>         // This library provides ESP8266 specific Wi-Fi routines that we are calling to connect to the network.
#include "DHTesp.h"              // Through this liberary,we can have access to the functionalities needed to get temperature measurements
DHTesp dht;                      // Global Variable


String apiWritekey = "VYEU6KXB0JNG8V7R";   // Api key is used to write your sensor vlaues onto the thingspeak channel
const char* ssid = "vivo 1823";           // the name of the WiFi network you want to connect to
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
