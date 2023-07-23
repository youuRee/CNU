#define SERVO_PIN 9
#define BUTTON 40
const int FLEX_PIN = A0; // Pin connected to voltage divider output
// Measure the voltage at 5V and the actual resistance of your resistor, and enter them below:
const float VCC = 5; // Measured voltage of Ardunio 5V line
const float R_DIV = 10000.0; // Measured resistance of your resistor
// Upload the code, then try to adjust these values to more accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

int FSR_PIN = A1; // the FSR and 10K pulldown are connected to a1
int fsrReading; // the analog reading from the FSR resistor divider
int fsrVoltage; // the analog reading converted to voltage
unsigned long fsrResistance; // The voltage converted to resistance
unsigned long fsrConductance;
long fsrForce; // Finally, the resistance converted to force
int brt;

void setup() {
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
  pinMode(FSR_PIN, INPUT);
  pinMode(SERVO_PIN, OUTPUT);
}

void servoPulse(int servoPin, int angle) {

  int pulseWidth = (angle*11) + 700;
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);
  delay(20 - pulseWidth/1000);
}

int cnt = 0;
int servoAngle;

void loop() {
int state = digitalRead(BUTTON);
  if (state == 1) {
    if (cnt == 0) {
      // flex sensor
      int flexValue = analogRead(FLEX_PIN);
      servoAngle = map(flexValue, 0, 1023, 0, 180);
      Serial.println("flex");
      Serial.println(servoAngle);
      cnt = 1;
    }
    else {
      // force sensor
      int forceValue = analogRead(FSR_PIN);
      servoAngle = map(forceValue, 0, 1023, 0, 180);
      Serial.println("force");
      Serial.println(forceValue);
      Serial.println(servoAngle);
      cnt = 0;
    }
    //delay(200);
  }
  int d_angle = 1;
  for (int angle = 0; angle <= servoAngle; angle = angle + d_angle) {
    servoPulse(SERVO_PIN, angle);
  }
  delay(1000);

}
