#define A_BUTTON 22
#define B_BUTTON 23

int LED_pin[4] = {28, 29, 30, 31};
int val_A = 0;
int val_B = 0;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(LED_pin[i], OUTPUT);
  }
  pinMode(A_BUTTON, INPUT);
  pinMode(B_BUTTON, INPUT);

}

void loop() {
  val_A = digitalRead(A_BUTTON);
  val_B = digitalRead(B_BUTTON);

  if (val_A == HIGH) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED_pin[i], HIGH);
      delay(500);
    }
    for (int i = 3; i >= 0; i--) {
      digitalWrite(LED_pin[i], LOW);
      delay(500);
    }
  } else {
      for (int i = 0; i < 4; i++) {
      digitalWrite(LED_pin[i], LOW);
      delay(500);
    }
  }

  if (val_B == HIGH) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED_pin[i], HIGH);
      delay(500);
      digitalWrite(LED_pin[i], LOW);
      delay(500);
      digitalWrite(LED_pin[i], HIGH);
      delay(500);
    }
    for (int i = 3; i >= 0; i--) {
      digitalWrite(LED_pin[i], LOW);
      delay(500);
      digitalWrite(LED_pin[i], HIGH);
      delay(500);
      digitalWrite(LED_pin[i], LOW);
      delay(500);
      digitalWrite(LED_pin[i], HIGH);
      delay(500);
      digitalWrite(LED_pin[i], LOW);
      delay(500);
    }   
  } else {
      for (int i = 0; i < 4; i++) {
      digitalWrite(LED_pin[i], LOW);
      delay(500);
    }
  }
  delay(1000);
}
