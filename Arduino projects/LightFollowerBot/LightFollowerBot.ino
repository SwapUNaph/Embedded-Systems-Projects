boolean LEFT=0;
boolean RIGHT=1;
boolean BACKWARD=0;
boolean FORWARD=1;
#define TPR 220  //time(ms) per rotation of the bot
//Configure motor
uint8_t leftMotorHigh=9;
uint8_t leftMotorLow=10;
uint8_t rightMotorHigh=11;
uint8_t rightMotorLow=12;

//Configure sensors
uint8_t leftSensor=A2;
uint8_t rightSensor=A3;
uint8_t rearSensor=A0;
int leftSensorReading=0;
int rightSensorReading=0;
//int rearSensorReading=0;
//uint8_t lowCalibLeft=300;
//uint8_t lowCalibRight=300;
//int highCalibLeft=1000;
//int highCalibRight=1000;
//int leftSensorReading=0;
//int rightSensorReading=0;

//configure led and button
//uint8_t ledPin=9;


void rotateBot(int theta){
  if(theta>=0){
    rotateMotor(LEFT,BACKWARD);
    rotateMotor(RIGHT,FORWARD);
  }
  else {
    rotateMotor(RIGHT,BACKWARD);
    rotateMotor(LEFT,FORWARD); 
  }
  delay(abs(theta)*TPR/360);
  stopBot();  //Brake 
}

void moveBot(boolean dir, int duration){
    rotateMotor(LEFT,dir);
    rotateMotor(RIGHT,dir);
    delay(duration);
    stopBot(); //Brake 
}

void rotateMotor(uint8_t num, boolean dir){
  if(num==LEFT){
      digitalWrite(leftMotorHigh,dir);
      digitalWrite(leftMotorLow,!dir);
  }
  else if(num==RIGHT){
      digitalWrite(rightMotorHigh,dir);
      digitalWrite(rightMotorLow,!dir);
  }
 }

 void stopBot(void){
      digitalWrite(rightMotorHigh,0);
      digitalWrite(rightMotorLow,0);
      digitalWrite(leftMotorHigh,0);
      digitalWrite(leftMotorLow,0);
  }


void mapSensorValues(void){
  leftSensorReading = analogRead(leftSensor);
  rightSensorReading = analogRead(rightSensor);
  //rearSensorReading = analogRead(rearSensor);
 // leftSensorReading = map(leftSensorReading, lowCalibLeft,highCalibLeft,0,100);
 // rightSensorReading = map(rightSensorReading, lowCalibRight,highCalibRight,0,100);
}
//int getAngle(void){
//  mapSensorValues();
//  int threshold=300;
//  int theta=90;
//  if(leftSensorReading>threshold && rightSensorReading>threshold){
//     theta=90*leftSensorReading/(leftSensorReading+rightSensorReading)-45;
//  }
//  else theta=90;
//  return theta;
//}


void setup() {
  // put your setup code here, to run once:
  pinMode(leftMotorHigh,OUTPUT);
  pinMode(leftMotorLow,OUTPUT);
  pinMode(rightMotorHigh,OUTPUT);
  pinMode(rightMotorLow,OUTPUT);  
  pinMode(leftSensor,INPUT);
  pinMode(rightSensor,INPUT);
  stopBot();
}

void loop() {
  // put your main code here, to run repeatedly:
  float ratio;
  mapSensorValues();
  ratio=leftSensorReading/rightSensorReading;
  if(leftSensorReading<50 && rightSensorReading<50)
    rotateBot(60);
  //else if(leftSensorReading<50 && rightSensorReading<50 && rearSensorReading>50)  
   // rotateBot(100);
  else if(ratio>1)
    rotateBot(15);
  else if(ratio<0.3)
    rotateBot(-15);
  else if(ratio>5) 
    rotateBot(30);
  else if(ratio<0.01)
    rotateBot(-30);
  else 
    moveBot(FORWARD,200);
  delay(250);

}


