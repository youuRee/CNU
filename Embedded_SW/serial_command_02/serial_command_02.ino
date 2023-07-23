#define LightSensor 0
#define Thermistor 1
void setup(){
 Serial.begin(9600);
}
byte sntmsg[4];
float pad = 10000;
float convertToCelsius(int RawADC) {
 long Resistance;
 float Temp; // Dual-Purpose variable to save space.
 Resistance=((1024 * pad / RawADC) - pad);
 Temp = log(Resistance);
 Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
 Temp = Temp - 273.15;
 return Temp; }
void loop(){
 int val1 = analogRead(LightSensor);
 int val2 = analogRead(Thermistor);
 float temp = convertToCelsius(val2);
 sntmsg[0] = (byte)(val1>>8);
 sntmsg[1] = (byte)(val1);
 sntmsg[2] = (byte)(val2>>8);
 sntmsg[3] = (byte)(val2);

 Serial.write(sntmsg,4);

 delay(1000);
}
 