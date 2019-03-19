#include <IRremote.h>

int RECV_PIN = 11;
int fanPin = 5;
int tubeLightPin = 6;
int bulbPin = 7;
boolean fanStatus = LOW;
boolean tubeLightStatus = LOW;
boolean bulbStatus = LOW;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(fanPin, OUTPUT);
  pinMode(tubeLightPin, OUTPUT);
  pinMode(bulbPin, OUTPUT);
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    switch(results.value){
      case 0x1FE50AF: 
         fanStatus = !fanStatus;
         Serial.print("Fan status is ");
         Serial.println(printStatus(fanStatus));
         break;
      case 0x1FED827: 
         tubeLightStatus = !tubeLightStatus;
         Serial.print("Tube-light status is ");
         Serial.println(printStatus(tubeLightStatus));
         break;
      case 0x1FEF807: 
         bulbStatus = !bulbStatus;
         Serial.print("Bulb status is ");
         Serial.println(printStatus(bulbStatus));
         break;
      default:break;
    }
    irrecv.resume(); // Receive the next value
  }
  
  digitalWrite(fanPin,fanStatus);
  digitalWrite(tubeLightPin,tubeLightStatus);
  digitalWrite(bulbPin,bulbStatus);
}

String printStatus(boolean i){
  if(i == 1)
    return "ON";
   else
    return "OFF";
}

