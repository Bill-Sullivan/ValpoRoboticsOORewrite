#pragma once

#include "StandardHeader.hpp"

#include <Servo.h>


class Peripheral {
	public:
	virtual void doThing();
	virtual void doNotConnectedThing();
};
