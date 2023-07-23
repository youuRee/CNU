#include <SoftwareSerial.h>
#include <Servo.h>

#define ENB 6
#define IN4 7
#define IN3 8
#define POWER_BUTTON_PIN 22
#define FAN_BUTTON_PIN 24
#define ROTATION_BUTTON_PIN 26

SoftwareSerial bluetooth(10, 11); // RX, TX
Servo servo; // Servo object

bool fanOn = false;
int fanPowerLevel = 0;
bool rotationOn = false;

void setup() {
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(POWER_BUTTON_PIN, INPUT);
  pinMode(FAN_BUTTON_PIN, INPUT);
  pinMode(ROTATION_BUTTON_PIN, INPUT);
  servo.attach(5); // Attach servo motor to pin 5
  bluetooth.begin(9600);
  Serial.begin(9600);
  // Initialize the fan and rotation states
  updateFanState();
  updateRotationState();
}

void dcMotor() {
  int fanButtonState = digitalRead(FAN_BUTTON_PIN);
  if (fanButtonState == HIGH) {
    fanOn = !fanOn; // Toggle fan state
    updateFanState();
    delay(500); // Debounce delay
  }
}

void servoMotor() {
  int rotationButtonState = digitalRead(ROTATION_BUTTON_PIN);
  if (rotationButtonState == HIGH && fanOn) {
    rotationOn = !rotationOn; // Toggle rotation state
    updateRotationState();
    delay(500); // Debounce delay
  }
}

void updateFanState() {
  if (fanOn) {
    analogWrite(ENB, fanPowerLevel); // Set fan speed to maximum
    digitalWrite(IN4, fanOn);
    digitalWrite(IN3, !fanOn); 
  } else {
    analogWrite(ENB, 0); // Turn off the fan
  }
}

void updateRotationState() {
  if (rotationOn) {
    servo.write(90); // Set servo angle to 90 degrees
  } else {
    servo.write(0); // Set servo angle to 0 degrees
  }
}

void loop() {
  // Check for incoming Bluetooth commands
  if (bluetooth.available()) {
    char command = bluetooth.read();
    if (command == 'f') {
      Serial.println("Fan on!");
      fanOn = !fanOn; // Toggle fan state
      updateFanState();
    } else if (command == 'p') {
      // Adjust fan power level based on command value
      Serial.println("You can power control!");
      if (bluetooth.available()) {
        char powerLevel = bluetooth.read();
        Serial.println(powerLevel);
        if (powerLevel >= '1' && powerLevel <= '4') {
          fanPowerLevel = map(powerLevel - '0', 1, 4, 64, 255); // Convert power level to PWM value
          updateFanState();
        }
      }
    } else if (command == 'r') {
      Serial.println("You can rotation control!");
      rotationOn = !rotationOn; // Toggle rotation state
      updateRotationState();
    }
  }
  
  // Check the state of physical buttons
  dcMotor();
  servoMotor();
}



