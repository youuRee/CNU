#include <SimpleTimer.h>

#define led 30
#define speakerOut 32
#define Thermistor 0

SimpleTimer timer;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(speakerOut, OUTPUT);
  Serial.begin(9600);
  timer.setInterval(1000, blink);
  timer.setInterval(5000, read);

}

float pad = 10000;

float convertToCelsius(int RawADC) {
  long Resistance;
  float Temp; // Dual-Purpose variable to save space.
  Resistance=((1024 * pad / RawADC) - pad);
  Temp = log(Resistance);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;
  return Temp; 
}

void read() {
  int val = analogRead(Thermistor);
  float temp = convertToCelsius(val);

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("°C");
  
  if (temp < 23) {
    Serial.println("It's chilly today");
    tone(speakerOut, 1000, 5000);
    delay(1000);
    noTone(speakerOut);
  }

}

void blink() {
  digitalWrite(led, !digitalRead(led));
}

void loop() {
  timer.run();
}
