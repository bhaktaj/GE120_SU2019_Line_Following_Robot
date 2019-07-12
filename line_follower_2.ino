/*********************************************************************
 * 
 * Module name: line_follower_2.ino (replace with the actual fie name)          
 *
 * This software is copyrighted by and is the sole property of
 * (your name).  All rights, title, ownership, or other interests
 * in the software remain the property of (your name) .  This
 * software may only be used in accordance with the corresponding
 * license agreement.  Any unauthorized use, duplication, transmission,
 * distribution, or disclosure of this software is expressly forbidden.
 *
 * This Copyright notice may not be removed or modified without prior
 * written consent of (your name).
 *
 * (your name) reserves the right to modify this software without notice.
 *
 * Author: (your name)
 *
 * Created on July 10th, 2019
 * 
 *
 * Version 1.0: 
 *                  a) First version of code for line following robot to 
 *                  meet the specifications defined for the assignment
 *                  
 ************************************************************************/

/************************************************************************
* Arduino Hardware Connections
*************************************************************************/

/*connections to Dual TB6612FNG motor controller*/
const int PWMA=3; /*pulse width modulation for motor A*/
const int AI1=4; /*control input A1 for motor controller board */
const int AI2=5; /*control input A2 for motor controller board */
const int PWMB=6;
const int BI1=7;
const int BI2=8;

/*built in LED*/
const int BUILT_IN_LED=13;

/*digital inputs*/
const int START_BUTTON=9;
const int BUMPER=10;

/*analog input channels*/
const int LEFT_LIGHT_SENSOR=0;
const int RIGHT_LIGHT_SENSOR=1;


/************************************************************************
* GLOBAL CONSTANTS
*************************************************************************/
const int SPEED=100; //0 min, 255 max speed. PWM duty cycle for the motors
const int SPEED_TURNING_INSIDE=50; //speed of the inside wheel during a turn


/************************************************************************
* FUNCTION PROTOTYPES
*************************************************************************/
void stopMotors();
void moveForward();
void moveBackwards();
void steerLeft();
void testMotors();
void testSensors();
void waitForStartButtonPress();
int rightSensorOnTrack();
int leftSensorOnTrack();


/************************************************************************
* SETUP FUNCTION
*************************************************************************/
void setup() {
  
  /*setup serial port for debugging*/
  Serial.begin(9600);
  
  /*configuring digital IO pins*/
  pinMode(PWMA,OUTPUT);
  pinMode(AI1,OUTPUT);
  pinMode(AI2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(BI1,OUTPUT);
  pinMode(BI2,OUTPUT);
  pinMode(START_BUTTON,INPUT);
  pinMode(BUMPER,OUTPUT);
  pinMode(BUILT_IN_LED,OUTPUT);

  /*test motors by running them back and forth*/
  testMotors();

  /*test the reflectance sensors*/
  testSensors();

  /*turn on the built in LED*/

  
  /*wait for the button to be pressed*/
  waitForStartButtonPress();
  
}


/************************************************************************
* MAIN LOOP
*************************************************************************/
void loop() {
  
  moveForward();

  /*test if the bumper has been pressed*/
  if(!digitalRead(BUMPER)){
    Serial.println("Bumper pressed");
    stopMotors();
    waitForStartButtonPress();   
  }
  
  /* test if we have encountered a station*/
  if(leftSensorOnTrack() && rightSensorOnTrack()){
    Serial.println("Reached Station");
    stopMotors();
    waitForStartButtonPress();
  } 
  else {

    /*test if the left sensor is on the track*/
    if(leftSensorOnTrack()){
      steerLeft();
    }

    if(rightSensorOnTrack()){
      steerRight();
    }
  }  
}


/*************************************************************************
* Function name      : stopMotors()
* returns            : void
* Description        : stops both motors without applying brake
* Notes              : 
**************************************************************************/
void stopMotors(){
  /*turn off left motor*/
  digitalWrite(AI1,LOW);
  digitalWrite(AI2,LOW);

  /*turn off the right motor*/
  digitalWrite(BI1,LOW);
  digitalWrite(BI2,LOW);

  Serial.println("motors stopped");
 }


/*************************************************************************
* Function name      : moveForward()
* returns            : void
* Description        : Moves the robot in the forward direction
* Notes              : The speed of the motors is set by the SPEED global 
*                      variable
**************************************************************************/
void moveForward(){
  /*left motor forward*/
  analogWrite(PWMA,SPEED);
  digitalWrite(AI1,HIGH);
  digitalWrite(AI2,LOW);

  /*right motor forward*/
  analogWrite(PWMB,SPEED);
  digitalWrite(BI1,HIGH);
  digitalWrite(BI2,LOW);

  Serial.println("moving forward");
}

/*************************************************************************
* Function name      : moveBackwards()
* returns            : void
* Description        : Moves the robot in the backward direction
* Notes              : The speed of the motors is set by the SPEED global 
*                      variable
**************************************************************************/
void moveBackwards(){
  //put your code to move the robot backwards here   
}  
  
/*************************************************************************
* Function name      : steerLeft()
* returns            : void
* Description        : Steers the robot to the left by slowing the wheel
*                       on the inside of the turn to SPEED_TURNING_INSIDE
* Notes              : 
**************************************************************************/
void steerLeft(){
  /*slow the left motor*/
  analogWrite(PWMA,SPEED_TURNING_INSIDE);
  digitalWrite(AI1,HIGH);
  digitalWrite(AI2,LOW);

  /*right motor forward*/
  analogWrite(PWMB,SPEED);
  digitalWrite(BI1,HIGH);
  digitalWrite(BI2,LOW);

  Serial.println("steering left"); 
}

/*************************************************************************
* Function name      : steerRight()
* returns            : void
* Description        : Steers the robot to the right by slowing the wheel
*                       on the inside of the turn to SPEED_TURNING_INSIDE
* Notes              : 
**************************************************************************/
void steerRight(){

  //put your code to steer the robot to the right here
}

/*************************************************************************
* Function name      : testMotors()
* returns            : void
* Description        : Runs the motors back and forth for the self test routine
* Notes              : 
**************************************************************************/
void testMotors(){
  /*run both motors forward for 2 seconds*/

  /*run both motors in reverse for 2 seconds*/
  
}

/*************************************************************************
* Function name      : testSensors()
* returns            : void
* Description        : Tests if the reflectance sensors are producing values
*                       within acceptable limits
* Notes              : 
**************************************************************************/
void testSensors(){

  int rightSensorFault;
  int leftSensorFault;
  
 
  /* test the right sensor*/
  rightSensorFault=(analogRead(RIGHT_LIGHT_SENSOR)>1000 || analogRead(RIGHT_LIGHT_SENSOR)<50); 

  if(rightSensorFault){
    Serial.println("Right reflectance sensor faulty");
  }

  /*test the left sensor*/
  leftSensorFault=(analogRead(LEFT_LIGHT_SENSOR)>1000 || analogRead(LEFT_LIGHT_SENSOR)<50);  

  if(leftSensorFault){
    Serial.println("left reflectance sensor faulty");
  }

  if(rightSensorFault || leftSensorFault){
    /* enter infinite loop and flash the built-in-led twice per second */
    while(1){
      //write your code to flash the led here
    }    
  }
}


/*************************************************************************
* Function name      : waitForStartButtonPress()
* returns            : void
* Description        : waits until the start button is pressed
* Notes              : 
**************************************************************************/
void waitForStartButtonPress(){
  //write code to wait until the start button is pressed before continuing
  
}

/*************************************************************************
* Function name      : rightSensorOnTrack()
* returns            : int
* Description        : returns 1 if the sensor is over the black track
* Notes              : 
**************************************************************************/
int rightSensorOnTrack(){
  //write code return 1 if the sensor if over the black track
  
}


/*************************************************************************
* Function name      : leftSensorOnTrack()
* returns            : int
* Description        : returns 1 if the sensor is over the black track
* Notes              : 
**************************************************************************/
int leftSensorOnTrack(){
  //write code return 1 if the sensor if over the black track
  
}
