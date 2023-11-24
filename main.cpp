#include <Arduino_LSM9DS1.h>

const float thresholdStart = 1.2; // Acceleration threshold to start the timer (in g)
const float thresholdStop = 0.3;  // Acceleration threshold to stop the timer (in g)

unsigned long startTime = 0;
bool timing = false;

void setup() {
  Serial.begin(9600);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize the LSM9DS1 IMU!");
    while (1);
  }
}

void loop() {
  sensors_event_t accelEvent;
  IMU.readAcceleration(accelEvent);

  float zAcceleration = accelEvent.acceleration.z;

  // Check if the Z-axis acceleration is greater than the start threshold
  if (zAcceleration >= thresholdStart && !timing) {
    startTimer();
  }

  // Check if the Z-axis acceleration is less than the stop threshold
  if (zAcceleration <= thresholdStop && timing) {
    stopTimer();
  }
}

void startTimer() {
  startTime = millis();
  timing = true;
  Serial.println("Timer started!");
}

void stopTimer() {
  timing = false;
  unsigned long stopTime = millis();
  unsigned long elapsedTime = stopTime - startTime;

  Serial.print("Timer stopped! Elapsed time: ");
  Serial.print(elapsedTime);
  Serial.println(" milliseconds");
}
