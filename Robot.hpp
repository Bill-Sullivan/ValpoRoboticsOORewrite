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

#include "array.hpp"

#include "Config.hpp"

#include "Peripheral.hpp"

#if !defined(MAX_TOTAL_PERIPERALS)
	#define MAX_TOTAL_PERIPERALS 10
#endif

#if !defined(MRDC_ROBOT)
  #include "RoboticFootballLibraries.hpp"
#elif defined(ERNIE)
  #include "ErnieLibraries.hpp"
#elif defined(MARVIN)
  #include "MarvinLibraries.hpp"
#elif defined(PARKER)
  #include "ParkerLibraries.hpp"
#endif


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
  * @brief Pointer to an LED 
  *
  * Pointer to an LED 
  * Stores an pointer to an LED class so that all peipherals that acces the LED (ie the Tackle Sensor)
  * access the same LED
  */
  #if defined(LED_STRIP)
  LED* led; 
  #endif

  /**
  * @brief Pointer to a DriveTrain
  *
  * eStop is run when the controller is disconnected
  * doThing runs continously when the controller is connected
  * setup runs once when the microcontroller is turned on
  */
	DriveTrain* driveTrain;
 /**
  * @brief Array of pointers to Peripherals
  *
  * doNotConnectedThing is run when the controller is disconnected
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
		
		// This is copied from example code on how to use the PS3BT library 
		// it initilizes the dongle and makes sure no other code runs if it cannot 
		if (Usb.Init() == -1) // this is for an error message with USB connections
		{
			Serial.print(F("\r\nOSC did not start"));
			while (1);
		}
		Serial.print(F("\r\nPS3 Bluetooth Library Started"));
   Serial.println();
    #if defined(LED_STRIP)
      led = new LED();        
    #endif
	
	// begin add all peripals to peripheralVec
  
    // Add peripherals to the peripheralVec 
	// any peipheral added will have its Constructor, setup, doThing and doNotConnectedThing run at the appropreate time
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
	
	// Dont know if this is still needed investigate this and remove if unneeded
    #if defined(NO_PERIPHERALS_DEFINED)
      peripheralVec.push_back(new EmptyPeripheral);
    #endif
    
    #if defined(QB_PERIPHERALS)
      peripheralVec.push_back(new QBArm);
    #endif

    #if defined(DROP_DETECTOR_2) 
      peripheralVec.push_back(new DropDetector(2,4));
    #endif
    #if defined(DROP_DETECTOR_3)
      peripheralVec.push_back(new DropDetector(3,5));
    #endif

    #if defined(VACUUM)
      peripheralVec.push_back(new Vacuum(VACUUM_PIN, VACUUM_BUTTON, VACUUM_SPEED));
    #endif
    #if defined(VACUUM_ARM)
      peripheralVec.push_back(new ButtonMotorMover(VACUUM_ARM_PIN, VACUUM_ARM_DOWN_BUTTON, VACUUM_ARM_UP_BUTTON, VACUUM_ARM_SPEED));
    #endif
    #if defined(BOWLING_BALL_ARM)
      peripheralVec.push_back(new ButtonMotorMover(BOWLING_BALL_ARM_PIN, BOWLING_BALL_ARM_DOWN_BUTTON, BOWLING_BALL_ARM_UP_BUTTON, BOWLING_BALL_ARM_SPEED));
    #endif
    

    // end add all peripals to peripheralVec

      // choose drive train
    #if defined(BASIC_DRIVETRAIN)
      Serial.println("Basic Drive");
      driveTrain = new BasicDriveController;
    #elif defined(OMNIWHEEL_DRIVETRAIN)
      driveTrain = new OmniDriveConrtoller;
    #elif defined(NEW_OMNIWHEEL_DRIVETRAIN)
      driveTrain = new NewOmniDrive;
    #elif defined(TEST_DRIVETRAIN)
      driveTrain = new testDriveConrtoller;
    #elif defined(AUTONOMOUS_DRIVE)
      Serial.println("Autonomous Drive");
      driveTrain = new AutonomousBasicDrive;
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
    Usb.Task(); // this updates the PS3 object 
	if (PS3.PS3Connected)                 // This only lets the program run if the PS3
	// controller is connected.
	{
	  newConnection();
	  
	  //when controller connected once per loop run the driveTrain's doThing method
	  driveTrain->doThing();    
	  //when controller connected once per loop run each peripheral's doThing method
	  for (Peripheral* peripheral : peripheralVec) {
	  	peripheral->doThing();
	  }

	  //disconnect when the PS button (the middle button) is pressed
      if (PS3.getButtonClick(PS)) {
        PS3.disconnect();
        newconnect = 0;
      }
	} else {
		//when controller disconnected once per loop run the driveTrain's eStop method
	    driveTrain->eStop();
		//when controller disconnected once per loop run each peripheral's doNotConnectedThing method
	    for (Peripheral* peripheral : peripheralVec) {
	    	 peripheral->doNotConnectedThing();
	    }
	}
	}
};
