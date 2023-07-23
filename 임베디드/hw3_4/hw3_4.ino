// 시리얼 모니터 입력값에 1, 2, 3, 4 숫자를 넣고 버튼을 누르면 누른 숫자대로 해당 led 불이 켜짐
// ex) 1, 3, 1, 3 -> led1 led3 led1 led3 순으로 on!

#define button 2
#define LED1 43
#define LED2 42
#define LED3 41
#define LED4 40

int queue[50];
int queueLength = 0;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(button), executeQueue, RISING);
}

void loop() {
  if (Serial.available() > 0) {
    int input = Serial.parseInt();
    if (input >= 1 && input <= 4) {
      enqueue(input);
    }
  }
}

void enqueue(int input) {
  if (queueLength < 50) {
    queue[queueLength] = input;
    queueLength++;
    Serial.print("Added to queue: ");
    Serial.println(input);
  }
}

void executeQueue() {
  for (int i = 0; i < queueLength; i++) {
    switch (queue[i]) {
      case 1:
        blink(LED1);
        break;
      case 2:
        blink(LED2);
        break;
      case 3:
        blink(LED3);
        break;
      case 4:
        blink(LED4);
        break;
    }
  }
  clearQueue();
}

void blink(int led) {
  digitalWrite(led, HIGH);
  delay(50000);
  digitalWrite(led, LOW);
  delay(50000);
}

void clearQueue() {
  queueLength = 0;
  for (int i = 0; i < 50; i++) {
    queue[i] = 0;
  }
}

