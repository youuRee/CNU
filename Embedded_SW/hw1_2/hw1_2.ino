#define L1 49 
#define L2 47
#define L3 3 
#define A_BUTTON 48 
#define B_BUTTON 46

int val_A = 0;
int val_B = 0;

void setup() {
 pinMode(L1, OUTPUT);
 pinMode(L2, OUTPUT); 
 pinMode(L3, OUTPUT);
 pinMode(A_BUTTON, INPUT);
 pinMode(B_BUTTON, INPUT); 
}
void loop(){
 val_A = digitalRead(A_BUTTON);
 val_B = digitalRead(B_BUTTON); 

  if (val_A == HIGH && val_B == HIGH) {
    digitalWrite(L3, HIGH);
    digitalWrite(L1, LOW); 
    digitalWrite(L2, LOW);
  } 
  else {
    digitalWrite(L3, LOW);
    if (val_A == HIGH) {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
    } 
    else if (val_B == HIGH) {
      digitalWrite(L2, HIGH);
      digitalWrite(L1, LOW);
    }
    else {
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
    }
  }
}

