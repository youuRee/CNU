#define ENB 6
#define IN4 7
#define IN3 8
#define BUTTON1 40
#define BUTTON2 42
int state = LOW;
int power = 127;
int val = LOW;
int old_val = LOW;
int val2 = LOW;
int old_val2 = LOW;
void setup() {
 pinMode(IN4, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(ENB, OUTPUT);
 pinMode(BUTTON1, INPUT);
 pinMode(BUTTON2, INPUT);
}
void loop()
{
 button1();
 button2();
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
void button2(){
 val2 = digitalRead(BUTTON2);
 if((val2 == HIGH) && (old_val2 == LOW)){
 power += 64;
 if(power > 256) power = 127;
 }
 old_val2 = val2;
 delay(100);
}
void control_motor(){
 if(state==LOW){
 analogWrite(ENB, state);
 digitalWrite(IN4, state);
 digitalWrite(IN3, state);
 }else{
 analogWrite(ENB, power);
 digitalWrite(IN4, state);
 digitalWrite(IN3, !state);
 }
}
