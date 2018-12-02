#pragma once

/**
 * \class OmniDriveConrtoller
 *
 * \ingroup DriveTrain
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This is the drive train for omniwheel robots
 * Used for most four motor robots.
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

#include <Servo.h>

#include "../DriveTrain.hpp"

#define MOTOR_1               7     //   1//-FRONT-\\4
#define MOTOR_2               8     //     |       |
#define MOTOR_3               9     //     |       |                                                                          <-- check this for accuracy
#define MOTOR_4               10    //   2\\-------//3

class NewOmniDrive: public DriveTrain {
protected:
	/**
	* \brief function that controls the robot
	*/
	void drive();
	/**
	* \brief function that takes input from the PS3 Controller and stores it for further use
	*/
	void handelInputs();
	
	/**
	* \brief right stick's left/right input
	*/
	int	rightInputX;
	/**
	* \brief left stick's up/down input
	*/
	int leftInputY;
	/**
	* \brief left stick's left/right input
	*/
	int leftInputX;
	/**
	* \brief variable that corrects for diffrences between each motor (Mostly irrlevent since bainbots moters were replaced)
	*/
	int 	motorCorrect;
	/**
	* \brief variable that selects if robot is driving backwords
	*/
	int8_t inverting;
	/**
	* \brief motor power is divided by this variable for rotational motion
	*/
	int8_t turnHandicap;
	/**
	* \brief Flag that selects weather the robot is using kid or normal handcap
	*/
	uint8_t state;
	/**
	* \brief motor power is divided by this variable for linear motion
	*/
	int8_t handicap;
	/**
	* \brief motor power is negated to drive the robot backwords
	*/
	int8_t motorReverse;
	/**
	* \brief Victors are modeled as servos
	*/
	Servo motor1, motor2, motor3, motor4;
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
};

#include "NewOmniDrive.cpp"

