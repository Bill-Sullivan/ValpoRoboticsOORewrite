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

class PeripheralName: public Peripheral {
private:
    //place variables that need to be accesed by multiple methods here
public:

	/**
	* @brief Function that runs every loop when controller is connected.
	*
	* Function that runs every loop when controller is connected. 
	* Fill in more relevent comments here in your peripheral implementation
	*/
	void doThing() {
		// code for what should happen every loop goes here
		// this must be implemented or you will get an error of the form: cc7HafMs.ltrans5.ltrans.o*: (.rodata+0x16): undefined reference to Peripheral::doThing()
		// if you implement doThing() without a function body (ie doThing();) you will get an error of the form:
		// cc5o5YRY.ltrans4.ltrans.o*: In function operator new
		//	  new.cpp : 22 : undefined reference to vtable for PeripheralName
		//	  new.cpp : 22 : undefined reference to vtable for PeripheralName
	
	return;
	}
	
	/**
	* @brief Function that runs every loop when controller is not connected.
	*
	* Function that runs every loop when controller not is connected. 
	* Fill in more relevent comments here in your peripheral implementation
	*/
	void doNotConnectedThing() {
		// code for what should happen when the controller disconeects 
		// this must be implemented or you will get an error of the form: cc7HafMs.ltrans5.ltrans.o*: (.rodata+0x16): undefined reference to Peripheral::doNotConnectedThing()
		// if you implement doNotConnectedThing() without a function body (ie doNotConnectedThing();) you will get an error of the form:
		// cc5o5YRY.ltrans4.ltrans.o*: In function operator new
		//	  new.cpp : 22 : undefined reference to vtable for PeripheralName
		//	  new.cpp : 22 : undefined reference to vtable for PeripheralName
	
	return;
	}
	
	/**
	* @brief Function that runs once when the microcontroller turns on.
	*
	* Function that runs once when the microcontroller turns on.
	* Fill in more relevent comments here in your peripheral implementation
	*/
	void setup() {
		// code for what should happen when the controller disconeects 
		// this must be implemented or you will get an error of the form: cc7HafMs.ltrans5.ltrans.o*: (.rodata+0x16): undefined reference to Peripheral::doNotConnectedThing()
		// if you implement doNotConnectedThing() without a function body (ie doNotConnectedThing();) you will get an error of the form:
		// cc5o5YRY.ltrans4.ltrans.o*: In function operator new
		//	  new.cpp : 22 : undefined reference to vtable for PeripheralName
		//	  new.cpp : 22 : undefined reference to vtable for PeripheralName
		
		return;
	}
      
};
