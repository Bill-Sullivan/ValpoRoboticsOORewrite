#pragma once

/**
 * \class BasicDriveController
 *
 * \ingroup DriveTrain
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This is the basic drivetrain that most robots use
 * Used for most two motor robots.
 *
 * \author  <!-- ((last to touch it) --> Bill Sullivan
 *
 * \version $Revision: 1.0 
 *
 * \date  2018/08/15 14:16:20
  <!-- YYYY/MM/DD -->
 * 
 *
 * Created on: 2018/04/14 14:16:20
 */


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



class BasicDriveController: public DriveTrain {
	// to do check if volitile is nessessary before driveCtrl
protected:
	/**
	* \brief Flag that selects weather the robot is using Tank or Arcade control
	*/
	int driveCtrl;
	/**
	* \brief Flag that selects weather the robot is using kid or normal handcap
	*/
	uint8_t state;
	/**
	* \brief variable that corrects for diffrences between each motor (Mostly irrlevent since bainbots moters were replaced)
	*/
	int 	motorCorrect;	
	/**
	* \brief variable that selects if robot is driving backwords
	*/
	uint8_t inverting;
	/**
	* \brief motor power is divided by this variable
	*/
	uint8_t handicap;
	/**
	* \brief function that controls how the robot controls under arcade controls
	*/
	const void arcadeDrive();
	/**
	* \brief function that controls how the robot controls under tank controls
	*/
	const void tankDrive();
	
	/**
	* \brief function that handels inputs not directly related to stearing
	*/
	void handelInputs();
	
	
public:	
	/**
	* \brief stop the robot so in the event control is lost
	* controls what happens when the controller disconnects
	* Make sure this code results in the robot stopping or we will break anouther door 
	*/
	void eStop();
	/**	
	*
	* \brief the implementation of doThing should implement what happens when the controller is connected
	*/
	void doThing();
	/**	
	*
	* \brief sets initial values of variables and motors
	*/
	void setup();
	
	/**
	* \brief Victors are modeled as servos
	*/
	Servo leftMotor, rightMotor;        // Define motor objects
	#ifdef DUAL_MOTORS
		Servo leftMotor2, rightMotor2;
	#endif
};

#include "BasicDrive.cpp"