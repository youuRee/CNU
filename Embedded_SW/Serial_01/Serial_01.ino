#define LED1 49
#define LED2 48
#define speakerOut 47
#define c3 7692 // 130 Hz
#define d3 6802 // 147 Hz
#define e3 6060 // 165 Hz
#define f3 5714 // 175 Hz
#define g3 5102 // 196 Hz
#define a3 4545 // 220 Hz
#define b3 4048 // 247 Hz
#define c4 3830 // 261 Hz
#define d4 3400 // 294 Hz
#define e4 3038 // 329 Hz
#define f4 2864 // 349 Hz
#define g4 2550 // 392 Hz
#define a4 2272 // 440 Hz
#define b4 2028 // 493 Hz
#define c5 1912 // 523 Hz
#define r1 0
int melody[] = {c4, c4, e4, e4, a3, a3, c4, e4, d4, d4, f4, f4, g3, g3, b3, b3, r1};
int beats[] = {22, 10, 22, 10, 22, 10, 24, 8, 22, 10, 22, 10, 22, 10, 22, 10, 16};
int MAX_MELODY = sizeof(melody)/2;
long tempo = 15000;
int pause = 10;
int tone_ = c4;
int beat = 0;
long duration = 0;
volatile unsigned long last_int_time = 0;
volatile unsigned long int_time;
volatile unsigned long last_int2_time = 0;
volatile unsigned long int2_time;
volatile int debounceGuard = 500;
volatile int state = LOW;
int d = 1000;
void setup(){
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);

 pinMode(speakerOut,OUTPUT);

 attachInterrupt(0, ledToggle, RISING);

 Serial.begin(9600);
}
void loop(){
 led2Blink();
 readSerial();
}
void led2Blink(){
 digitalWrite(LED2, HIGH);
 delay(d);
 digitalWrite(LED2, LOW);
 delay(d);
}
void readSerial(){
 if( Serial.available() > 0 ){
 int cmd = Serial.read();
 Serial.print("reading :");
 Serial.println(cmd);

 if( cmd == '1' ){
 Serial.println("Blinking period changes to 1000ms");
 d = 500;
 }
 else if( cmd == '2' ){
 Serial.println("Blinking period changes to 600ms");
 d = 300;
 }
 else if( cmd == '3' ){
 Serial.println("Blinking period changes to 200ms");
 d = 100;
 }
 else{
 Serial.println("Blinking period changes to 2000ms");
 d = 1000;
 }
 }
}
void ledToggle(){
 int_time = millis();
 if( int_time - last_int_time > debounceGuard ){
 int lval = analogRead(0);
 Serial.print("Light Sensor Reading : ");
 Serial.println(lval);

 state = !state;
 digitalWrite(LED1,state);
 if( state == HIGH ){
 Serial.println("Ready to play Music.");
 attachInterrupt(1, playMusic, RISING);
 }
 else{
 Serial.println("Not ready to play Music.");
 detachInterrupt(1);
 }
 last_int_time = int_time;
 }
}
void play_tone(){
 long elapsed_time = 0;
 if( tone_ > 0 ){
 while( elapsed_time < duration ){
 if( elapsed_time + tone_ <= duration ){
 digitalWrite(speakerOut,HIGH);
 delayMicroseconds(tone_ / 2);
 digitalWrite(speakerOut,LOW);
 delayMicroseconds(tone_ / 2);
 }
 elapsed_time += tone_;
 }
 }
 else{
 delayMicroseconds(duration);
 }
 delay(pause);
}
void playMusic(){
 int2_time = millis();
 if( int2_time - last_int2_time > debounceGuard ){
 for(int i = 0; i < MAX_MELODY ; i++ ){
 tone_ = melody[i];
 beat = beats[i];

 duration = beat * tempo;
 play_tone();
 }
 Serial.println("Music Played.");
 last_int2_time = int2_time;
 }
}

