#include "telegraph.h"
#define LED1 30
const unsigned int DIT_LENGTH = 100;
Telegraph telegraph(LED1, DIT_LENGTH );
const byte COMMAND_1 = 0x1;
const byte COMMAND_2 = 0x2;
byte rcvmsg[3];
unsigned int n_repeat;
void setup(){
 pinMode(LED1, OUTPUT);
 Serial.begin(9600);
}
void loop(){
 if( Serial.available() > 0 ){
 int len = Serial.readBytes(rcvmsg, sizeof(rcvmsg));
 if( len > 0 ){
 n_repeat = rcvmsg[1];
 if(rcvmsg[0] == COMMAND_1){
 for( int i = 0; i < n_repeat ; i++ ){
 telegraph.send_message("HI");
 }
 }
 else if(rcvmsg[0] == COMMAND_2){
 for( int i = 0; i < n_repeat ; i++ ){
 telegraph.send_message("SOS");
 }
 }
 Serial.println("");
 }
 }
}
 
