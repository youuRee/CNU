// for communicating between bluetooth connected device and serial monitor
// In android, use bluetooth serial controller for testing communication link
// any string ended with "#" entered on bluetooth serial controller is displayed on serial monitor.
#include <SoftwareSerial.h>
// Note:
// Not all pins on the Mega and Mega 2560 support change interrupts,
// so only the following can be used for RX:
// 10, 11, 12, 13, 50, 51, 52, 53,
// A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
int blueTx=13;
int blueRx=12;
SoftwareSerial mySerial(blueTx, blueRx);
String myString ="";
void setup() {
 // put your setup code here, to run once:
 // Setup your serial monitor with "no line ending"
 Serial.begin(9600);
 mySerial.begin(9600);
 Serial.println("hello");
}
void loop() {
 // put your main code here, to run repeatedly:U
 if(mySerial.available()){
 char myChar = (char)mySerial.read();
 if( myChar == '#' ){
 Serial.println("input value: "+myString);
 myString="";
 } else{
 myString+=myChar;
 delay(10);
 }
 }
}
