#pragma once

/**
 * \class ServoBallCollector
 *
 * \ingroup Peripherals
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief Provide an example
 *
 * This class is meant as an example.  It is not useful by itself
 * rather its usefulness is only a function of how much it helps
 * the reader.  It is in a sense defined by the person who reads it
 * and otherwise does not exist in any real form. 
 *
 * \author  <!-- ((last to touch it) --> Bill Sullivan
 *
 * \version $Revision: 1.0 
 *
 * \date  2018/08/14 14:16:20
	<!-- YYYY/MM/DD -->
 * 
 *
 * Created on: 2018/04/14 14:16:20
 *
 * $Id: doxygen-howto2.html,v 1.5  bv Exp $
 *
 */

// both of these headers locations maybe diffrent depending on where your peripheral is
#include "../../StandardHeader.hpp" // This includes the standard header, which has the libraries needed in every file, and deals with the PS3 Controller stuff
#include "../../Peripheral.hpp"    // this inculdes the parent class of all peripherals

class ServoBallCollector : public Peripheral {
private:
    //place variables that need to be accesed by multiple methods here	
	/**
	* @brief button that should be pressed when you want the vaccum to suck
	* 
	* The supported buttons are:
    * UP, RIGHT, DOWN, LEFT, L1, L2, L3, R1, R2, R3
    * TRIANGLE, CIRCLE, CROSS, SQUARE, and T.
	*/
	ButtonEnum forwardButton;
	
	/**
	* @brief button that should be pressed when you want the vaccum to suck
	* 
	* The supported buttons are:
    * UP, RIGHT, DOWN, LEFT, L1, L2, L3, R1, R2, R3
    * TRIANGLE, CIRCLE, CROSS, SQUARE, and T.
	*/
	ButtonEnum backwordButton;
	/**
	* @brief The pin that the victor that controlls the motor is connected to
	*/
	uint8_t	   pin;
	
	Servo 	   collector;

	
	
public:
	ServoBallCollector(uint8_t _pin, ButtonEnum _forwardButton, ButtonEnum _backwordButton);
	/**
	* @brief Function that runs every loop when controller is connected.
	*
	* Function that runs every loop when controller is connected. 
	* Fill in more relevent comments here in your peripheral implementation
	*/
	void doThing();
	
	/**
	* @brief Function that runs every loop when controller is not connected.
	*
	* Function that runs every loop when controller not is connected. 
	* Fill in more relevent comments here in your peripheral implementation
	*/
	void doNotConnectedThing();
	
	/**
	* @brief Function that runs once when the microcontroller turns on.
	*
	* Function that runs once when the microcontroller turns on.
	* Fill in more relevent comments here in your peripheral implementation
	*/
	void setup();
};

#include "BallCollector.cpp"