#pragma once

#include <Arduino.h>
#include <stdint.h>

#include <StandardCplusplus.h> // this is nessissary because Arduino Doesn't inlude the full standard library by default
// can be found here: https://github.com/maniacbug/StandardCplusplus
#include <vector>

#if !defined(PS3_VARS)
	//Include libraries
	#include <PS3BT.h>
	#include <usbhub.h>
	USB Usb;
	USBHub Hub1(&Usb);
	BTD Btd(&Usb);
	PS3BT PS3(&Btd);
	
	#define PS3_VARS
#endif

#include "Config.hpp"

#if !defined(MAX_TOTAL_PERIPERALS)
	#define MAX_TOTAL_PERIPERALS 0
#endif

/*
// include all possible libraries here
#include "DriveTrain.hpp"
#include "BasicDrive.hpp"
#include "OmniDrive.hpp"

#include "Peripheral.hpp"
#include "kicker.hpp"
#include "center.hpp"
#include "LED.hpp"
#include "tackle.hpp"
*/
#include "RoboticFootballLibraries.hpp"

class Robot {
private:	
	DriveTrain* driveTrain;
	std::vector<Peripheral*> peripheralVec;

	void newConnection() {
		static bool newconnect = false;
		if (newconnect == false)                // this is the vibration that you feel when you first connect
			{
				newconnect = true;
				//Serial.println("Rumble is on!");
				PS3.moveSetRumble(64);
				PS3.setRumbleOn(100, 255, 100, 255); //VIBRATE!!!
			
			}
	}

public:
Robot() {
    peripheralVec.resize(MAX_TOTAL_PERIPERALS);

		//Begin Serial Communications
		Serial.begin(115200);
		if (Usb.Init() == -1)                 // this is for an error message with USB connections
		{
			Serial.print(F("\r\nOSC did not start"));
			while (1);
		}
		Serial.print(F("\r\nPS3 Bluetooth Library Started"));
		
			// add all peripals to peripheralVec    
		#if defined(BASIC_DRIVETRAIN)
			driveTrain = basicDriveConrtoller();
		#elsif defined(OMNIWHEEL_DRIVETRAIN)
			driveTrain = omniDriveConrtoller();
		#endif
		peripheralVec = {
    // Note if you have no peripherals declared the code will not compile.
    // The simplest fix if you do not need any peripherals is to create a simple peripheral that does nothing
			#if defined(CENTER_PERIPHERALS)
				new Center(),
			#endif
			#if defined(KICKER_PERIPHERALS)
				new Kicker(),				
			#endif
			// This will might error out if LED is not defined and anything else is but that should be fine		
			#if defined(LED_STRIP)
				new LED()
			#endif
      
		};
		
		// add all peripals to peripheralVec
		// Peripherals should have thier setup done in their constructors
		// This means we dont need to do anything here to set them up
}
	
	void loop () {
		if (PS3.PS3Connected)                 // This only lets the program run if the PS3
		// controller is connected.
		{
			newConnection();
			
			driveTrain->doThing();
			for (Peripheral* peripheral : peripheralVec) {
				peripheral->doThing();
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
