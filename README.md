# Gesture-Controlled Robot Car

A wireless robot car controlled using hand gestures. An MPU6050 accelerometer detects the orientation of an Arduino Nano, which converts the detected movement into directional commands. The commands are transmitted wirelessly using RF communication to an ESP32, which controls the robot's motors through an L298N motor driver.

## How It Works

The project uses two microcontrollers:

* **Arduino Nano** — reads data from the MPU6050 and determines the hand gesture.
* **ESP32** — receives the wireless command and controls the robot's motors.

### Control Flow

**MPU6050 → Arduino Nano → RF Transmitter → RF Receiver → ESP32 → L298N → Motors**

## Gestures

| Hand Movement    | Command | Robot Movement |
| ---------------- | ------- | -------------- |
| Tilt forward     | `F`     | Forward        |
| Tilt backward    | `B`     | Backward       |
| Tilt left        | `L`     | Left           |
| Tilt right       | `R`     | Right          |
| Neutral position | `S`     | Stop           |

## Hardware

* Arduino Nano
* ESP32
* MPU6050 accelerometer/gyroscope
* RF transmitter
* RF receiver
* L298N motor driver
* 2 DC motors
* Robot car chassis
* Battery pack
* Jumper wires

## Software & Libraries

* Arduino IDE
* C/C++
* Wire library
* SPI library
* RadioHead library (`RH_ASK`)

## Arduino Nano

The Arduino Nano communicates with the MPU6050 using I2C and continuously reads the accelerometer values.

The accelerometer readings are converted into acceleration values in `g` and compared against a threshold:

```cpp
float threshold = 0.35;
```

Depending on the direction of the detected tilt, the Nano generates one of five commands:

* `F` — Forward
* `B` — Backward
* `L` — Left
* `R` — Right
* `S` — Stop

The command is then transmitted using the RF transmitter.

## ESP32

The ESP32 receives the wireless commands through the RF receiver.

Each command is mapped to a corresponding motor movement using an L298N motor driver.

### L298N Connections

| ESP32 GPIO | L298N Pin |
| ---------- | --------- |
| GPIO 27    | IN1       |
| GPIO 28    | IN2       |
| GPIO 29    | IN3       |
| GPIO 33    | IN4       |

The ESP32 controls the direction of both motors by setting the L298N input pins HIGH or LOW.

## Project Structure

```text
gesture-controlled-robot-car/
│
├── README.md
│
├── nano/
│   └── gesture_transmitter.ino
│
├── esp32/
│   └── robot_car_receiver.ino
│
├── images/
│   └── robot-car.jpg
│
└── circuit/
    └── wiring-diagram.png
```

> The `images` and `circuit` folders are optional and can be added later when photos or wiring diagrams are available.

## Features

* Wireless robot control
* Gesture-based directional control
* Real-time accelerometer input
* RF communication between microcontrollers
* Forward, backward, left, right, and stop commands
* Differential motor control
* Separate transmitter and receiver systems
* ESP32-based motor control

## Communication

The system uses RF communication between the Arduino Nano and ESP32.

### Transmitter

The Arduino Nano sends a single-character command based on the detected gesture.

| Character | Meaning  |
| --------- | -------- |
| `F`       | Forward  |
| `B`       | Backward |
| `L`       | Left     |
| `R`       | Right    |
| `S`       | Stop     |

### Receiver

The ESP32 continuously listens for incoming RF commands. When a command is received, it activates the corresponding motor-control function.

## Motor Control

The L298N motor driver controls two DC motors.

### Forward

```text
Left Motor  → Forward
Right Motor → Forward
```

### Backward

```text
Left Motor  → Backward
Right Motor → Backward
```

### Left

```text
Left Motor  → Backward
Right Motor → Forward
```

### Right

```text
Left Motor  → Forward
Right Motor → Backward
```

### Stop

```text
Left Motor  → Stop
Right Motor → Stop
```

## Setup

### 1. Arduino Nano

1. Connect the MPU6050 to the Arduino Nano using I2C.
2. Connect the RF transmitter to the Nano.
3. Upload `nano/gesture_transmitter.ino`.
4. Open the Serial Monitor to view the detected commands.

### 2. ESP32

1. Connect the RF receiver to the ESP32.
2. Connect the L298N motor driver to the ESP32.
3. Connect the motors to the L298N.
4. Upload `esp32/robot_car_receiver.ino`.
5. Open the Serial Monitor to view received commands.

### 3. Test the Robot

Once both systems are powered:

1. Tilt the Arduino Nano forward.
2. The Nano sends `F`.
3. The RF receiver receives `F`.
4. The ESP32 commands the motors to move forward.

The same process occurs for backward, left, right, and stop commands.

## Troubleshooting

### Robot does not move

Check:

* Motor battery power
* L298N motor connections
* ESP32 GPIO connections
* Common ground connections
* Motor driver power connections

### RF commands are not received

Check:

* RF transmitter and receiver power
* Transmitter and receiver data pins
* RadioHead library installation
* Matching RF communication speed
* Distance between transmitter and receiver

### Robot moves in the wrong direction

If a motor spins in the opposite direction, swap the two wires connected to that motor on the L298N.

### Robot moves when lifted but not on the ground

This usually indicates that the motors are not receiving enough power or current under load. Check the battery pack, motor driver power supply, and motor connections.

## Future Improvements

* Add obstacle detection using an ultrasonic sensor
* Add PWM-based speed control
* Improve gesture detection using gyroscope data
* Add accelerometer calibration
* Add signal filtering to reduce accidental movements
* Add rechargeable battery management
* Add Bluetooth or Wi-Fi control as an alternative
* Add a mobile control interface
* Add autonomous driving modes
* Improve the robot chassis and mechanical design

## Project Goals

This project demonstrates the integration of:

* Embedded systems
* Microcontrollers
* Sensors
* Wireless communication
* Motor control
* C/C++ programming
* Real-time input processing

The project combines these concepts into a single wireless robotic system controlled through physical hand movement.

## Author

Archisha Bodhmage

Built as an embedded systems project using Arduino Nano, ESP32, MPU6050, RF communication, and an L298N motor driver.
