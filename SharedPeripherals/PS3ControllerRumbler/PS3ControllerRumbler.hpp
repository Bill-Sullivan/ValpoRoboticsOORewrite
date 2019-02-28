#pragma once

// ../ means one directory up
#include "../../StandardHeader.hpp" // This includes the standard header, which has the libraries needed in every file, and deals with the PS3 Controller stuff

class PS3ControllerRumbler {
	protected:
		long unsigned int leftRunTime;
		long unsigned int leftStartTime;
		
		long unsigned int rightRunTime;
		long unsigned int rightStartTime;
	public:
		void setRumbleOn(int16_t rightDuration, uint8_t rightPower, int16_t leftDuration, uint8_t leftPower);
};

#include "PS3ControllerRumbler.cpp"