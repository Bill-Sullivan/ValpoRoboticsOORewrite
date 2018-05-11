#include <Arduino.h>
#include <Servo.h>
#include <stdint.h>

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

#define TACKLE_INPUT    6           // Tackle sensor is wired to pin 6

class TackleSensor {
	private:
		bool checkTackled() {
			tackled = !digitalRead(TACKLE_INPUT);
			return tackled;
		}			
	public:
		bool tackled;
	

	
	TackleSensor() {
		pinMode(TACKLE_INPUT, INPUT); // define the tackle sensor pin as an input
	}
}