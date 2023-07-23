#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

enum {
  RIGHT,
  UP ,
  DOWN ,
  SELECT,
  LEFT,
  NONE,
};

// button 의 adc value
int adc_value = 0;
// button value
byte button_value = NONE;

// ADC 를 읽어 button 값 받기
int read_key()
{
	adc_value = analogRead(0);

	if (adc_value < 50)   return RIGHT;
	else if (adc_value < 250)  return UP;
	else if (adc_value < 450)  return DOWN;
	else if (adc_value < 650)  return LEFT;
	else if (adc_value < 850)  return SELECT;
	else return NONE;

}

// 프로그램 초기화
void setup()
{
	Serial.begin(9600); // 시리얼 통신 초기화
	lcd.begin(16, 2);  // 16x2 LCD
	lcd.setCursor(0, 0);   
  lcd.print("Hello World!");
}

// 계속 실행할 무한 루프 
void loop()
{
	button_value = read_key();   // 키 값을 읽음
	lcd.setCursor(0, 1);    // 커서를 2번째줄 맨 앞 칸으로 이동

	// LCD에 키 값을 출력
	switch (button_value)
	{
    // 가장 긴 문자열 길이만큼 띄어쓰기
		case RIGHT:		lcd.print("Right ");	break;
		case LEFT:		lcd.print("Left  ");	break;
		case UP:		lcd.print("Up    ");	break;
		case DOWN:		lcd.print("Down  ");	break;
		case SELECT:	lcd.print("Select");	break;
		//case NONE:		lcd.print("NONE  ");	break;
	}
}
