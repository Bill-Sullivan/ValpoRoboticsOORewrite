#pragma once

/**
 * \class ButtonMotorMover
 *
 * \ingroup Peripherals
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief Class that causes a motor to rotate forward when one button is pressed and backword when anouther button is.
 *
 * This class is ment to control motors by buttons. 
 * This is a very common thing on MRDC robots application.
 * Examples are:
 *   Motor rotating a shaft to suck up balls.
 *   Motor lifting  a lever to open up a box.
 *   Motor rotating to pull a rope.
 *   Motor rotating to move a vacuum hose.
 *   Motor rotating to move a aluminam arm to hold in a bowling ball.
 *   Liniar Actuator extenting to press a button.
 *
 * \author  <!-- ((last to touch it) --> Bill Sullivan
 *
 * \version $Revision: 1.0 
 *
 * \date  2019/02/20 23:16:20
	<!-- YYYY/MM/DD -->
 * 
 *
 * Created on: 2019/02/20 18:16:20
 *
 * $Id: doxygen-howto2.html,v 1.5  bv Exp $
 *
 */

// both of these headers locations maybe diffrent depending on where your peripheral is
// ../ means one directory up
#include "../../StandardHeader.hpp" // This includes the standard header, which has the libraries needed in every file, and deals with the PS3 Controller stuff
#include "../../Peripheral.hpp"    // this inculdes the parent class of all peripherals

class ButtonMotorMover: public Peripheral {
protected:
	/**
	* @brief button that should be pressed when you want the motor to rotate forward	
	* 
	* The supported buttons are:
    * UP, RIGHT, DOWN, LEFT, L1, L2, L3, R1, R2, R3
    * TRIANGLE, CIRCLE, CROSS, SQUARE, and T.
	*/
	ButtonEnum forward;
	/**
	* @brief button that should be pressed when you want the motor to rotate backword
	* 
	* The supported buttons are:
    * UP, RIGHT, DOWN, LEFT, L1, L2, L3, R1, R2, R3
    * TRIANGLE, CIRCLE, CROSS, SQUARE, and T.
	*/
	ButtonEnum backword;
	/**
	* @brief Our motor controllers are moddeled as Servos
	*
	* Victors take a pulsewidth of 0-2000 µs and output a voltage between 0-12V 
	* Servos are controlled the same way so victors can be controlled the same way. 
	* 
	*/
	Servo 	   motor;
	/**
	* @brief The pin that the victor that controlls the motor is connected to
	*/
	uint8_t	   pin;
	/**
	* @brief how fast the motor should move
	* speed should be a value between 0-500 
	* higher values make the motor rotate faster
	* a value of 0 means the motor will never rotate 
	*/	
	uint16_t   speed;
public:
	/**
	* @brief Constructor 
	* @param _pin the pin that the victor that controlls the motor is connected to
	* @param _forward Button that makes the motor rotate forward
	* @param _backword Button that makes the motor rotate backword
	* @param _speed scalled value between 0 and 500 that determies how fast the motor rotates. Higher is faster. 0 is alwase stoped.
	*/
	ButtonMotorMover(uint8_t _pin, ButtonEnum _forward, ButtonEnum _backword, uint16_t _speed);
	/**
	* @brief Function that runs every loop when controller is connected.
	* Checks if the forward or backword button is pressed. 
	* If either is pressed the motor moves in the respective direction.
	*/
	void doThing();
	
	/**
	* @brief Function that runs every loop when controller is not connected.
	* stops the motors when the controller is not connected for saftey. 
	*/
	void doNotConnectedThing();
	
	/**
	* @brief Function that runs once when the microcontroller turns on.
	* sets up the motor
	*/
	void setup();
      
};

#include "ButtonMotorMover.cpp"