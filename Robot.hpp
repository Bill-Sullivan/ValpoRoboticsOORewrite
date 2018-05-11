#include <Arduino.h>
#include <stdint.h>

#include <StandardCplusplus.h> // this is nessissary because Arduino Doesn't inlude the full standard library by default
// can be found here: https://github.com/maniacbug/StandardCplusplus

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

#include <array>

class Robot {
private:	
	DriveTrain driveTrain;
	std::array<Peripheral, MAX_TOTAL_PERIPERALS> peripheralVec;

	void newConnection() {
		static newconnect = false;
		if (newconnect == false)                // this is the vibration that you feel when you first connect
			{
				newconnect = true;
				//Serial.println("Rumble is on!");
				PS3.moveSetRumble(64);
				PS3.setRumbleOn(100, 255, 100, 255); //VIBRATE!!!
			
			}
	}

public:
	void setup () {
		//Begin Serial Communications
		Serial.begin(115200);
		if (Usb.Init() == -1)                 // this is for an error message with USB connections
		{
			Serial.print(F("\r\nOSC did not start"));
			while (1);
		}
		Serial.print(F("\r\nPS3 Bluetooth Library Started"));
		
		int numPeripherals = 0;
		
		// add all peripals to peripheralVec
		#if defined(BASIC_DRIVETRAIN)
			
		#elsif defined(OMNIWHEEL_DRIVETRAIN)
		
		#endif
		#if defined(CENTER_PERIPHERALS)
			array.at(numPeripherals) = Center();
			numPeripherals++;
		#endif
		#if defined(KICKER_PERIPHERALS)
			array.at(numPeripherals) = Kicker();
			numPeripherals++;
		#endif
		#if defined(LED_STRIP)
			array.at(numPeripherals) = LED();
			numPeripherals++;
		#endif
		
		
		// add all peripals to peripheralVec
		// Peripherals should have thier setup done in their constructors
		// This means we dont need to do anything here to set them up
	}
	
	void loop () {
		if (PS3.PS3Connected)                 // This only lets the program run if the PS3
		// controller is connected.
		{
			newConnection();
			
			driveTrain.doThing();
			for (Peripheral peripheral : peripheralVec) {
				peripheral.doThing();
			}
		}
		else 
		{
			driveTrain.eStop();
			for (Peripheral peripheral : peripheralVec) {
				peripheral.doNotConnectedThing();
			}
		}
	}
}