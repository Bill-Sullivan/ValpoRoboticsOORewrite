#include <Arduino.h>
#include <Servo.h>
#include <stdint.h>

#include "Periperal.hpp"

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


#define CENTER_RELEASE        5     // the ball release servo is wired to pin 5
#define CENTER_RELEASE_DOWN   120   // these are the angles between 0 and 180 to set servo for releasing and holding the ball
#define CENTER_RELEASE_UP     70    



class Center: public Periperal {
	private:
	void FortyTwoDropper();
	volatile void (*centerCtrl)();
	Servo centerRelease;                // define servo object for ball release 
	public:
	void doThing() {
		centerCtrl();
	}
	void doNotConnectedThing();
	
	Center() {
		centerRelease.attach(CENTER_RELEASE);   // attach ball release servo to its pin
		centerRelease.write(CENTER_RELEASE_UP); // 
		centerCtrl = FortyTwoDropper;
	}
};

void Center::FortyTwoDropper()
{
  if (PS3.getButtonClick(TRIANGLE)) centerRelease.write(CENTER_RELEASE_UP);
  else if (PS3.getButtonClick(CROSS)) centerRelease.write(CENTER_RELEASE_DOWN);
}