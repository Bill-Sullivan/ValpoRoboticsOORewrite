#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <stdint.h>
#include <EEPROM.h>

#include "DriveTrain.hpp"

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
 
#define LEFT_MOTOR            9     // left motor is wired to pin 9
#define RIGHT_MOTOR           10    // right motor is wired to pin 10

#ifdef DUAL_MOTORS
  #define LEFT_MOTOR2           7
  #define RIGHT_MOTOR2          8
#endif
  



class basicDriveConrtoller: public DriveTrain {
	// to do check if volitile is nessessary before driveCtrl
	private:	
	static void arcadeDrive();
	static void tankDrive();
	
	static uint8_t state;
	static int 	motorCorrect;	
	static uint8_t inverting;
	
	static uint8_t handicap;
	
	static void (*driveCtrl)();	
	static void handelInputs();
	
	
	public:	
  void eStop();
	void doThing() {
		handelInputs();
		driveCtrl();
		
	}
	
	static Servo leftMotor, rightMotor;        // Define motor objects
	#ifdef DUAL_MOTORS
		static Servo leftMotor2, rightMotor2;
	#endif

	basicDriveConrtoller() {
		leftMotor.attach(LEFT_MOTOR, 1000, 2000);
		leftMotor.writeMicroseconds(1500);            //stopped
		rightMotor.attach(RIGHT_MOTOR, 1000, 2000);
		rightMotor.writeMicroseconds(1500);
		#ifdef DUAL_MOTORS
			leftMotor2.attach(LEFT_MOTOR2, 1000, 2000);
			leftMotor2.writeMicroseconds(1500);
			rightMotor2.attach(RIGHT_MOTOR2, 1000, 2000);
			rightMotor2.writeMicroseconds(1500);
		#endif
    driveCtrl = arcadeDrive;
	}
};


void basicDriveConrtoller::eStop() {
	leftMotor.writeMicroseconds(1500);
	rightMotor.writeMicroseconds(1500);
	
	#ifdef DUAL_MOTORS
	leftMotor2.writeMicroseconds(1500);
	rightMotor2.writeMicroseconds(1500);
	#endif
}

void basicDriveConrtoller::handelInputs() {
	if (PS3.getButtonClick(SELECT)) //Switch between tank drive and arcade mode. 0 is arcade 1 is tank
	{
		if (PS3.getButtonPress(L1)) {
			if (driveCtrl == (void (*)())arcadeDrive) {
				EEPROM.write(0, 1);
			}
			else if (driveCtrl == (void (*)())tankDrive) {
				EEPROM.write(0, 0);
			}
		}
	}
	if (PS3.getButtonClick(START))
	{ // switches between normal driving mode
	// and kid mode
		if (state == DRIVING)
		{
			state = KID;
			PS3.setLedRaw(9);               // ON OFF OFF ON
			PS3.setRumbleOn(5, 255, 5, 255);// vibrate both, then left, then right
			handicap = KID_HANDICAP;
		}
		else if (state == KID)
		{
			state = DRIVING;
			PS3.setLedRaw(1);               // OFF OFF OFF ON
			PS3.setRumbleOn(5, 255, 5, 255);// vibrate both, then left, then right
			handicap = DEFAULT_HANDICAP;				
		}
	}
	if (PS3.getButtonClick(R1)) {       //This inverts the driving for tank drive.
		if (inverting == 0) {
			inverting = 1;
			PS3.setRumbleOn(10, 255, 10, 255);
		}
		else if (inverting == 1) {
			inverting = 0;
			PS3.setRumbleOn(10, 255, 10, 255);
		}
	}
}

void basicDriveConrtoller::arcadeDrive() {
	int xInput, yInput, throttleL, throttleR;
	static uint8_t drive, turn;
	  
    yInput = map(PS3.getAnalogHat(LeftHatY), 0, 255, -90, 90);  // Recieves PS3
    // forward/backward input
    xInput = map(PS3.getAnalogHat(RightHatX), 0, 255, 90, -90); // Recieves PS3
    // horizontal input and
    // sets it to an inverted
    // scale of 90 to -90
 
    if (abs(yInput) < 8) yInput = 0;                            // deals with the stickiness
    if (abs(xInput) < 8) xInput = 0;                            // of PS3 joysticks
 
    if ((yInput == 0) && (xInput == 0))
    { // if no input this should ensure that
      // the motors actually stop, and skip the rest
      // of the drive function
      leftMotor.writeMicroseconds(1500);
      rightMotor.writeMicroseconds(1500);
	  #ifdef DUAL_MOTORS
          leftMotor2.writeMicroseconds(1500);
          rightMotor2.writeMicroseconds(1500);
      #endif
      return;
    }
 
    // Instead of following some sort of
    // equation to slow down acceleration
    // We just increment the speed by one
    // towards the desired speed.
    // The acceleration is then slowed
    // because of the loop cycle time
 
    if (drive < yInput)		 drive++;				// Accelerates
    else if (drive > yInput) drive--;               // Decelerates
 
    if (turn < xInput)		{ turn++; } 
    else if (turn > xInput) { turn--; }
 
    throttleL = LEFT_MOTOR_REVERSE * ((drive + turn) / handicap) + motorCorrect;
    // This is the final variable that
    // decides motor speed.
    throttleR = RIGHT_MOTOR_REVERSE * ((drive - turn) / handicap ) + motorCorrect;
 
    if (throttleL > MAX_DRIVE) throttleL = MAX_DRIVE;
    else if (throttleL < -MAX_DRIVE)throttleL = -MAX_DRIVE;
    if (throttleR > MAX_DRIVE) throttleR = MAX_DRIVE;
    else if (throttleR < -MAX_DRIVE)throttleR = -MAX_DRIVE;
 
    leftMotor.write(throttleL + 90);                // Sending values to the speed controllers
    rightMotor.write(throttleR + 90);
    #ifdef DUAL_MOTORS
      leftMotor2.write(throttleL + 90);                // Sending values to the speed controllers
      rightMotor2.write(throttleR + 90);
    #endif
}

void basicDriveConrtoller::tankDrive() {
	int rightInput, leftInput, throttleL, throttleR;
	static uint8_t leftDrive, rightDrive = 0;
    if (inverting == 0) {
      leftInput = map(PS3.getAnalogHat(LeftHatY), 0, 255, -90, 90);  // Recieves PS3
      // forward/backward input
      rightInput = map(PS3.getAnalogHat(RightHatY), 0, 255, -90, 90); // Recieves PS3
    }
    else if (inverting == 1) {
      leftInput = map(PS3.getAnalogHat(RightHatY), 0, 255, 90, -90);  // Recieves PS3
      // forward/backward input
      rightInput = map(PS3.getAnalogHat(LeftHatY), 0, 255, 90, -90); // Recieves PS3
    }
 
    // forward/backward input
    // sets it to an inverted
    // scale of 90 to -90
                                              
    if (abs(leftInput) < 8) leftInput = 0;    // deals with the stickiness
    if (abs(rightInput) < 8) rightInput = 0;  // of PS3 joysticks
 
    if ((leftInput == 0) && (rightInput == 0))
    { // if no input this should ensure that
      // the motors actually stop, and skip the rest
      // of the drive function      
      leftMotor.writeMicroseconds(1500);
      rightMotor.writeMicroseconds(1500);
	  #ifdef DUAL_MOTORS
          leftMotor2.writeMicroseconds(1500);
          rightMotor2.writeMicroseconds(1500);
      #endif
      return;
    }
 
    // Instead of following some sort of
    // equation to slow down acceleration
    // We just increment the speed by one
    // towards the desired speed.
    // The acceleration is then slowed
    // because of the loop cycle time
 
    if (leftDrive < leftInput)      leftDrive++;                     // Accelerates
    else if (leftDrive > leftInput) leftDrive--;               // Decelerates
 
    if (rightDrive < rightInput)      rightDrive++;
    else if (rightDrive > rightInput) rightDrive--;                //Since this is tank drive it is not actually turning
 
    throttleL = LEFT_MOTOR_REVERSE  * ((leftDrive) / handicap) + motorCorrect;
    // This is the final variable that
    // decides motor speed.
    throttleR = RIGHT_MOTOR_REVERSE * ((rightDrive) / handicap ) + motorCorrect;
 
    if (throttleL > MAX_DRIVE) 		throttleL = MAX_DRIVE;
    else if (throttleL < -MAX_DRIVE)throttleL = -MAX_DRIVE;
    if (throttleR > MAX_DRIVE) 		throttleR = MAX_DRIVE;
    else if (throttleR < -MAX_DRIVE)throttleR = -MAX_DRIVE;
 
    leftMotor.write(throttleL + 90);                // Sending values to the speed controllers
    rightMotor.write(throttleR + 90);

    #ifdef DUAL_MOTORS
      leftMotor2.write(throttleL + 90);                // Sending values to the speed controllers
      rightMotor2.write(throttleR + 90);
    #endif
}
