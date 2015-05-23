#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  
 
#define I2C_ADDR    0x3F  
#define  LED_OFF  0
#define  LED_ON  1
LiquidCrystal_I2C lcd(I2C_ADDR, 4, 5, 6, 0, 1, 2, 3, 7, NEGATIVE);
const int  startButton = 2;
const int  pauseButton = 3;
const int  resumeButton = 4;
const int  resetButton = 5;
bool startScreen = true; 
int seconds = 0;
int minutes = 0;
char buf[50];
  
void setup()   
{
  lcd.begin (16,2);  
  lcd.setBacklight(LED_ON);
  pinMode(startButton, INPUT);
  pinMode(pauseButton, INPUT);
  Serial.begin(9600);
}
 
void loop()
{
  if(startScreen){
    lcd.setCursor(0,0);
    lcd.print("00:00");
    lcd.setCursor(0,1);
    lcd.print("str pas res rest");
    startScreen = false;
  }
  if((digitalRead(startButton)) == HIGH) startTimer();   
}

int startTimer(){
  startScreen = true;
  lcd.setCursor(0,0);
  minutes = 0;
  seconds = 0;
  while(1){
    if((digitalRead(pauseButton)) == HIGH){
      while(1){
        if((digitalRead(resumeButton)) == HIGH) break;
        if((digitalRead(resetButton)) == HIGH) return 0;  
      }
    }
    if((digitalRead(resetButton)) == HIGH)return 0;    
    lcd.clear();  
    lcd.setCursor(0,0);    
    sprintf(buf, "%0.2d:%0.2d",minutes, seconds);
    lcd.print(buf);
    lcd.setCursor(0,1);
    lcd.print("str pas res rest");
    seconds++;
    delay(1000);      
    if(seconds == 59){
      minutes++;
      seconds = 0;
    }     
  }
}
