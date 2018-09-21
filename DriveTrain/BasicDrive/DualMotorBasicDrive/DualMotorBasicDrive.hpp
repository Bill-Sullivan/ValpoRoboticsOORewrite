/*
#pragma once

#include <Servo.h>
#include <EEPROM.h>

#include "../../DriveTrain.hpp"


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

//  these are to reverse the motor direction if a motor is wired backwards.
//  In almost every case, it would be better to fix the wiring than to change this in code


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

#define LEFT_MOTOR2           7
#define RIGHT_MOTOR2          8

class DualMotorBasicDrive : public BasicDriveController {
private:
	static void arcadeDrive();
	static void tankDrive();

	static void(*driveCtrl)();
	static void handelInputs();

	void eStop();

	static Servo leftMotor2, rightMotor2;
public:

};

void DualMotorBasicDrive::arcadeDrive() {
	basicDriveConrtoller::arcadeDrive();
	rightMotor2.write(rightMotor.read());
	leftMotor2.write(leftMotor.read());
	
}

void DualMotorBasicDrive::tankDrive() {
	basicDriveConrtoller::tankDrive();
	rightMotor.write(rightMotor.read());
	leftMotor.write(leftMotor.read());

	rightMotor2.write(rightMotor.read());
	leftMotor2.write(leftMotor.read());	
}


void DualMotorBasicDrive::eStop() {
	basicDriveConrtoller::eStop();
	leftMotor2.writeMicroseconds(1500);
	rightMotor2.writeMicroseconds(1500);
}
*/