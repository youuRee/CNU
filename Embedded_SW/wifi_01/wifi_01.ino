// for communicating with esp8266 through Serial Monitor
#include <SoftwareSerial.h>
// Note:
// Not all pins on the Mega and Mega 2560 support change interrupts,
// so only the following can be used for RX:
// 10, 11, 12, 13, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
int wifiTx = 11;
int wifiRx = 10;
SoftwareSerial mySerial(wifiTx, wifiRx);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // At first time, the default baud rate of esp8266 is 115200.
  // For clear operation, we are going to rate down the baud rate of esp8266 to 9600
  // by using following command
  // AT+CIOBAUD=9600
  // mySerial.begin(115200);
  mySerial.begin(9600);
  Serial.println("hello");
}
/* Try following command
* Setup your serial monitor with "Both NL & CR"
AT : check the communication channel
AT+GMR : check esp8266 firmware version
AT+CWMODE? : check the mode of esp8266 (1 : station or client, 2 : AP or Host, 3 : Station/AP
Dual)
AT+CWMODE=1 : set the mode of esp8266 to client
AT+CWMODE=2 : set the mode of esp8266 to ap
AT+CWLAP : list available APs (output e.g. : +CWLAP:(ecn,ssid,rssi,mac,ch,freq offset,freq
calibration), ecn:0=open,1=wep,2=wpa_psk,3=wpa2_psk,4=wpa_wpa2_psk)
AT+CWJAP="SSID of AP","Password" : connect to AP
AT+CWJAP? : check the connected AP
AT+CIFSR : check the assigned IP address. You can test with ping
AT+CWQAP : disconnects from the AP
AT+CIPMUX = 1 : allow multiple connections
AT+CIPSTART=4,"TCP","www.google.com",80 : create a tcp connection to www.google.com as "4"
AT+CIPSEND=4,18 : Send command with length 18 on the connection "4" (use this command
"GET / HTTP/1.1" )
AT+CIPCLOSE=4 : Close connection "4"
*/
void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
