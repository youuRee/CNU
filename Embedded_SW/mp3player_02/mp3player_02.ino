#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#define dfTx A8
#define dfRx A9
#define busyPIN 30
SoftwareSerial mySoftwareSerial(dfTx, dfRx); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void setup()
{
 mySoftwareSerial.begin(9600);
 Serial.begin(115200);

 Serial.println();
 Serial.println(F("DFRobot DFPlayer Mini Demo"));
 Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

 if (!myDFPlayer.begin(mySoftwareSerial)) { //Use softwareSerial to communicate with mp3.
 Serial.println(F("Unable to begin:"));
 Serial.println(F("1.Please recheck the connection!"));
 Serial.println(F("2.Please insert the SD card!"));
 while(true);
 }
 Serial.println(F("DFPlayer Mini online."));

 myDFPlayer.volume(15); //Set volume value. From 0 to 30
 myDFPlayer.play(1); //Play the first mp3
}
void loop()
{
 boolean play_state = digitalRead(busyPIN);// connect Pin30 to BUSY pin of player
 if(play_state == HIGH){
 myDFPlayer.next();
 }
}
