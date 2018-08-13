#pragma once

#include "../../StandardHeader.hpp"
#include "../DriveTrain.hpp"

#include <Servo.h>
#include <EEPROM.h>

#undef ARCADE_DRIVE 
#define ARCADE_DRIVE 0

#undef TANK_DRIVE
#define TANK_DRIVE 1

// mode definitions
#undef DRIVING
#define DRIVING         1

#undef CALIBRATION
#define CALIBRATION     2

#undef KID
#define KID             3

#undef MAX_DRIVE
#define MAX_DRIVE             84    // limited because of issues with calibrating victors to full 0-180 range

#undef ALTERNATE_HANDICAP
#define ALTERNATE_HANDICAP    1    

#undef DEFAULT_HANDICAP
#define DEFAULT_HANDICAP      3     // when not using boost, speed is divided by 3

#undef KID_HANDICAP
#define KID_HANDICAP          7     // when in kids mode, speed s divided by 7	
	
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



class basicDriveController: public DriveTrain {
	// to do check if volitile is nessessary before driveCtrl
protected:	
	uint8_t state;
	int 	motorCorrect;	
	uint8_t inverting;
	
	uint8_t handicap;
	
	const void arcadeDrive();
	const void tankDrive();
	
	
	int driveCtrl;
	void handelInputs();
	
	
public:	
	void eStop();
	void doThing();
	void setup();
	
	Servo leftMotor, rightMotor;        // Define motor objects
	#ifdef DUAL_MOTORS
		Servo leftMotor2, rightMotor2;
	#endif
};

#include "BasicDrive.cpp"