#pragma once

#include "../../StandardHeader.hpp"

#include <Servo.h>

#include "../../Peripheral.hpp"


#define KICKER_MOTOR          5     // Kicker motor is wired to pin 5
	//these are the speeds for kicking and reload the kicker foot
#define KICKER_POWER          175   
#define KICKER_RELOAD         85

class Kicker : public Peripheral {
	private:
	void kickerCtrl();
	Servo kicker;                       // Define motor object for the kicker motor
	public:
	void doThing() {
		kickerCtrl();
	}
	
	void doNotConnectedThing() {
		return;
	}
	
	Kicker() {
		kicker.attach(KICKER_MOTOR);
		kicker.writeMicroseconds(1500);
	}
};

void Kicker::kickerCtrl()
{
  if (PS3.getButtonPress(CROSS)) kicker.write(KICKER_POWER);
  else if (PS3.getButtonPress(TRIANGLE)) kicker.write(KICKER_RELOAD);
  else kicker.writeMicroseconds(1500);
}
