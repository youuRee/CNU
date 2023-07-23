#define LEDa 2 // analog out
#define LED 40 // the pin for the LED
#define BUTTON 48 // input pin of the pushbutton
#define MAX_COUNT 4
int val = 0; // stores the state of the input pin
int old_val = 0; // stores the previous value of "val"
int state = 0;
int brightness = 0; // Stores the brightness value
int period = 2000;
void setup() {
 pinMode(LEDa, OUTPUT); // tell Arduino LED is an output
 pinMode(LED, OUTPUT); // tell Arduino LED is an output
 pinMode(BUTTON, INPUT); // and BUTTON is an input
}
void ledOn(int duty){
 float tmp = (float)period * (float)duty / (float)100;

 if( tmp == 0 ){
 digitalWrite(LED, LOW);
 } else {
 digitalWrite(LED, HIGH);
 delayMicroseconds((int)tmp);
 digitalWrite(LED, LOW);
 delayMicroseconds(period - (int)tmp);
 }
}
void loop() {
 val = digitalRead(BUTTON); // read input value and store it yum, fresh check if there was a transition
 if ((val == HIGH) && (old_val == LOW)) {
 state++;
 if( state >= MAX_COUNT ) state = 0;
 delay(10);
 }
 old_val = val;
 if( state == 0 ){
 ledOn(0);
 brightness = 0;
 } else if( state == 1 ){
 ledOn(50);
 brightness = 70;
 } else if( state == 2 ){
 ledOn(150);
 brightness = 140;
 } else if( state == 3 ){
 ledOn(100);
 brightness = 255;
 }
}
