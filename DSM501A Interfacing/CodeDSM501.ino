#include<DSM501.h>
#define DSM501_PM10 26
#define DSM501_PM25 25
int a;
DSM501 dsm501(DSM501_PM10, DSM501_PM25);
String apiWritekey = "B88FV10HS5DKRPN2";   // Api key is used to write your sensor vlaues onto the thingspeak channel
const char* ssid = "khan";           // the name of the WiFi network you want to connect to
const char* password = "11223344" ;       // password of router
const char* server = "api.thingspeak.com";  // this is the thingspeak address  
float resolution=3.3/1023;                  // 3.3 is the supply volt  & 1023 is max analog read value 
WiFiClient client;                          // client that will be contacting the host (server)
void setup()
{
  // Initialize DSM501
  dsm501.begin(MIN_WIN_SPAN);
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
}

void loop()
{
  for(a=1;a<=100;a++){
  // call dsm501 to handle updates.
  dsm501.update();

  Serial.print(a);
  Serial.print(")");
  // get PM density of particles over 1.0 μm
  Serial.print("PM10: ");
  Serial.print(dsm501.getParticleWeight(0));
  Serial.print(" ug/m3");
 
  // get PM density of particles over 2.5 μm
  Serial.print("  PM25: ");
  Serial.print(dsm501.getParticleWeight(1));
  Serial.println(" ug/m3");

   if (client.connect(server,80))
   {
    String tsData = apiWritekey;
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
    delay(1000);                      // delay of 1 second
    Serial.println("uploaded to Thingspeak server....");  // print "uploaded to Thingspeak server...." at serial monitor
   }
  Serial.println("Waiting to upload next reading...");   // print "Waiting to upload next reading..." at serial monitor
  Serial.println();
  delay(15000);                                         // delay for next reading
  }
}
  
