#define LED 41 // the pin for the LED
#define BUTTON 40 // the input pin where the pushbutton is connected

int val = 0; // val will be used to store the state of the input pin
int old_val = 0; // this variable stores the previous value of "val"
int button_counter = 0;

unsigned long startTime = 0;
unsigned long interval = 200;

void setup() {
  pinMode(LED, OUTPUT); // tell Arduino LED is an output
  pinMode(BUTTON, INPUT); // and BUTTON is an input
  Serial.begin(9600);
}

void loop(){
  val = digitalRead(BUTTON); // read input value and store it yum, fresh
  // check if there was a transition
  if ((val == HIGH) && (old_val == LOW)){
    button_counter++;
    startTime = millis();
    Serial.println(button_counter);
    Serial.println(startTime);
  }
  old_val = val; // val is now old, let's store it
  // 현재 - 과거가 0.2초 보다 크면 if문 실행
  // 그렇지 않으면 if문 실행x -> button_counter 값 그대로 유지ㄴ
  if( startTime + interval < millis() ){
    if (button_counter == 1) {
      digitalWrite(LED, HIGH); // turn LED ON
    } if( button_counter == 2 ){
      digitalWrite(LED, LOW); // turn LED OFF
    }
  button_counter = 0;
  }
}

