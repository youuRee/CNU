#define LEDa1 7
const int FLEX_PIN = A0; // Pin connected to voltage divider output
// Measure the voltage at 5V and the actual resistance of your resistor, and enter them below:
const float VCC = 5; // Measured voltage of Ardunio 5V line
const float R_DIV = 10000.0; // Measured resistance of your resistor
// Upload the code, then try to adjust these values to more accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg
void setup()
{
 Serial.begin(9600);
 pinMode(FLEX_PIN, INPUT);
 pinMode(LEDa1,OUTPUT);
}
void loop()
{
 // Read the ADC, and calculate voltage and resistance from it
 int flexADC = analogRead(FLEX_PIN);
 float flexV = flexADC * VCC / 1023.0;
 float flexR = R_DIV * (VCC / flexV - 1.0);
 Serial.println("Resistance: " + String(flexR) + " ohms");
 // Use the calculated resistance to estimate the sensor's bend angle:
 float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);

 Serial.println("Bend: " + String(angle) + " degrees");
 Serial.println();
 int brt = int(angle);
 if( brt < 10 ) brt = 10;
 else if( brt > 250 ) brt = 250;

 analogWrite(LEDa1,brt);
 delay(500);
}

