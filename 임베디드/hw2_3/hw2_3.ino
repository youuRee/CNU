#define Thermistor 0
#define led1 32
#define led2 30

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(Thermistor, INPUT);

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


void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(Thermistor);
  float temp = convertToCelsius(val);

  // Serial.println(temp);

  if (temp >= 25) {
    digitalWrite(led1, HIGH);
    Serial.println("LED ON!");
  } else {
    digitalWrite(led1, LOW);
  }

   if (temp >= 27) {
    digitalWrite(led2, HIGH);
    Serial.println("LED ON!");
  } else {
    digitalWrite(led2, LOW);
  }
}

