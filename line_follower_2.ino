
/* hardware connections to Arduino 
 note that motor A is the left motor
 motor B is the right motor
*/

const int PWMA=3;
const int AI1=4;
const int AI2=5;
const int PWMB=6;
const int BI1=7;
const int BI2=8;
const int LEFT_LIGHT_SENSOR=0;
const int RIGHT_LIGHT_SENSOR=1;


/*global constants*/
const int SPEED=100; //0 min, 255 max speed. Sets the PWM duty cycle for the motors

/* function declarations */
void stopMotors();
void moveForward();


void setup() {
  
  /*configuring digital IO pins*/
  pinMode(PWMA,OUTPUT);
  pinMode(AI1,OUTPUT);
  pinMode(AI2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(BI1,OUTPUT);
  pinMode(BI2,OUTPUT);

  /*stop the motors*/
  stopMotors();

  /*forward*/
  moveForward();
  delay(2000);
  stopMotors();
}

void loop() {
  // put your main code here, to run repeatedly:

}

//create a function to read the left reflectance sensor, return 1 if the sensor is receiving low light
//(on the track), otherwise return 0

//create a function to read the right reflectance sensor, return 1 if the sensor is receiving low light
//(on the track), otherwise return 0


/* function: stopMotor()
 *  stops the motors
*/

void stopMotors(){
  /*turn off left motor*/
  digitalWrite(AI1,LOW);
  digitalWrite(AI2,LOW);

  /*turn off the right motor*/
  digitalWrite(BI1,LOW);
  digitalWrite(BI2,LOW);
  
}

/* function: moveForward()
 *  moves the robot forward
*/

void moveForward(){
  /*left motor forward*/
  analogWrite(PWMA,SPEED);
  digitalWrite(AI1,HIGH);
  digitalWrite(AI2,LOW);

  /*right motor forward*/
  analogWrite(PWMB,SPEED);
  digitalWrite(BI1,HIGH);
  digitalWrite(BI2,LOW);
}

