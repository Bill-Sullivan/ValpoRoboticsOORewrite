#include <Arduino.h>
#include <Servo.h>
#include <stdint.h>

#include "Periperal.hpp"

  #define KICKER_MOTOR          5     // Kicker motor is wired to pin 5
  //these are the speeds for kicking and reload the kicker foot
  #define KICKER_POWER          175   
  #define KICKER_RELOAD         85
  

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


class Kicker: public Periperal {
	private:
	void kickerCtrl();
	Servo kicker;                       // Define motor object for the kicker motor
	public:
	void doThing() {
		kickerCtrl();
	}
	void doNotConnectedThing();
	
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