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

#include "../SharedDefinitions.hpp"
#include "../DriveTrain.hpp"

//#include <Servo.h>
#include "../WheelPair.hpp"
#include <EEPROM.h>

#undef ARCADE_DRIVE 
#define ARCADE_DRIVE 0

#undef TANK_DRIVE
#define TANK_DRIVE 1

  /*  these are to reverse the motor direction if a motor is wired backwards.
   *  In almost every case, it would be better to fix the wiring than to change this in code
   */
   
#if defined(BAG_MOTOR)
  #define LEFT_MOTOR_REVERSE    1     
  #define RIGHT_MOTOR_REVERSE   -1     
  #endif
#if defined (_775_MOTOR) || defined(CIM_MOTOR) || defined(BANEBOTS_MOTOR)
  #define LEFT_MOTOR_REVERSE    -1     
  #define RIGHT_MOTOR_REVERSE   1 
#endif

#if defined(MRDC_ROBOT) 
	#define LEFT_MOTOR            10     // left motor is wired to pin 9
	#define RIGHT_MOTOR           8    // right motor is wired to pin 10
	
	#define LEFT_MOTOR2           11
	#define RIGHT_MOTOR2          9	
#else 
	#define LEFT_MOTOR            9     // left motor is wired to pin 9
	#define RIGHT_MOTOR           10    // right motor is wired to pin 10
	
	#define LEFT_MOTOR2           7
	#define RIGHT_MOTOR2          8
#endif	

enum ControlMode {tank, arcade};


class BasicDriveController: public DriveTrain {
protected:
	#if defined(BRIDGE_MODE_ENABLED)
	bool brigeMode = false;
	void bridgeMode();
	#endif

	/**
	* \brief Flag that selects weather the robot is using Tank or Arcade control
	*/
	ControlMode driveCtrl;
	/**
	* \brief Flag that selects weather the robot is using kid or normal handcap
	* Enter/Exit Kids mode by pressing start
	* Kids mode makes the robot move slowly enough that it is safe to let a two year old drive it with minimal supervision.
	*/
	bool kidsMode;
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
	* \brief function that handels inputs 
	*/
	void handelInputs();
	
	/**
	* \brief invert inputs if inverting is true
	*/
	void invertInputs();
	
	/**
	* \brief right stick's up/down input
	*/
	int rightInputY;
	/**
	* \brief left stick's up/down input
	*/
	int leftInputY;
	/**
	* \brief right stick's left/right input
	*/
	int	rightInputX;
	
public:	
	/**
	* \brief stop the robot so in the event control is lost
	* controls what happens when the controller disconnects
	* Make sure this code results in the robot stopping or we will break anouther door 
	*/
	void eStop();
	/**	
	*
	* \brief doThing controls the calls functions that handel inputs and control motors 
	* calls functions that handel inputs and places those inputs into variables to be used later
	* Then selects which control mode to use based on user input
	* then calls a drivetrain funcion
	*/
	void doThing();
	/**	
	*
	* \brief sets initial values of variables and motors
	*/
	void setup();
	
	/**
	* \brief Victors are modeled as Motors
	*/
	Motor leftMotor;        // Define motor objects
	/**
	* \brief Victors are modeled as Motors
	*/
	Motor rightMotor;
};

#include "BasicDrive.cpp"