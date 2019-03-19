#include <Event.h>
#include <Timer.h>
#include <ArduinoJson.h>

Timer timer;

int washTime = 0;
int dryTime = 0;
int washTimeRem = 0;
int dryTimeRem = 0;
bool isWashing = false;
bool isDrying  = false;
bool reset  = false;
short int waterLevel = 0;
String incomingString;

const short int washingPin = 5;
const short int dryingPin = 6;

const size_t bufferSizeStatus = JSON_OBJECT_SIZE(7);
DynamicJsonBuffer jsonBufferStatus(bufferSizeStatus);
JsonObject& statusMessage = jsonBufferStatus.createObject();

const size_t bufferSizeCommand = JSON_OBJECT_SIZE(3) + 40;
DynamicJsonBuffer jsonBufferCommand(bufferSizeCommand);
  
void receiveCommand(String incomingString);
void sendStatusMessage(void);

void setup(){
  Serial.begin(9600);
  while(!Serial) continue;
  timer.every(1000, sendStatusMessage);
  timer.every(1000, updateTimer);

  pinMode(washingPin, OUTPUT);
  pinMode(dryingPin, OUTPUT);
  digitalWrite(washingPin, LOW);
  digitalWrite(dryingPin, LOW); 
   
}
  
void loop(){
  timer.update();
  if(Serial.available() > 0){
    incomingString = Serial.readString();
    receiveCommand(incomingString);
    if(reset == true){
      washTime = 0;
      dryTime = 0;
      washTimeRem = 0;
      dryTimeRem = 0;
      isWashing = false;
      isDrying = false;
      reset = false;
    }
  }else{}

  digitalWrite(washingPin, isWashing);
  digitalWrite(dryingPin, isDrying);
}

void sendStatusMessage(void){
  statusMessage["washTime"] = washTime;
  statusMessage["dryTime"] = dryTime;
  statusMessage["isWashing"] = isWashing;
  statusMessage["isDrying"] = isDrying;
  statusMessage["washTimeRem"] = washTimeRem;
  statusMessage["dryTimeRem"] = dryTimeRem;
  statusMessage["waterLevel"] = waterLevel;
 
  //Send Status
  statusMessage.prettyPrintTo(Serial);
}

void receiveCommand(String dataString){
  //receive command
  // message === const char* json = "{\"washTime\":1000,\"dryTime\":200,\"reset\":1}";
  JsonObject& command = jsonBufferCommand.parseObject(dataString);
  
  washTime = command["washTime"]; // 1000
  dryTime = command["dryTime"]; // 200
  reset = (bool) command["reset"]; // 1
  if(!isWashing)
    washTimeRem = washTime;
  if(!isDrying)
    dryTimeRem = dryTime;
}

void updateTimer(void){
  if(washTimeRem <= 0)
    isWashing = false;
  else{ 
    isWashing = true; 
    washTimeRem--;
  }

  if(dryTimeRem <= 0)
    isDrying = false;
  else{ 
    isDrying = true; 
    dryTimeRem--;
  }

}

