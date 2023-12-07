#include <ArduinoBLE.h>
#include <Arduino_BMI270_BMM150.h>
// If you're using the PlatformIO plugin on VScode you'll need to 
// replace #include <Arduino_BMI270_BMM150.h> with #include <Arduino_LSM9DS1.h>

unsigned long startTime = 0;
unsigned long endTime = 0;
bool timing = false;
float distance = 1.0; // Distance in meters

BLEService environmentService("181A"); // Environmental Sensing Service UUID
BLECharacteristic temperatureCharacteristic("2A6E", BLERead | BLENotify, 4); // Temperature Characteristic UUID
BLECharacteristic humidityCharacteristic("2A6F", BLERead | BLENotify, 4);    // Humidity Characteristic UUID
BLECharacteristic speedCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 20); // Custom Speed Characteristic UUID

void setup() {
  Serial.begin(9600);

  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE! Exiting...");
    while (1);
  }

  // Set the local name for the BLE device
  BLE.setLocalName("SpeedSensor");

  // Add the service and characteristics
  BLE.setAdvertisedService(environmentService);
  environmentService.addCharacteristic(temperatureCharacteristic);
  environmentService.addCharacteristic(humidityCharacteristic);
  environmentService.addCharacteristic(speedCharacteristic);
  BLE.addService(environmentService);

  // Start advertising
  BLE.advertise();

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

      // Convert the float to a string
      char speedStr[20]; // Adjust the size as needed
      snprintf(speedStr, sizeof(speedStr), "%.4f", speed);

      // Update BLE characteristics
  
      speedCharacteristic.writeValue(speedStr);

      // Print the speed in meters per second
      Serial.print("Speed: ");
      Serial.println(speed, 2); // 4 decimal places

      // Reset for the next measurement
      startTime = 0;
      endTime = 0;

      // Delay before the system is ready for the next measurement
      delay(2500); // Adjust this delay as needed
      Serial.println("System ready.");
    }
  }

  // Keep the BLE stack running
  BLE.poll();
}
