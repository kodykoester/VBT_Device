
<h2 align="center">Velocity based training device.</h2>

<p align="left">
Strength coaches control as many factors as possible to help train their athletes appropriately and target a desired outcome. Think rest, sets, reps, load, etc. What happens when external factors like sleep, stress, and nutrition get in the way? These devices account for such factors with something called:

### **Auto-Regulation** 

By monitoring velocity of a given exercise, athletes can adjust their training weight based on their daily readiness and fatigue levels. This concept is known as auto-regulation. If an athlete is not moving a weight at the desired velocity, it may indicate fatigue, and they can adjust the load accordingly to maintain optimal training intensity.
</p>
</div>

### Built With

[![Arduino Shield](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)


## Benefits
- **Affordable:** Significantly reduces the cost of velocity-based training equipment.
- **Versatile:** Offers both wireless and wired modes for flexible usage.
- **User-Friendly:** Can be integrated with a computer to display velocity data in real-time.

## Limitations
- **Accuracy:** Requires measurement of the athlete's pulling height for precise data.

## Technical Specifications

### Hardware
- Arduino microcontroller
- BLE (Bluetooth Low Energy) module for wireless communication
- Accelerometer (e.g., BMI270 or LSM9DS1)

### Software
- **Python and Pygame** for displaying data on a computer screen
- **Arduino Code** for sensor data processing and BLE communication

## Installation

### Python Code (Pygame Display)
The Python script initializes a serial connection and uses Pygame to display the velocity data received from the Arduino. The data is read from the serial port and displayed as large text on the screen.

#### Dependencies
- `serial`
- `pygame`

<!-- ROADMAP -->
## Roadmap

- [x] Add BLE Connectivity
- [ ] Refine code
- [x] Add multi-orientation support?
- [ ] Multi-language Support

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->

[arduino-shield]: https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white

