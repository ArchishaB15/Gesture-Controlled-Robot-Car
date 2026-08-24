#include <RH_ASK.h>
#include <SPI.h>

// RF receiver
// Speed = 2000
// RX pin = GPIO 4
RH_ASK driver(2000, 4, 21, 0);

// L298N motor driver pins
#define IN1 27
#define IN2 28
#define IN3 29
#define IN4 33

void setup() {
  Serial.begin(115200);

  // Set motor driver pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Start with motors stopped
  stopMotors();

  // Initialize RF receiver
  if (!driver.init()) {
    Serial.println("Receiver failed!");
  } else {
    Serial.println("Receiver ready!");
  }
}

void loop() {

  uint8_t buf[20];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {

    char command = buf[0];

    Serial.print("Received: ");
    Serial.println(command);

    // Interpret command
    if (command == 'F') {
      forward();
    }
    else if (command == 'B') {
      backward();
    }
    else if (command == 'L') {
      left();
    }
    else if (command == 'R') {
      right();
    }
    else if (command == 'S') {
      stopMotors();
    }
  }
}

// ---------------- MOTOR FUNCTIONS ----------------

void forward() {
  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  // Left motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  // Left motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
