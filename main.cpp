#include <Arduino_LSM9DS1.h>

unsigned long startTime = 0;
unsigned long endTime = 0;
bool timing = false;

void setup() {
  Serial.begin(9600);
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.println("Ready");
}

void loop() {
  float x, y, z;
   if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    

  if (z > 1.2 && !timing) {
    // Start the timer
    startTime = millis();
    timing = true;
    Serial.println("Timer started!");
  }

  if (timing && z < 0.3) {
    // Stop the timer
    endTime = millis();
    unsigned long elapsedTime = endTime - startTime;
    timing = false;

    // Print the elapsed time
    Serial.print("Elapsed Time: ");
    Serial.print(elapsedTime);
    Serial.println(" ms");
  }
}
}
