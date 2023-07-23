void setup() {
  // 시리얼 통신 시작
  Serial.begin(9600);
  // LED1 핀 설정
  pinMode(5, OUTPUT);
  // LED2 핀 설정
  pinMode(6, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    byte buffer[4];
    int count = Serial.readBytes(buffer, 4);
    if (count == 4) {
      byte cmd = buffer[0];
      byte onoff = buffer[1];
      byte mode = buffer[2];
      byte reserved = buffer[3];

      if (cmd == 0x01) {  // LED1 제어
        if (onoff == 0x01) {  // ON
          digitalWrite(5, HIGH);
          if (mode == 0x02) {  // Blink 모드
            digitalWrite(6, LOW);
            delay(500);
            digitalWrite(6, HIGH);
            delay(500);
          }
        } else {  // OFF
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
        }
      } else if (cmd == 0x02) {  // LED2 제어
        if (onoff == 0x01) {  // ON
          digitalWrite(6, HIGH);
          if (mode == 0x02) {  // Blink 모드
            digitalWrite(5, LOW);
            delay(500);
            digitalWrite(5, HIGH);
            delay(500);
          }
        } else {  // OFF
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
        }
      }
    }
  }
}
