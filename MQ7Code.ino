#include <MQ7.h>

#define A_PIN 2
#define VOLTAGE 5

// init MQ7 device
MQ7 mq7(A_PIN, VOLTAGE);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial connection
  }

  Serial.println("");   // blank new line

  Serial.println("Calibrating MQ7");
  mq7.calibrate();    // calculates R0
  Serial.println("Calibration done!");
}
 
void loop() {
  Serial.print("PPM = "); Serial.println(mq7.readPpm());

  Serial.println("");   // blank new line
  delay(1000);
}
