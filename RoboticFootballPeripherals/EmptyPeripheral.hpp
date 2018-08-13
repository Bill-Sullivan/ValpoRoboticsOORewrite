#pragma once

#include "../StandardHeader.hpp"

#include <Servo.h>


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


class EmptyPeripheral : public Peripheral {
private:
public:
	void doThing() {
		return;
	}
	void doNotConnectedThing() {
		return;
	}

	EmptyPeripheral() {
		return;
	}

	~EmptyPeripheral() {
		return;
	}
};