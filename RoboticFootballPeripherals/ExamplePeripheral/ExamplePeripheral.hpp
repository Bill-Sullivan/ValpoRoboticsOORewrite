#pragma once

/**
 * \class TestClass
 *
 * \ingroup PackageName
 * (Note, this needs exactly one \defgroup somewhere)
 *
 * \brief Provide an example
 *
 * This class is meant as an example.  It is not useful by itself
 * rather its usefulness is only a function of how much it helps
 * the reader.  It is in a sense defined by the person who reads it
 * and otherwise does not exist in any real form. 
 *
 * \note Attempts at zen rarely work.
 *
 * \author (last to touch it) $Author: bv Bill Sullivan$
 *
 * \version $Revision: 1.0 $
 *
 * \date $Date: 2018/04/14 14:16:20 $
 * 
 *
 * Created on: 
 *
 * $Id: doxygen-howto2.html,v 1.5 2018/04/14 14:16:20 bv Exp $
 *
 */

// both of these headers locations maybe diffrent depending on where your peripheral is
#include "../../StandardHeader.hpp" // This includes the standard header, which has the libraries needed in every file, and deals with the PS3 Controller stuff
#include "../../Peripheral.hpp"    // this inculdes the parent class of all peripherals

class PeripheralName: public Peripheral {
  private:
    //place variables that need to be accesed by multiple methods here
  public:
      void doThing() {
        // code for what should happen every loop goes here
		// this must be implemented or you will get an error of the form: cc7HafMs.ltrans5.ltrans.o*: (.rodata+0x16): undefined reference to Peripheral::doThing()
		// if you implement doThing() without a function body (ie doThing();) you will get an error of the form:
		// cc5o5YRY.ltrans4.ltrans.o*: In function operator new
		//	  new.cpp : 22 : undefined reference to vtable for PeripheralName
		//	  new.cpp : 22 : undefined reference to vtable for PeripheralName
		  
		return;
      }
      void doNotConnectedThing() {
        // code for what should happen when the controller disconeects 
		// this must be implemented or you will get an error of the form: cc7HafMs.ltrans5.ltrans.o*: (.rodata+0x16): undefined reference to Peripheral::doNotConnectedThing()
		// if you implement doNotConnectedThing() without a function body (ie doNotConnectedThing();) you will get an error of the form:
		// cc5o5YRY.ltrans4.ltrans.o*: In function operator new
		//	  new.cpp : 22 : undefined reference to vtable for PeripheralName
		//	  new.cpp : 22 : undefined reference to vtable for PeripheralName

		return;
      }
};
