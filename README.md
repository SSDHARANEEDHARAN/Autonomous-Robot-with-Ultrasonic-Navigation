# Autonomous Robot with Ultrasonic Navigation

![Robot Assembly](https://img.shields.io/badge/Status-Under%20Development-yellow)
![Arduino](https://img.shields.io/badge/Platform-Arduino-00979D)
![License](https://img.shields.io/badge/License-MIT-blue)

## 📋 Project Overview

An autonomous robot built with Arduino Uno that uses ultrasonic sensors for obstacle detection and navigation. The robot features a differential drive system with two DC motors and a caster wheel for stability.

## 🛠️ Components List

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno R3 | 1 | Main microcontroller |
| Lithium Battery (3.7V) | 1-2 | Power source |
| BMS (Battery Management System) | 1 | Battery protection & charging |
| L298N/L293D Motor Driver | 1 | DC motor control |
| DC Gear Motors (3-12V) | 2 | Drive wheels |
| Ultrasonic Sensors (HC-SR04) | 3 | Front, left, and right obstacle detection |
| Battery Holder | 1 | Secure battery placement |
| Robot Chassis/Frame | 1 | Structural base |
| Drive Wheels | 2 | Locomotion |
| Caster Wheel (Swivel) | 1 | Stability and balance |
| Jumper Wires | As needed | Connections |
| Breadboard (optional) | 1 | Prototyping |

## 📁 Repository Structure

```
autonomous-robot/
│
├── /src/
│   ├── main_robot.ino      # Main Arduino sketch
│   ├── motor_control.cpp   # Motor driver functions
│   └── ultrasonic.cpp      # Sensor reading functions
│
├── /docs/
│   ├── wiring_diagram.pdf  # Connection schematic
│   ├── pinout.md           # Pin configuration
│   └── assembly_guide.md   # Build instructions
│
├── /3d_models/             # Custom frame/parts (if any)
│
├── /images/                # Project photos
│
└── /lib/                   # External libraries
```

## 🔌 Wiring Diagram

### Motor Driver Connections
```
Motor Driver (L298N) → Arduino
ENA → Pin 5 (PWM)
IN1 → Pin 7
IN2 → Pin 8
ENB → Pin 6 (PWM)
IN3 → Pin 9
IN4 → Pin 10
```

### Ultrasonic Sensors Connections
```
Front Sensor:
TRIG → Pin 11
ECHO → Pin 12

Left Sensor:
TRIG → Pin 2
ECHO → Pin 3

Right Sensor:
TRIG → Pin 4
ECHO → Pin 13
```

### Power Management
```
Battery (+) → BMS IN+
BMS OUT+ → Motor Driver 12V
BMS OUT+ → Arduino Vin (or 5V with regulator)
GND → Common ground all components
```

## 🚀 Installation & Setup

### 1. Hardware Assembly
1. Mount motors on chassis
2. Attach wheels to motor shafts
3. Install caster wheel at front/rear
4. Secure battery holder and BMS
5. Mount Arduino and motor driver
6. Position ultrasonic sensors (front, left, right)

### 2. Software Requirements
- Arduino IDE 1.8.x or newer
- No external libraries required for basic functionality

### 3. Upload Code
```bash
1. Clone this repository
2. Open Arduino IDE
3. Navigate to File → Open → main_robot.ino
4. Select correct board (Arduino Uno) and port
5. Click Upload
```

## 🎮 Operation Modes

The robot currently supports:

1. **Obstacle Avoidance Mode** - Default autonomous navigation
2. **Manual Control Mode** - Serial command control
3. **Test Mode** - Component diagnostics

Switch between modes via Serial Monitor commands:
- `A` - Autonomous mode
- `M` - Manual control
- `T` - Test sensors/motors
- `S` - Stop all motors

## ⚙️ Configuration

Adjust these parameters in `main_robot.ino`:

```cpp
// Navigation parameters
#define SAFE_DISTANCE 20    // cm - minimum safe distance
#define TURN_DELAY 500      // ms - turning duration
#define SPEED_NORMAL 150    // 0-255 motor speed

// Motor calibration (if needed)
#define LEFT_MOTOR_OFFSET 0
#define RIGHT_MOTOR_OFFSET 0
```

## 🔋 Power Specifications

- **Input Voltage**: 7-12V DC (via BMS)
- **Motor Voltage**: 3-12V (depending on battery)
- **Arduino**: 5V regulated from motor driver or direct from BMS
- **Current Consumption**: 500mA-2A (peak with motors)

⚠️ **Safety Notes**:
- Always use BMS with lithium batteries
- Ensure proper polarity when connecting
- Add appropriate fuses if needed
- Do not exceed motor driver current rating

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🆘 Troubleshooting

| Issue | Possible Solution |
|-------|-------------------|
| Motors not moving | Check power connections, enable pins |
| Erratic sensor readings | Ensure stable power, check wiring |
| Robot moves in circles | Calibrate motor offsets, check wheel grip |
| Arduino resets randomly | Add capacitors near power inputs, check battery level |

## 🙏 Acknowledgments

- Arduino community for extensive resources
- HC-SR04 ultrasonic sensor documentation
- Various open-source robot projects for inspiration

## 📞 Contact

For questions or support, please:
1. Open an Issue in this repository
2. Provide detailed description of your problem
3. Include photos of your setup if relevant

