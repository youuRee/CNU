#define button 2
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

int melody1[] = {c4, c4, e4, e4, a3, a3, c4, e4, d4, d4, f4, f4, g3, g3, b3, b3, r1}; // 17개
int beats1[] = {22, 10, 22, 10, 22, 10, 24, 8, 22, 10, 22, 10, 22, 10, 22, 10, 16};
int melody2[] = {e4, e4, e4, c4, e4, g4, g3, c4, g3, e3, a3, b3, b3, a3, g3, e4, g4, a4, f4, g4, e4, c4, d4, b3, c3}; // 25개
int beats2[] = {8, 16, 16, 8, 16, 32, 32, 24, 24, 24, 16, 16, 8, 16, 10, 10, 10, 16, 8, 16, 16, 8, 8, 8, 16};

int MAX_MELODY_1 = sizeof(melody1)/2;
int MAX_MELODY_2 = sizeof(melody2)/2;

long tempo = 15000;
int pause = 100;
int tone_ = c4;
int beat = 0;
long duration = 0;


void play_tone() {
  long elapsed_time = 0;
  if(tone_ > 0) {
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
  else {
    delayMicroseconds(duration);
  }
  delay(pause);
}

void setup() {
  pinMode(button, INPUT);
  pinMode(speakerOut, OUTPUT); 

}

int val = 0; 
int old_val = 0; 
int button_counter = 0;
unsigned long startTime = 0;
unsigned long interval = 1000;

void loop() {
  val = digitalRead(button); // read input value and store it yum, fresh
  // check if there was a transition
  if ((val == HIGH) && (old_val == LOW)){
    button_counter++;
    startTime = millis();
  }
  old_val = val; // val is now old, let's store it
  if( startTime + interval < millis() ){
    if (button_counter == 1) {
      for(int i = 0; i < MAX_MELODY_1 ; i++ ) {
        tone_ = melody1[i];
        beat = beats1[i];

        duration = beat * tempo;
        play_tone();
      }
    } 
    if( button_counter == 2 ){
      for(int i = 0; i < MAX_MELODY_2 ; i++ ) {
        tone_ = melody2[i];
        beat = beats2[i];

        duration = beat * tempo;
        play_tone();
      }
    }
    button_counter = 0;
  }

}
