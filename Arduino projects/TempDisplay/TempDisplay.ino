#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
short int temp;
byte DegC[8]={0b11000,0b11000,0b00111,0b00100,0b00100,0b00100,0b00111,0b00000};
byte DegF[8]={0b11000,0b11000,0b00111,0b00100,0b00110,0b00100,0b00100,0b00000};
void setup() {
  lcd.begin(16,2);
  // put your setup code here, to run once:
lcd.createChar(0,DegC);
lcd.createChar(1,DegF);
lcd.setCursor(5,0);
lcd.print("Hello!");
delay(1500);
lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
temp=analogRead(5)/2-2;
lcd.setCursor(0,0);
lcd.print("Room Temperature");
lcd.setCursor(0,1);
lcd.print(temp+273);
lcd.print("K");
lcd.setCursor(7,1);
lcd.print(temp);
lcd.write(byte (0));
lcd.setCursor(12,1);
lcd.print((temp)*9/5+32);
lcd.write(byte (1));
delay(3000);
lcd.clear();
}
