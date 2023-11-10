
#include <Arduino_LPS22HB.h> // Barometer Sensor Library
#include "Arduino_BMI270_BMM150.h" // IMU Sensor Library

int currentalt;

int time1;
int time2;

int altstamp1;
int altstamp2;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
}

void loop() {
  float pressure = BARO.readPressure();  //Read presure
  float altitude = 44330 * ( 1 - pow(pressure/101.325, 1/5.255) ); // convert it to meters
  float currentalt = ((altitude) - 322.25);    // equation to balance current pressure to zero-ish.

  Serial.print(currentalt);
  // print an empty line
  Serial.println();
  // wait 1 second to print again
  delay(100);
  }
}
