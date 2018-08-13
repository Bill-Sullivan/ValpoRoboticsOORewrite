#pragma once

#include "../../StandardHeader.hpp"

#include <Servo.h>
#include "../../Peripheral.hpp"

#define CENTER_RELEASE        5     // the ball release servo is wired to pin 5
#define CENTER_RELEASE_DOWN   120   // these are the angles between 0 and 180 to set servo for releasing and holding the ball
#define CENTER_RELEASE_UP     70    



class Center : public Peripheral {
	private:
	void centerCtrl();
	Servo centerRelease;                // define servo object for ball release 
	public:
	void doThing() {
		centerCtrl();
	}
	void doNotConnectedThing() {
		return;
	}
	
	void setup() {
		centerRelease.attach(CENTER_RELEASE);   // attach ball release servo to its pin
		centerRelease.write(CENTER_RELEASE_UP); // 
		return;
	}
};

void Center::centerCtrl()
{
  if (PS3.getButtonClick(TRIANGLE)) centerRelease.write(CENTER_RELEASE_UP);
  else if (PS3.getButtonClick(CROSS)) centerRelease.write(CENTER_RELEASE_DOWN);
}
