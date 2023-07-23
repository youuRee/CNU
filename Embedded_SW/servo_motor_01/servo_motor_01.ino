#define SERVO_PIN 9
void setup()
{
 pinMode(SERVO_PIN, OUTPUT);
}
void servoPulse(int servoPin, int angle)
{
 // 20ms : period of ServoPulse PWM signal
 // ~1ms pulse : 0 degree position
 // ~1.5ms pulse : 90 degree position
 // ~2ms pulse : 180 degree position
int pulseWidth = (angle*11) + 700;
 digitalWrite(servoPin, HIGH);
 delayMicroseconds(pulseWidth);
 digitalWrite(servoPin, LOW);
 delay(20 - pulseWidth/1000);
}
void loop()
{
 int d_angle = 10;
 for (int angle = 0; angle <= 180; angle = angle + d_angle) {
 servoPulse(SERVO_PIN, angle);
 }
 delay(1000);
} 
