#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"
#define dfTx A8
#define dfRx A9
SoftwareSerial mySoftwareSerial(dfTx, dfRx); // RX, TX
// Note:
// Not all pins on the Mega and Mega 2560 support change interrupts,
// so only the following can be used for RX:
// 10, 11, 12, 13, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68),A15 (69)
int blueTx=13;
int blueRx=12;
SoftwareSerial mySerial(blueTx, blueRx);
DFRobotDFPlayerMini myDFPlayer;
String myString ="";
int cmd_ready = 0;
int cmd = 0;
void setup() {
 // put your setup code here, to run once:
 // Setup your serial monitor with "no line ending"
 Serial.begin(9600);
 mySoftwareSerial.begin(9600);
 mySerial.begin(9600);
 Serial.println();
 Serial.println(F("DFRobot DFPlayer Mini Demo"));
 Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
 mySoftwareSerial.listen();
 if (!myDFPlayer.begin(mySoftwareSerial)) { //Use softwareSerial to communicate with mp3.
 Serial.println(F("Unable to begin:"));
 Serial.println(F("1.Please recheck the connection!"));
 Serial.println(F("2.Please insert the SD card!"));
 while(true);
 }
 Serial.println(F("DFPlayer Mini online."));
 myDFPlayer.volume(15); //Set volume value. From 0 to 30
}
void loop() {
 // put your main code here, to run repeatedly:
 mySerial.listen();
 if(mySerial.available()){
 char myChar = (char)mySerial.read();
 if( myChar == '#' ){
 Serial.println("input value: "+myString);
 if( myString == "nt" ){
 Serial.println("nt!!");
 cmd = 0;
 }
 else if( myString == "pr"){
 Serial.println("pr!!");
 cmd = 1;
 }
 else if( myString == "vu"){
 Serial.println("vu!!");
 cmd = 2;
 }
 else if( myString == "vd" ){
 Serial.println("vd!!");
 cmd = 3;
 }
 else if( myString == "p" ){
 Serial.println("p!!");
 cmd = 4;
 }
 else if( myString == "s" ){
 Serial.println("s!!");
 cmd = 5;
 }
 cmd_ready = 1;
 myString="";
 } else{
 myString+=myChar;
 delay(10);
 }
 }
 if(cmd_ready == 1){
 mySoftwareSerial.listen();

 if(cmd == 0 ){
 Serial.println("next!!");
 myDFPlayer.next();
 }
 else if( cmd == 1){
 Serial.println("prev!!");
 myDFPlayer.previous();
 }
 else if( cmd == 2){
 Serial.println("vol_up!!");
 myDFPlayer.volumeUp();
 }
 else if( cmd == 3){
 Serial.println("vol_down!!");
 myDFPlayer.volumeDown();
 }
 else if( cmd == 4){
 Serial.println("paused!!");
 myDFPlayer.pause();
 }
 else if( cmd == 5){
 Serial.println("start!!");
 myDFPlayer.start();
 }

 cmd_ready = 0;
 }
}
