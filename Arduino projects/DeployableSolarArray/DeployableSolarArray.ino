#include<Servo.h>
String payload;
uint8_t angle = 0;
int fullSwing = 90;
uint8_t ledPin = 13;
int stepTime = 200;
unsigned long angleTime = 0;
unsigned long ledTime = 0;
int blinkTime = 200;
bool pause = false;

Servo servo1;
Servo servo2;
Servo servo3;

enum Mode{
  DEPLOY,
  RETRACT,
  IDL
};

Mode mode = IDL;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(9);
  servo2.attach(8);
  servo3.attach(7);
  setPosition(0);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, HIGH);
  Serial.begin(9600);
  Serial.println("Initializing...");
  Serial.println("Full Swing angle: " + String(fullSwing) + " deg");
  Serial.println("Step time per degree: " + String(stepTime) + " ms/deg");
  Serial.println("Angular velocity: " + String(1000.0/stepTime) + " deg/s");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    payload = Serial.readString();
    char command = payload[0];
    payload.remove(0,1);
    switch(command){
      case 'd':
      case 'D':
        Serial.println("Starting Deployment....");
        mode = DEPLOY;
        //Serial.println("Deployment Complete.");
        break;
      case 'r':
      case 'R':
        Serial.println("Starting Retraction....");
        mode = RETRACT;
        //Serial.println("Retraction Complete.");
        break;
     case 'F':
     case 'f':
        Serial.println("Setting full swing angle(deg) to " + payload);
        fullSwing = payload.toInt();
        break;
     case 'T':
     case 't':
        Serial.println("Setting step time(ms) to " + payload);
        stepTime = payload.toInt();
        break;
     case 'W':
     case 'w':
        Serial.println("Setting angular velocity(deg/s) to " + payload);
        stepTime = (int) (1000 / payload.toInt());
        break;
     case 'P':
     case 'p':
        if(pause){
          Serial.println("Continuing (unpausing) the process...");
          pause = false;
        }else{
          Serial.println("Pausing the process...");
          pause = true;
        }
        break;
      default:
        Serial.print("Send 'd' to deploy,'r' to retract.");
        break;
   
    }
  }

  switch(mode){
    case DEPLOY:
      deploy();
      blinkLED();
      break;
    case RETRACT:
      retract();
      blinkLED();
      break;
    case IDL:
      digitalWrite(ledPin, HIGH);
      break;
  }
}

void setPosition(int pos){
  servo1.write(pos);
  servo2.write(pos);
  servo3.write(pos);
}

void deploy(){
  unsigned long currentTime = millis();
  if(!pause){
    if(((currentTime - angleTime)> stepTime) && (angle<fullSwing)){
      setPosition(angle++);
      Serial.println(angle);
      angleTime = currentTime;
    }
  }
  if(angle >= fullSwing){
    mode = IDL;
    Serial.println("Deployment Complete.");
  } 
}

void retract(){
  unsigned long currentTime = millis();
  if(!pause){
    if((currentTime - angleTime) > (stepTime) && (angle>0)){
      setPosition(angle--);
      Serial.println(angle);
      angleTime = currentTime;
    }
  }
  if(angle <= 1){
    mode = IDL;
    Serial.println("Retraction Complete.");
  } 
}

void blinkLED(){
  unsigned long currentTime = millis();
  if((currentTime - ledTime) > blinkTime){
    digitalWrite(ledPin, !digitalRead(ledPin));
    ledTime = currentTime;
  }
}

