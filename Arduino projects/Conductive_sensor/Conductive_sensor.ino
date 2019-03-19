#include "Wire.h"
byte inputA=0;
byte inputB=0;
boolean level[10];
void setup()
{
 Serial.begin(9600);
 Wire.begin(); // wake up I2C bus
}
void loop()
{
 Wire.beginTransmission(32);
 Wire.write(0x12); // set MCP23017 memory pointer to GPIOA address
 Wire.endTransmission();
 Wire.requestFrom(0x20, 1); // request one byte of data from MCP20317
 inputA=Wire.read(); // store the incoming byte into "inputs"
 Wire.beginTransmission(32);
  
 Wire.write(0x13); // set MCP23017 memory pointer to GPIOB address
 Wire.endTransmission();
 Wire.requestFrom(0x20, 1); // request one byte of data from MCP20317
 inputB=Wire.read(); // store the incoming byte into "inputs"
// Serial.println(inputA, BIN); // display the contents of the GPIOA register in binary
 //Serial.println(inputB, BIN); // display the contents of the GPIOB register in binary
 delay(500);
 
level[9]=inputB & 0b00000010;
level[8]=inputB & 0b00000001;
for(byte i=0; i<8; i++){
  level[i]= inputA & (1<<i);
}
//for(int i=0; i<10; i++){
//  Serial.println(level[i]);
//}
int height=-3;
for(int i=9; i>=0; i--){
  Serial.print(level[i]);
  if(level[i]==0)
    height+=3;
}
Serial.print("\t\t");
Serial.println(height);
}
