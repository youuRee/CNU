/*
A 버튼 : LED2의 점멸 주기 변경, 점멸 주기를 변경할 준비가 되면 LED1이 켜짐
B 버튼 : LED2의 깜박임 주기를 변경, 누를 때마다 2000ms -> 1000ms -> 600ms -> 200ms 순으로 점멸 주기 변경
B 버튼은 A 버튼을 눌렀을 때만 작동

-> A 버튼을 누르면 LED1 불이 켜지면서 LED2의 점멸 주기 변하는걸 준비
  그 후, B 버튼을 누를때마다 LED2의 점멸 주기 속도를 변경
*/

#define button_1 2
#define button_2 3
#define led_1 49
#define led_2 48

volatile unsigned long last_int_time = 0; 
volatile unsigned long int_time;
volatile unsigned long last_int2_time = 0; 
volatile unsigned long int2_time;
volatile int debounceGuard = 500; 
volatile int state = LOW;
int d = 2000;
int cnt = 0;

void setup()
{
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  
  // 0번 인터럽트 : 2번 pin에 Low->High (RISING)로 바뀌면 인터럽트 발생 (ledToggle 실행)
  attachInterrupt(0, ledToggle, RISING);
}

void loop()
{
  led2Blink();
}

void led2Blink(){ 
  digitalWrite(led_2, HIGH);
  delay(d);
  digitalWrite(led_2, LOW);
  delay(d);
}

void ledToggle(){
  int_time = millis();
  if( int_time - last_int_time > debounceGuard ){
    state = !state;
	digitalWrite(led_1,state);
    if( state == HIGH ){
      // 1번 인터럽트 : 3번 pin에 Low->High or High->Low (FALLING)로 상태 바뀌면 인터럽트 발생
      attachInterrupt(1, changeBlink, RISING);
	  }
    else{
      detachInterrupt(1);
    }
    last_int_time = int_time;
  }
}

void changeBlink(){
  cnt += 1;
  // cnt가 1이면 아직 인터럽트 1번 걸린 것
  if (cnt == 1){
    d = 1000;
  }
  else if (cnt == 2){
    d = 600;
  }
  else if (cnt == 3){
    d = 200;
  }
  else{
    d = 2000;
    cnt = 0;
  }
}
