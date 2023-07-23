#include "telegraph.h"
#define LED1 30
#define LED2 32
const unsigned int DIT_LENGTH = 100;

const byte COMMAND_1 = 0x1;
const byte COMMAND_2 = 0x2;

byte rcvmsg[4];
unsigned int mod;
unsigned int led;
unsigned int state;

bool is_blinking_1 = false; // 깜빡임 상태를 저장할 변수
bool is_blinking_2 = false;

void setup() {
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 Serial.begin(9600);
}

void blink(int led_pin) {
 digitalWrite(led_pin, HIGH);
 delay(500);
 digitalWrite(led_pin, LOW);
 delay(500);
 digitalWrite(led_pin, HIGH);
 delay(500);
 digitalWrite(led_pin, LOW);
 delay(500);
}

void loop() {
 if (Serial.available() > 0) {
  int len = Serial.readBytes(rcvmsg, sizeof(rcvmsg));
  led = rcvmsg[0];
  state = rcvmsg[1];
  mod = rcvmsg[2];

  if (state == 1) {
   if (led == 1) {
    if (mod == 1) {
     digitalWrite(LED1, HIGH);
     is_blinking_1 = false; // 깜빡임 상태를 해제
    }
    else if (mod == 2) {
     is_blinking_1 = true; // 깜빡임 상태를 설정
    }
   }
   else if (led == 2) {
    if (mod == 1) {
     digitalWrite(LED2, HIGH);
     is_blinking_2 = false; // 깜빡임 상태를 해제
    }
    else if (mod == 2) {
     is_blinking_2 = true; // 깜빡임 상태를 설정
    }
   }
  }
  else if (state == 2) {
   if (led == 1) {
    digitalWrite(LED1, LOW);
    is_blinking_1 = false; // 깜빡임 상태를 해제
   }
   else if (led == 2) {
    digitalWrite(LED2, LOW);
    is_blinking_2 = false; // 깜빡임 상태를 해제
   }
  }
 }

 if (is_blinking_1) { // 깜빡임 상태인 경우
    blink(LED1); // LED1을 깜빡임
 }
  if (is_blinking_2) { // 깜빡임 상태인 경우
    blink(LED2); // LED2을 깜빡임
 }
}


