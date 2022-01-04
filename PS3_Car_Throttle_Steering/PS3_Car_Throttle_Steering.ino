#include <Ps3Controller.h>

//Right motor
int enableRightMotor=22; 
int rightMotorPin1=16;
int rightMotorPin2=17;
//Left motor
int enableLeftMotor=23;
int leftMotorPin1=18;
int leftMotorPin2=19;

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

void notify()
{
  int yAxisValue =(Ps3.data.analog.stick.ly);  //Left stick  - y axis - forward/backward car movement
  int xAxisValue =(Ps3.data.analog.stick.rx);  //Right stick - x axis - left/right car movement

  int throttle = map( yAxisValue, 127, -127, -255, 255);
  int steering = map( xAxisValue, -127, 127, -255, 255);  
  int motorDirection = 1;
  
  if (throttle < 0)       //Move car backward
  {
    motorDirection = -1;    
  }

  int rightMotorSpeed, leftMotorSpeed;
  rightMotorSpeed =  abs(throttle) - steering;
  leftMotorSpeed =  abs(throttle) + steering;
  rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);
  leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);

  //Serial.println(rightMotorSpeed);
  //Serial.println(leftMotorSpeed);  
  rotateMotor(rightMotorSpeed * motorDirection, leftMotorSpeed * motorDirection);

}

void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  rotateMotor(0, 0);
  Serial.println("Disconnected!.");    
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }
  
  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  } 
  ledcWrite(rightMotorPWMSpeedChannel, abs(rightMotorSpeed));
  ledcWrite(leftMotorPWMSpeedChannel, abs(leftMotorSpeed));   
}

void setUpPinModes()
{
  pinMode(enableRightMotor,OUTPUT);
  pinMode(rightMotorPin1,OUTPUT);
  pinMode(rightMotorPin2,OUTPUT);
  
  pinMode(enableLeftMotor,OUTPUT);
  pinMode(leftMotorPin1,OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);

  //Set up PWM for motor speed
  ledcSetup(rightMotorPWMSpeedChannel, PWMFreq, PWMResolution);
  ledcSetup(leftMotorPWMSpeedChannel, PWMFreq, PWMResolution);  
  ledcAttachPin(enableRightMotor, rightMotorPWMSpeedChannel);
  ledcAttachPin(enableLeftMotor, leftMotorPWMSpeedChannel);  
  
  rotateMotor(0, 0);
}


void setup()
{
  setUpPinModes();
  Serial.begin(115200);
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.attachOnDisconnect(onDisConnect);
  Ps3.begin();
  Serial.println("Ready.");
}

void loop()
{
}
