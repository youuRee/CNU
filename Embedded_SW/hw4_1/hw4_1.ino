#include <LimitedLogQueue.h>
#define LightSensor 0
#define Thermistor 1
#define Button 2

// LimitedLogQueue class 객체 생성하면 QueueArray의 큐 자료구조 같이 생성
LimitedLogQueue <int> l_queue("Light Sensor", 0);
LimitedLogQueue <int> t_queue("Thermister", 0);

int count = 0;

void setup() {
  pinMode(Button, OUTPUT);
  Serial.begin(9600);
}

void start() {
  if (count < 10) {
    int val1 = analogRead(LightSensor);
    int val2 = analogRead(Thermistor);
    l_queue.add(val1);
    t_queue.add(val2);
    count+=1;
    delay(100);
  }

  else {
    Serial.println("Light Sensor Values:");
    float l_mean = l_queue.getAverage();

    Serial.println("Thermistor Values:");
    float t_mean = t_queue.getAverage();

    if (l_mean > 400) {
      Serial.println("I Love Sunshine");
    }
    
    if (l_mean < 150) {
      Serial.println("“I Need More Sunshine");
    }
  } 
}

void loop() {
  int b_val = digitalRead(Button);
  if (b_val == HIGH) {
    start();
    delay(100);
  }

}
