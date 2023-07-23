#define LightSensor 0
#define BUTTON 40

const int ledPins[6] = {2, 3, 4, 5, 6, 7};

int bnt_val = 0;
int bnt_old_val = 0;
int sensorValue;
bool holdValue = false;
int brightness = 0; 

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(LightSensor, INPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  bnt_val = digitalRead(BUTTON);

  if (bnt_val == LOW && bnt_old_val == HIGH) {
    holdValue = !holdValue;
  }
  bnt_old_val = bnt_val;

  if (!holdValue) {
    sensorValue = analogRead(LightSensor);
    sensorValue = sensorValue / 16; // sensorValue 값 범위 : 0~15

    for (int i = 0; i < 6; i++) {
      // bitread(x,n) : x를 bit로 바꾸고 그 x의 n번째 bit의 값을 읽음
      if (bitRead(sensorValue, i) == 1) {
        digitalWrite(ledPins[i], HIGH);
      } else {
        digitalWrite(ledPins[i], LOW);
      }
    }  
    delay(500);
  }

}
