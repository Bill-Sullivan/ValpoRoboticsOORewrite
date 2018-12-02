#pragma once

#include "../StandardHeader.hpp"

#include <Servo.h>
class EmptyPeripheral : public Peripheral {
private:
public:
	void doThing() {
		return;
	}
	void doNotConnectedThing() {
		return;
	}
	void setup() {
		return;
	}

	EmptyPeripheral() {
		return;
	}

	~EmptyPeripheral() {
		return;
	}
};