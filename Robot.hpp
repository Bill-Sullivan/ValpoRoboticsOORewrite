#pragma once

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
	void newConnection() {
		if (newconnect == false)                // this is the vibration that you feel when you first connect
			{
				newconnect = true;
				Serial.println("Rumble is on!");
				PS3.moveSetRumble(64);
				PS3.setRumbleOn(100, 255, 100, 255); //VIBRATE!!!
			
			}
	}
public:
  
   LED* led;
 

	DriveTrain* driveTrain;
	ValpoRobotics::array<Peripheral*, MAX_TOTAL_PERIPERALS> peripheralVec;

  bool newconnect = false;
  
	void setup() {
		//Begin Serial Communications
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
    
//    #if defined(NO_PERIPHERALS_DEFINED)
//      peripheralVec.push_back(new EmptyPeripheral);         
//    #endif

    // add all peripals to peripheralVec
    // Peripherals should have thier setup done in their constructors
    // This means we dont need to do anything here to set them up

      // choose drive train
    #if defined(BASIC_DRIVETRAIN) && !defined(DUAL_MOTORS)
      driveTrain = new basicDriveController;
    #elif defined(DUAL_MOTORS)
      driveTrain = new DualMotorBasicDrive;
    #elif defined(OMNIWHEEL_DRIVETRAIN)
      driveTrain = new omniDriveConrtoller;
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
	
	void loop () {
    Usb.Task();
		if (PS3.PS3Connected)                 // This only lets the program run if the PS3
		// controller is connected.
		{
			newConnection();
			
			driveTrain->doThing();
			for (Peripheral* peripheral : peripheralVec) {
				peripheral->doThing();
        Serial.println("Thing Done");
			}

      if (PS3.getButtonClick(PS)) {
        PS3.disconnect();
        newconnect = 0;
      } 
		}
		else 
		{			
			driveTrain->eStop();
      int counter = 0;
			for (Peripheral* peripheral : peripheralVec) {
				 peripheral->doNotConnectedThing();
        Serial.println("Not connected Thing Done");
        Serial.println(counter);
        counter++;
			}
		}
	}
};

