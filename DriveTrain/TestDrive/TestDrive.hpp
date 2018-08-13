#pragma once

#include "../../StandardHeader.hpp"
#include "../DriveTrain.hpp"

class testDriveConrtoller: public DriveTrain {
	public:
	void eStop() {
		Serial.println("Estop");
		return;
	}
	void doThing() {
		Serial.println("doThing");
		return;
	}
};