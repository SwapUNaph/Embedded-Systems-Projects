//Author: Swapneel Naphade
//Dynamometer datalogger for time period of rotation.
/* Connections:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 */
 #include<SPI.h>
 #include<SD.h>
 void sd_error(uint8_t);
 const uint8_t sensor_pin=8;
 const uint8_t error_pin=9;
 const uint8_t chip_select=4;
 int start_time=0;
 int rot_time=0;
 int count=0;
 File dynoFile;
 
void setup() {
pinMode(error_pin,OUTPUT);
pinMode(sensor_pin,INPUT);
if(!SD.begin(chip_select))
  sd_error(1);
else sd_error(0);

if(SD.exists("dynoData.txt"))
    SD.remove("dynoData.txt");
else dynoFile=SD.open("dynoData.txt");
dynoFile.close();
start_time=millis()+25;
}

void loop() {
String time_string="";
rot_time=start_time-millis();
if(digitalRead(sensor_pin)==LOW)
  count++;

  if(count>10)
  {
    start_time=millis();
    count=0;
    time_string += String(rot_time);
    time_string += ',';
    dynoFile=SD.open("dynoData.txt",FILE_WRITE);
    if(dynoFile)
    {
      dynoFile.println(time_string);
      dynoFile.close();
    }
   }

}

void sd_error(uint8_t code)
{
  if(code==1)
  digitalWrite(error_pin,HIGH);
  else digitalWrite(error_pin,LOW);
}


