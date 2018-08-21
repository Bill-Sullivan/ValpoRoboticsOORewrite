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

#include <Servo.h>
#include <EEPROM.h>
#include <math.h>


#include "../DriveTrain.hpp"

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

class OmniDriveConrtoller: public DriveTrain {
protected:
	/**
	* \brief function that controls the robot
	*/
	void drive();	
	
	/**
	* \brief variable that corrects for diffrences between each motor (Mostly irrlevent since bainbots moters were replaced)
	*/
	int 	motorCorrect;
	/**
	* \brief variable that selects if robot is driving backwords
	*/
	int8_t inverting;
	
	float  motorReverse;
	/**
	* \brief motor power is divided by this variable for rotational motion
	*/
	int8_t turnHandicap;
	/**
	* \brief motor power is divided by this variable for linear motion
	*/
	int8_t handicap;
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

#include "OmniDrive.cpp"

