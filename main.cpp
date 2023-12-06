
#include <ArduinoBLE.h>
#include <Arduino_BMI270_BMM150.h>

unsigned long startTime = 0;
unsigned long endTime = 0;
bool timing = false;
float distance = 1.0; // Distance in meters

void setup() {
  Serial.begin(9600);

  while (!IMU.begin()) {
    Serial.println("Failed to initialize IMU! Retrying...");
    delay(1000);
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

      // Calculate speed in meters per second
      float timeInSeconds = elapsedTime / 1000.0;
      float speed = distance / timeInSeconds;

      // Print the speed in meters per second
      // Serial.print("Speed: ");
      Serial.print(speed);
      Serial.println(" m/s");
      // Reset for the next measurement
      startTime = 0;
      endTime = 0;

      // Delay before the system is ready for the next measurement
      // Serial.println("System will be ready in 2-3 seconds...");
      delay(2500); // Adjust this delay as needed
      Serial.println("System ready.");
    }
  }
}
