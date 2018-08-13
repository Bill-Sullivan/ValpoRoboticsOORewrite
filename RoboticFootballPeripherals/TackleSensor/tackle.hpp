#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <stdint.h>
#include "../LED/LED.hpp"


#include "../../Peripheral.hpp"

#define GREEN 'g'
#define RED   'r'
#define BLUE  'b'

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

class TackleSeansor : public Peripheral {
	private:
		LED* led;
	
		bool checkTackled() {
			tackled = !digitalRead(TACKLE_INPUT);
			return tackled;
		}					
	
		void handelTackle() {
		if (checkTackled()) {
			led->setColor(led->tackledColor);
		} else {
			led->setColor(led->notTackeledColor);
		}
		}

    
	public:
		void doNotConnectedThing() {
			led->setColor(BLUE);
		}
		void doThing() {
			handelTackle();
		}
		bool tackled;

	
	TackleSeansor(LED* _pLED) {
		led = _pLED;
		pinMode(TACKLE_INPUT, INPUT); // define the tackle sensor pin as an input
	}
};
