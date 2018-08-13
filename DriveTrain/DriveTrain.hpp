#pragma once

#include "../StandardHeader.hpp"

class DriveTrain {
	public:
		virtual void eStop();
		virtual void doThing();
		virtual void setup();
};
