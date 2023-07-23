#define ENB 6
#define IN4 7
#define IN3 8
#define BUTTON1 40
int state = LOW;
int val = LOW;
int old_val = LOW;
void setup() {
 pinMode(IN4, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(ENB, OUTPUT);
 pinMode(BUTTON1, INPUT);
}
void loop()
{
 button1();
 control_motor();
}
void button1(){
 val = digitalRead(BUTTON1);
 if((val == HIGH) && (old_val == LOW)){
 state = !state;
 }
 old_val = val;
 delay(100);
}
void control_motor(){
 if(state==LOW){
 digitalWrite(ENB, state);
 digitalWrite(IN4, state);
 digitalWrite(IN3, state);
 }else{
 digitalWrite(ENB, state);
 digitalWrite(IN4, state);
 digitalWrite(IN3, !state);
 }
}

