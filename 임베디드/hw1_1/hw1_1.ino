int LED_pin[6] = {5, 6, 7, 8, 9, 10};
int LED_state[6] = {LOW, LOW, LOW, LOW, LOW, LOW};

void setup()
{
  for (int i = 0; i < 6; i++) {
    pinMode(LED_pin[i], OUTPUT);
  }
}

void loop()
{
  int rand = random(0, 6);

  for (int i = 0; i < 6; i++) {
    if (i == rand) {
      LED_state[i] = !LED_state[i];
      break;
    }
  }
  // LED_state[rand] = !LED_state[rand]; -> 위에 for문 안쓰고 이거 하나만 써도 ok
  digitalWrite(LED_pin[random_LED], LED_state[random_LED]);
  delay(1000);
}

