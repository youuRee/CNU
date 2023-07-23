
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

int melody[] = {e4, e4, e4, c4, e4, g4, g3, c4, g3, e3, a3, b3, b3, a3, g3, e4, g4, a4, f4, g4, e4, c4, d4, b3, c3}; // 25개
int beats[] = {8, 16, 16, 8, 16, 32, 32, 24, 24, 24, 16, 16, 8, 16, 10, 10, 10, 16, 8, 16, 16, 8, 8, 8, 16};

int MAX_MELODY = sizeof(melody)/2;

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
  Serial.begin(9600);

}

int bval, lval;

void loop() {
  bval = digitalRead(button);

  if (bval == HIGH) {
    for (int j = 0; j < 5; j ++) {
      for(int i = 0; i < MAX_MELODY ; i++) {
      tone_ = melody[i];
      beat = beats[i];
      lval = analogRead(0);
      // tempo = lval * 10;

      Serial.print("light senser = ");
      Serial.println(lval);
      Serial.print("tempo = ");
      Serial.println(tempo);

      if (lval > 370) {
        tempo = 10000;
      }
      else if (lval > 350) {
        tempo = 15000;
      }
      else {
        tempo = 20000;
      }
    
      duration = beat * tempo;
      play_tone();
      }
    }
    
  }
  
  else {
    delay(100);
  }

}
