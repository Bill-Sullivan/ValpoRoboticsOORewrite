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
 * the reader. 
 *
 * To create a new peripheral copy this file and the associated .cpp file to a new directory, 
 * Replace every instance of PeripheralName in both files with the name of your peripheral.
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
// ../ means one directory up
#include "../../StandardHeader.hpp" // This includes the standard header, which has the libraries needed in every file, and deals with the PS3 Controller stuff
#include "../../Peripheral.hpp"    // this inculdes the parent class of all peripherals

class PeripheralName: public Peripheral {
private:
    //place variables and methods that need to be accesed by multiple methods here
public:
	//place variables and methods that need to be accesed by things outside object here

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
