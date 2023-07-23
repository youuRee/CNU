const int TriggerPin = 8; //Trig pin
const int EchoPin = 9; //Echo pin
long Duration = 0;
void setup(){
 pinMode(TriggerPin,OUTPUT); // Trigger is an output pin
 pinMode(EchoPin,INPUT); // Echo is an input pin
 Serial.begin(9600); // Serial Output
}
void loop(){
 digitalWrite(TriggerPin, LOW);
 delayMicroseconds(2);
 digitalWrite(TriggerPin, HIGH); // Trigger pin to HIGH
 delayMicroseconds(10); // 10us high
 digitalWrite(TriggerPin, LOW); // Trigger pin to HIGH
 Duration = pulseIn(EchoPin,HIGH); // Waits for the echo pin to get high
 // returns the Duration in microseconds
 long Distance_mm = Distance(Duration); // Use function to calculate the distance
 Serial.print("Distance = "); // Output to serial
 Serial.print(Distance_mm);
 Serial.println(" mm");
 delay(1000); // Wait to do next measurement
}
long Distance(long time)
{
 // Calculates the Distance in mm
 // ((time)*(Speed of sound))/ toward and backward of object)
// distance = duration (microsecond) * 343 (meter/second) / 2
// = duration/1000000 (second) * 343000 (millimeter/second) / 2
 long DistanceCalc; // Calculation variable
DistanceCalc = ((time /2.9154) / 2); // Actual calculation in mm
//DistanceCalc = time / 74 / 2; // Actual calculation in inches
 return DistanceCalc; // return calculated value
}

