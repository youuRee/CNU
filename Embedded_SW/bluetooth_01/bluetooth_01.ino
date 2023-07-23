#include <SoftwareSerial.h>
// Note:
// Not all pins on the Mega and Mega 2560 support change interrupts,
// so only the following can be used for RX:
// 10, 11, 12, 13, 50, 51, 52, 53,
// A8(62), A9(63), A10(64), A11(65), A12(66), A13(67), A14(68), A15(69)
int blueTx=13;
int blueRx=12;
SoftwareSerial mySerial(blueTx, blueRx);
void setup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
 mySerial.begin(9600);
 Serial.println("hello");
}
void loop() {
 // put your main code here, to run repeatedly:
 // Setup your serial monitor with "no line ending"
 // Please use following commands
 // AT : checking the connection
// AT+NAME[your bluetooth device name] :
// setting up the name of your BLE device e.g. AT+NAMEKBKIM
 // AT+PIN[pin number] : setting up the pin number of your BLE device e.g. AT+PIN1234
 if(mySerial.available()){
 Serial.write(mySerial.read());
 }
 if(Serial.available()){
 mySerial.write(Serial.read());
 }
}
