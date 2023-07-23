// for communicating with esp8266 through Serial Monitor
#include <SoftwareSerial.h>
// Note:
// Not all pins on the Mega and Mega 2560 support change interrupts,
// so only the following can be used for RX:
// 10, 11, 12, 13, 50, 51, 52, 53, A8 (62),
// A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
int wifiTx=11;
int wifiRx=10;
SoftwareSerial mySerial(wifiTx, wifiRx);
unsigned long lastTimeMillis = 0;
int state = 0;
/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send;
* timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug) {
 String response = "";
 mySerial.println(command); // send the read character to the esp8266
 long int time = millis();

 while( (time+timeout) > millis()) {
 while(mySerial.available()) {
 // The esp has data so display its output to the serial window
 char c = mySerial.read(); // read the next character.
 response+=c;
 }
 }

 if(debug) {
 Serial.println(response);
 }
 return response;
}
boolean DEBUG = true;
void setup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
 // At first time, the default baud rate of esp8266 is 115200.
// For clear operation, we are going to rate down the baud rate of esp8266
// to 9600 by using following command
 // AT+CIOBAUD=9600
 // mySerial.begin(115200);
 // Setup your serial monitor with "Both NL & CR"
 mySerial.begin(9600);

 Serial.println("hello");
 delay(1000);
 // ignore following, only if you set up your esp8266 already to connect an AP
sendData("AT+GMR",3000,DEBUG);
sendData("AT+CWJAP=\"SK_WiFi58DA\",\"1501035687\"",10000,DEBUG);
 sendData("AT+CIFSR",4000,DEBUG);

 sendData("AT+CIPMUX=1",4000,DEBUG);
}
void loop() {
 if( millis() - lastTimeMillis > 15000) {
 lastTimeMillis = millis();
 mySerial.println("AT+CIPSTART=4,\"TCP\",\"kyungbaekkim.jnu.ac.kr\",80");
 delay(1000);
 while(mySerial.available()){
 Serial.println(mySerial.readStringUntil('\n'));
 }
 String cmd = "";
 if(state == 0){
 cmd = "GET /data/temp/test1.c";
 state = 1;
 } else {
 cmd = "GET /data/temp/thread.c";
 state = 0;
 }
 mySerial.println("AT+CIPSEND=4,"+String(cmd.length()+4));
 delay(1000);
 mySerial.println(cmd);
 delay(1000);
 mySerial.println("");
 }
 if (mySerial.available()){
 Serial.write(mySerial.read());
 }
}
