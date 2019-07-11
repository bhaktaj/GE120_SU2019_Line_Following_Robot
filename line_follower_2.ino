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
* DEFINITIONS AND MACROS
*************************************************************************/
#define VERSION "1.0"
#define DEBUG /*keep this line to compile debug comments*/


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

/*digital inputs*/
const int START_STOP_BUTTON=9;

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
void steerLeft();

/************************************************************************
* SETUP FUNCTION
*************************************************************************/
void setup() {
  
  /*setup serial port for debugging*/
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  
  /*configuring digital IO pins*/
  pinMode(PWMA,OUTPUT);
  pinMode(AI1,OUTPUT);
  pinMode(AI2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(BI1,OUTPUT);
  pinMode(BI2,OUTPUT);
  pinMode(START_STOP_BUTTON,INPUT);

  
  /*stop the motors*/
  stopMotors();

  /*forward*/
  moveForward();
  delay(2000);
  stopMotors();

  /*left turn*/
  steerLeft();
  delay(2000);
  stopMotors();
}


/************************************************************************
* MAIN LOOP
*************************************************************************/
void loop() {
  // put your main code here, to run repeatedly:

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

  #ifdef DEBUG
    Serial.println("motors stopped");
  #endif
  
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

  #ifdef DEBUG
    Serial.println("moving forward");
  #endif
  
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

  #ifdef DEBUG
    Serial.println("steering left");
  #endif  
}


