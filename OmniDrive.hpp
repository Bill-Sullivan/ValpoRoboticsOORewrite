#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <stdint.h>
#include <EEPROM.h>
#include <math.h>

#if !defined(PS3_VARS)
	//Include libraries
	#include <PS3BT.h>
	#include <usbhub.h>
	USB Usb;
	USBHub Hub1(&Usb);
	BTD Btd(&Usb);
	PS3BT PS3(&Btd);
	
	#define PS3_VARS
#endif

// mode definitions
#undef DRIVING
#define DRIVING         1

#undef CALIBRATION
#define CALIBRATION     2

#undef KID
#define KID             3

#define MOTOR_1               7     //   1//-FRONT-\\4
#define MOTOR_2               8     //     |       |
#define MOTOR_3               9     //     |       |                                                                          <-- check this for accuracy
#define MOTOR_4               10    //   2\\-------//3

#undef KID_HANDICAP
#define KID_HANDICAP          5     // when omni is in kids mode, speed is divided by 5 


#define PI_OVER_2             M_PI/2
#define PI_OVER_4             M_PI/4
#define TURN_HANDICAP_AMOUNT  1     // divide turn speed by 1
#define MAX_TURN 14                 // limit the value for turning for calculations to send final speed to motors
#ifdef QB_PERIPHERALS               // If this is the QB then R2 slows down otherwise R2 is boost.
  #define DEFAULT_HANDICAP      1   // when not using boost, drive full speed
  #undef ALTERNATE_HANDICAP
  #define ALTERNATE_HANDICAP    3   // when using boost, divide speed by 3
#else
  #define DEFAULT_HANDICAP      3   // when not using boost, divide speed by 3
  #undef ALTERNATE_HANDICAP
  #define ALTERNATE_HANDICAP    2   // when using boost, divide speed by 2 
#endif
  Servo motor1, motor2, motor3, motor4;                                       // Define omni motor objects

#if !defined(MAX_DRIVE)
	#define MAX_DRIVE             84    // limited because of issues with calibrating victors to full 0-180 range
#endif
#if !defined(ALTERNATE_HANDICAP)
	#define ALTERNATE_HANDICAP    1    
#endif
#if !defined(DEFAULT_HANDICAP)
  #define DEFAULT_HANDICAP      3     // when not using boost, speed is divided by 3
#endif  
#if !defined(KID_HANDICAP)
  #define KID_HANDICAP          7     // when in kids mode, speed s divided by 7	
#endif  
  
	
  /*  these are to reverse the motor direction if a motor is wired backwards.
   *  In almost every case, it would be better to fix the wiring than to change this in code
   */

#define BAG_MOTOR
   
#if defined(BAG_MOTOR)
	#define LEFT_MOTOR_REVERSE    1     
	#define RIGHT_MOTOR_REVERSE   -1     
	#endif
#if defined (_775_MOTOR) || defined(CIM_MOTOR) || defined(BANEBOTS_MOTOR)
	#define LEFT_MOTOR_REVERSE    -1     
	#define RIGHT_MOTOR_REVERSE   1 
#endif

 
#ifdef ROTATION_LOCK
  #define MINIMUM_ANGLE               5
  #define SAMPLE_PERIOD               50
  #define ROTATION_CORRECT_MAGNITUDE  5
  Adafruit_BNO055 gyro = Adafruit_BNO055(55); //our rotation sensor;
  int rotationCorrect = 0;
  int desiredRotation = 0;
  sensors_event_t rotationReadout;
  int sample = 0;
  int wasIturning = 0;
#endif

#ifdef DUAL_MOTORS
  #define LEFT_MOTOR2           7
  #define RIGHT_MOTOR2          8
#endif

class omniDriveConrtoller: public DriveTrain {
	private:	
	static void drive();	
	
	static uint8_t state;
	static int 	motorCorrect;	
	static uint8_t inverting;
	static int8_t motorReverse;
	static int turnHandicap;
	
	
	static uint8_t handicap;
	
	#ifdef ROTATION_LOCK
	  Adafruit_BNO055 gyro = Adafruit_BNO055(55); //our rotation sensor;
	  int rotationCorrect = 0;
	  int desiredRotation = 0;
	  sensors_event_t rotationReadout;
	  int sample = 0;
	  int wasIturning = 0;
	#endif
	
	static void (*driveCtrl)();	
	static void handelInputs();
	
	public:	
  void eStop();
	void doThing() {
		handelInputs();
		driveCtrl();		
	}
	
	static Servo motor1, motor2, motor3, motor4;
		

	omniDriveConrtoller() {
		turnHandicap = 1;
		
		motor1.attach(MOTOR_1, 1000, 2000);
		motor1.writeMicroseconds(1500);
		motor2.attach(MOTOR_2, 1000, 2000);
		motor2.writeMicroseconds(1500);
		motor3.attach(MOTOR_3, 1000, 2000);
		motor3.writeMicroseconds(1500);
		motor4.attach(MOTOR_4, 1000, 2000);
		motor4.writeMicroseconds(1500);
		
		driveCtrl = drive;
	}
};

void omniDriveConrtoller::eStop() {
	motor1.writeMicroseconds(1500);
	motor2.writeMicroseconds(1500);
	motor3.writeMicroseconds(1500);
	motor4.writeMicroseconds(1500);
}

void omniDriveConrtoller::drive() {
  int yInput, xInput, turnInput, motor1Drive, motor2Drive, motor3Drive, motor4Drive, magn, angle;
  static int motor1Input, motor2Input, motor3Input, motor4Input;
	
  yInput = map(PS3.getAnalogHat(LeftHatY), 0, 255, 90, -90);      // Recieves PS3 forward/backward input
  xInput = map(PS3.getAnalogHat(LeftHatX), 0, 255, 90, -90);      // Recieves PS3 horizontal input and
  // sets it to an inverted scale of 90 to -90
  turnInput = map(PS3.getAnalogHat(RightHatX), 0, 255, -MAX_TURN, MAX_TURN);  // received turn input from right joystick
  if (!PS3.getButtonPress(L2))
  {
    if (PS3.getButtonPress(UP))
    {
      yInput = 90;
      xInput = 0;
    }
    else if (PS3.getButtonPress(DOWN))
    {
      yInput = -90;
      xInput = 0;
    }
    else if (PS3.getButtonPress(LEFT))
    {
      yInput = 0;
      xInput = 90;
    }
    else if (PS3.getButtonPress(RIGHT))
    {
      yInput = 0;
      xInput = -90;
    }
  }
  if (abs(yInput) < 8)yInput = 0;                     // taking care of sticky input
  if (abs(xInput) < 8)xInput = 0;
  if (abs(turnInput) < 2)turnInput = 0;               // this one is likely taken care
  // of by integer rounding already
  // rounding
 
  magn = sqrt(pow(xInput, 2) + pow(yInput, 2));       // finding magnitude of input
  //magn = map(magn, 0, float(90) * sqrt(2.0), 0, 60);// need to investigate the purpose of this
  angle = atan2(double(yInput), double(xInput));      // atan2 accounts for quadrants of input
 
 
#ifdef ROTATION_LOCK
  sample++;
  if (PS3.getButtonClick(R3))
  {
    gyro.getEvent(&rotationReadout);
    desiredRotation = rotationReadout.orientation.x;
    rotationCorrect = 0;
    PS3.setRumbleOn(10, 255, 10, 255); //vibrate!
    sample = 0;
  }
 
  if (turnInput)
  {
    rotationCorrect = 0;
    wasIturning = 1;
    sample = 0;
  }
 
  else if ((sample >= SAMPLE_PERIOD))
  {
    sample = 0;
    gyro.getEvent(&rotationReadout);
    int difference = rotationReadout.orientation.x - desiredRotation;
    if ((difference < 0 && difference > -180) || difference > 180)
    { //turning left condition
      difference = -(abs(difference - 360) % 360);
    }
    else                                                //turning right condition
    {
      difference = abs(difference + 360) % 360;
    }
    if (difference > MINIMUM_ANGLE)
    {
      rotationCorrect = -ROTATION_CORRECT_MAGNITUDE;
    }
    else if (difference < -MINIMUM_ANGLE)
    {
      rotationCorrect = ROTATION_CORRECT_MAGNITUDE;
    }
    else
    {
      rotationCorrect = 0;
    }
 
    if (wasIturning)
    {
      if (difference == 0)
      {
        wasIturning = 0;
      }
      else
      {
        rotationCorrect = 0;
      }
    }
  }

  Serial.print(rotationCorrect);
  Serial.print("   ");
  Serial.println(desiredRotation);
 
  Serial.print(rotationCorrect);
  Serial.print("   ");
  Serial.println(desiredRotation);

  motor1Drive += rotationCorrect;
  motor2Drive += rotationCorrect;
  motor3Drive += rotationCorrect;
  motor4Drive += rotationCorrect;

  
#endif

  motor4Drive = ((magn * (sin(angle + PI_OVER_4 + motorReverse)) / handicap)
                + (float)(turnHandicap * turnInput) + 90 + motorCorrect);

  motor1Drive = ((magn * (sin(angle + PI_OVER_4 + PI_OVER_2 + motorReverse)) / handicap)                          
                + (float)(turnHandicap * turnInput) + 90 + motorCorrect);

  motor2Drive = ((magn * (sin(angle + PI_OVER_4 + PI_OVER_2 + PI_OVER_2 + motorReverse)) / handicap)              
                + (float)(turnHandicap * turnInput) + 90 + motorCorrect);

  motor3Drive = ((magn * (sin(angle + PI_OVER_4 + PI_OVER_2 + PI_OVER_2 + PI_OVER_2 + motorReverse)) / handicap)  
                + (float)(turnHandicap * turnInput) + 90 + motorCorrect);

#ifdef QB_TRACKING
  motor1Drive -= aimingFactor;
  motor2Drive -= aimingFactor;
  motor3Drive -= aimingFactor;
  motor4Drive -= aimingFactor;
#endif

  if (motor1Drive < 5)motor1Drive = 5;
  else if (motor1Drive > 175)motor1Drive = 175;
  if (motor2Drive < 5)motor2Drive = 5;
  else if (motor2Drive > 175)motor2Drive = 175;
  if (motor3Drive < 5)motor3Drive = 5;
  else if (motor3Drive > 175)motor3Drive = 175;
  if (motor4Drive < 5)motor1Drive = 5;
  else if (motor4Drive > 175)motor4Drive = 175;
 
  if (motor1Drive > motor1Input)motor1Input++;
  else if (motor1Drive < motor1Input)motor1Input--;
  if (motor2Drive > motor2Input)motor2Input++;
  else if (motor2Drive < motor2Input)motor2Input--;
  if (motor3Drive > motor3Input)motor3Input++;
  else if (motor3Drive < motor3Input)motor3Input--;
  if (motor4Drive > motor4Input)motor4Input++;
  else if (motor4Drive < motor4Input)motor4Input--;
 
  motor1.write(motor1Input);
  motor2.write(motor2Input);
  motor3.write(motor3Input);
  motor4.write(motor4Input);
}
