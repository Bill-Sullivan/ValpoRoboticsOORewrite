#pragma once

/**
 * \class PeripheralName
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

#define ECHO_PIN 2
#define TRIG_PIN 4

#define CLIFF_THRESHOLD 10
#define TRIGGER_TIMEOUT 10000

class DropDetector : public Peripheral {
private:
    //place variables that need to be accesed by multiple methods here	
	long unsigned int echoStart;
	long unsigned int echoLength;
	
	bool triggered;
	long unsigned int timeTriggered;
	
	void trigger();
	
	
	/**
	* @brief Function that gets distance measured by a HC-SR04 in cm
	*/
	int getDistance();
	
public:
	DropDetector();
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

#include "DropDetector.cpp"