#define LightSensor1 0
#define LightSensor2 1
#define led 40

void setup() {
  pinMode(led, OUTPUT);
  pinMode(LightSensor1, INPUT);
  pinMode(LightSensor2, INPUT);
}

void loop() {
  int sensor_val1 = analogRead(LightSensor1); // 아날로그 선언 -> 자료형 필요!
  int sensor_val2 = analogRead(LightSensor2);

  // sensor 값 작으면(밝기 낮으면) led 껐다켰다 빨라짐 -> delay 값 줄이기 
  if (sensor_val1 > 500 && sensor_val2 > 500) {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  } else if (sensor_val1 > 500 || sensor_val2 > 500) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  } else {
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);
  }
}
