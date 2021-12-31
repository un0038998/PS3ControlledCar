#include <Ps3Controller.h>

//Right motor
int enableRightMotor=22; 
int rightMotorPin1=16;
int rightMotorPin2=17;
//Left motor
int enableLeftMotor=23;
int leftMotorPin1=18;
int leftMotorPin2=19;

#define MAX_MOTOR_SPEED 200

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int PWMSpeedChannel = 4;



void notify()
{
 int yAxisValue =(Ps3.data.analog.stick.ly);  //Left stick  - y axis - forward/backward car movement
 int xAxisValue =(Ps3.data.analog.stick.rx);  //Right stick - x axis - left/right car movement

  if (yAxisValue <= -50)       //Move car Forward
  {
    rotateMotor(MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  }
  else if (yAxisValue >= 50)   //Move car Backward
  {
    rotateMotor(-MAX_MOTOR_SPEED, -MAX_MOTOR_SPEED);
  }
  else if (xAxisValue >= 50)  //Move car Right
  {
    rotateMotor(-MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  }
  else if (xAxisValue <= -50)   //Move car Left
  {
    rotateMotor(MAX_MOTOR_SPEED, -MAX_MOTOR_SPEED);
  }
  else                                      //Stop the car
  {
    rotateMotor(0, 0);
  } 
}

void onConnect()
{
  Serial.println("Connected!.");
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
  ledcSetup(PWMSpeedChannel, PWMFreq, PWMResolution);
  ledcAttachPin(enableRightMotor, PWMSpeedChannel);
  ledcAttachPin(enableLeftMotor, PWMSpeedChannel);  
  ledcWrite(PWMSpeedChannel, MAX_MOTOR_SPEED);
  
  rotateMotor(0, 0);
}


void setup()
{
  setUpPinModes();
  Serial.begin(115200);
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin();
  Serial.println("Ready.");
}

void loop()
{
}
