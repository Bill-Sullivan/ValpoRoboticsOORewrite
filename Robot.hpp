#pragma once

/**
 * \class Robot
 *
 * \ingroup Robot
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief Class that acts as a wrapper for other classes
 *
 * This class enables each peipheral and drivetrain to be run without having to know what the other peripherals are doing
 *
 * \note Attempts at zen rarely work.
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
 *
 * $Id: doxygen-howto2.html,v 1.5  bv Exp $
 *
 */

#include "StandardHeader.hpp"

/*
#include <StandardCplusplus.h> // this is nessissary because Arduino Doesn't inlude the full standard library by default
// can be found here: https://github.com/maniacbug/StandardCplusplus
#include <vector>
*/
#include "array.hpp"

#include "Config.hpp"

#include "Peripheral.hpp"

#if !defined(MAX_TOTAL_PERIPERALS)
	#define MAX_TOTAL_PERIPERALS 10
#endif

#include "RoboticFootballLibraries.hpp"

class Robot {
protected:
  /**
  * @brief Function that runs when PS3 Controller connects
  *
  * Function that runs when PS3 Controller connects
  * Function tells rest of the firmware and the user that the controller has connected
  */
	void newConnection() {
		if (newconnect == false)                // this is the vibration that you feel when you first connect
			{
				newconnect = true;
				Serial.println("Rumble is on!");
				PS3.moveSetRumble(64);
				PS3.setRumbleOn(100, 255, 100, 255); //VIBRATE!!!
			
			}
	}
  /**
  * @brief Pointer to an LED no code rus from it mearly because it is here
  *
  * Pointer to an LED no code rus from it mearly because it is here
  * Stores an pointer to an LED class so that all peipherals that acces the LED (ie the Tackle Sensor)
  * access the same LED
  */
  LED* led; 

  /**
  * @brief Pointer to a DriveTrain its methods run because the pointer is populated
  *
  * eStop is run when the controller is disconnected
  * doThing runs continously when the controller is connected
  * setup runs once when the microcontroller is turned on
  */
	DriveTrain* driveTrain;
 /**
  * @brief Pointers to a Peripherals their methods run because the pointers are populated
  *
  * eStop is run when the controller is disconnected
  * doThing runs continously when the controller is connected
  * setup runs once when the microcontroller is turned on
  */
	ValpoRobotics::array<Peripheral*, MAX_TOTAL_PERIPERALS> peripheralVec;

  /**
  * @brief variable that tracks if the controller is connected
  */
  bool newconnect;
 public:
  /**
  * @brief Function that sets up the rest of the firmware
  *  setup function initilizes all variables
  *  sets up setial port to connect back to computer use to program the microcontroller
  */
	void setup() {
		//Begin Serial Communications
   newconnect = false;
		Serial.begin(115200);
		if (Usb.Init() == -1)                 // this is for an error message with USB connections
		{
			Serial.print(F("\r\nOSC did not start"));
			while (1);
		}
		Serial.print(F("\r\nPS3 Bluetooth Library Started"));
      #if defined(LED_STRIP)
        led = new LED();        
    #endif
  
    // Note if you have no peripherals declared the code will not compile.
    // The simplest fix if you do not need any peripherals is to create a simple peripheral that does nothing
    #if defined(CENTER_PERIPHERALS)
      peripheralVec.push_back(new Center);
    #endif
    #if defined(KICKER_PERIPHERALS)
      peripheralVec.push_back(new Kicker);
    #endif
    #if defined(TACKLE)
      #if !defined(LED_STRIP)
      #error "tackle sensor doesn't do anything without LED_STRIP defined"
      #endif
      peripheralVec.push_back(new TackleSeansor(led));
    #endif
    
    #if defined(QB_PERIPHERALS)
      peripheralVec.push_back(new QBArm);
    #endif

    // add all peripals to peripheralVec
    // Peripherals should have thier setup done in their constructors
    // This means we dont need to do anything here to set them up

      // choose drive train
    #if defined(BASIC_DRIVETRAIN) && !defined(DUAL_MOTORS)
      driveTrain = new BasicDriveController;
    #elif defined(DUAL_MOTORS)
      driveTrain = new BasicDriveController;
    #elif defined(OMNIWHEEL_DRIVETRAIN)
      driveTrain = new OmniDriveConrtoller;
    #elif defined(TEST_DRIVETRAIN)
      driveTrain = new testDriveConrtoller;
    #else
#error No Drive Train selected
    #endif

   
   driveTrain->setup();
   for (Peripheral* peripheral : peripheralVec) {
       peripheral->setup();
   }
   #if defined(LED_STRIP)
        led->setup();
    #endif   
	}
	/**
  * @brief Function that runs every to its end then repeats until device shutdown
  *  chekcs if controller is connectd 
  *  if it is
  *   setup controller on first loop after connection
  *   then run drive train and peripheral's connected code
  *  if it is not
  *   run drive train and peripheral's not connected code
  *  
  *  sets up setial port to connect back to computer use to program the microcontroller
  */
	void loop () {
    Usb.Task();
		if (PS3.PS3Connected)                 // This only lets the program run if the PS3
		// controller is connected.
		{
			newConnection();
			
			driveTrain->doThing();
			for (Peripheral* peripheral : peripheralVec) {
				peripheral->doThing();
			}

      if (PS3.getButtonClick(PS)) {
        PS3.disconnect();
        newconnect = 0;
      } 
		}
		else 
		{			
			driveTrain->eStop();      
			for (Peripheral* peripheral : peripheralVec) {
				 peripheral->doNotConnectedThing();        
			}
		}
	}
};

