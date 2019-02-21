#pragma once

/**
 * \class Vacuum
 *
 * \ingroup Peripherals
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief Provide an example
 *
 * This class is meant as an example.  It is not useful by itself
 * rather its usefulness is only a function of how much it helps
 * the reader. 
 *
 * To create a new peripheral copy this file and the associated .cpp file to a new directory, 
 * Replace every instance of Vacuum in both files with the name of your peripheral.
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


class Vacuum: public Peripheral {
private:
    /**
	* @brief button that should be pressed when you want the vaccum to suck
	* 
	* The supported buttons are:
    * UP, RIGHT, DOWN, LEFT, L1, L2, L3, R1, R2, R3
    * TRIANGLE, CIRCLE, CROSS, SQUARE, and T.
	*/
	ButtonEnum suckButton;
	/**
	* @brief Our motor controllers are moddeled as Servos
	*
	* Victors take a pulsewidth of 1000-2000 µs and output a voltage between 0-12V 
	* Servos are controlled the same way so victors can be controlled the same way. 
	* 
	*/
	Servo 	   vacuumMotor;
	/**
	* @brief The pin that the victor that controlls the motor is connected to
	*/
	uint8_t	   pin;
	/**
	* @brief how fast the motor should move
	* speed is a scalled value between 1000 and 2000
	* further from 1500 means more power to the motor
	* 1000 or 2000 is max power, which one is max depends on the polarity of the vacuum motor
	* a value of 1500 means the vacuum will not suck
	*/	
	uint16_t   vacuumSpeed;
public:
	/**
	* @brief Constructor 
	* @param _pin the pin that the victor that controlls the motor is connected to
	* @param _forward Button that makes the vacuum suck	
	* @param _vacuumSpeed speed of vacuum motor.
	*/
	Vacuum(uint8_t _pin, ButtonEnum _suckButton, uint16_t _vacuumSpeed);
	/**
	* @brief Function that runs every loop when controller is connected.
	* checks if the Suck Button is pressed.
	* if so the vacuum should start sucking.
	*/
	void doThing();
	
	/**
	* @brief Function that runs every loop when controller is not connected.
	*
	* Function that runs every loop when controller not is connected. 
	* stops the motors when the controller is not connected for saftey. 
	*/
	void doNotConnectedThing();
	
	/**
	* @brief Function that runs once when the microcontroller turns on.
	*
	* Function that runs once when the microcontroller turns on.
	* sets up the motor
	*/
	void setup();
      
};

#include "Vacuum.cpp"