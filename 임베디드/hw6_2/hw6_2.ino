#include <SoftwareSerial.h>
#include <Servo.h>

#define ENB 6
#define IN4 7
#define IN3 8

#define BUTTON1 22
#define BUTTON2 24
#define BUTTON3 26

SoftwareSerial bluetooth(10, 11); // RX, TX
Servo servo; // Servo object

int state = LOW;
int power = 128;
int angle = 1;
// fan turn on/off -> button1
int val = LOW;
int old_val = LOW;
unsigned long debounce_time = 0;
unsigned long debounce_delay = 50;

// fan power -> button2
int val2 = LOW;
int old_val2 = LOW;

// rotation turn on/off -> button3
int val3 = LOW;
int old_val3 = LOW;
int state2 = LOW;

void setup() {
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  servo.attach(5); // Attach servo motor to pin 5
  bluetooth.begin(9600);
  Serial.begin(9600);
}

void turn() {
  if (bluetooth.available()){
    char cmd = bluetooth.read();
    if (cmd == '1') {
      state = HIGH;
      Serial.println("turn on!");
    }
    else if (cmd == '0') {
      state = LOW;
      Serial.println("turn off!");
    }
  }
  else {
    val = digitalRead(BUTTON1);
    if (val != old_val) {
      if (millis() - debounce_time > debounce_delay) {
        if (val == HIGH) {
          state = !state;
          Serial.println(state ? "turn on!" : "turn off!");
        }
        debounce_time = millis();
      }
    }
    old_val = val;
  }
}

void control() {
  if (bluetooth.available()) {
    char cmd = bluetooth.read();
    if (cmd == '2') {
      power = 160;
      Serial.println("Power: 160");
    }
    else if (cmd == '3') {
      power = 192;
      Serial.println("Power: 192");
    }
    else if (cmd == '4') {
      power = 224;
      Serial.println("Power: 224");
    }
    else if (cmd == '5') {
      power = 256;
      Serial.println("Power: 256");
    }
  }
  else {
    val2 = digitalRead(BUTTON2);
    if (val2 != old_val2) {
      if (millis() - debounce_time > debounce_delay) {
        if (val2 == HIGH) {
          power += 32;
          if (power > 256) power = 128;
          Serial.print("Power: ");
          Serial.println(power);
        }
        debounce_time = millis();
      }
    }
    old_val2 = val2;
  }
}

void rotation() {
  if (bluetooth.available()) {
    // 블루투스 입력 처리
    char cmd = bluetooth.read();
    if (cmd == '8') {
      state2 = HIGH;
      Serial.println("rotation on!");
      servo.write(180);
    }
    else if (cmd == '9') {
      state2 = LOW;
      Serial.println("rotation off!");
      servo.write(0);
    }
  }
  
  // 버튼 입력 처리
  val3 = digitalRead(BUTTON3);
  if (val3 != old_val3) {
    if (val3 == HIGH) {
      if (millis() - debounce_time > debounce_delay) {
        state2 = !state2;
        if (state2 == HIGH) {
          Serial.println("rotation on!");
          servo.write(90);
        }
        else {
          Serial.println("rotation off!");
          servo.write(0);
        }
        debounce_time = millis();
      }
    }
  }
  old_val3 = val3;
}

void motor() {
  if (state == LOW) {
    analogWrite(ENB, state);
    digitalWrite(IN4, state);
    digitalWrite(IN3, state); 
    //servo.write(1);
  }
  else {
    analogWrite(ENB, power);
    digitalWrite(IN4, state);
    digitalWrite(IN3, !state);
  }
}

void loop() {
  turn();
  control();
  rotation();
  motor();
}
