#pragma once

#include "PS3ControllerRumbler.hpp"
void PS3ControllerRumbler::setRumbleOn(int16_t rightDuration, uint8_t rightPower, int16_t leftDuration, uint8_t leftPower) {
	long unsigned int currTime = millis();
	long unsigned int remainingLeftTime  = currTime - leftStartTime;
	long unsigned int remainingRightTime = currTime - rightStartTime;
	
	
	int16_t rightRumbleTime;
	int16_t leftRumbleTime;
	
	if (rightDuration > remainingRightTime) {
		rightRumbleTime = rightDuration;
		rightStartTime  = currTime;
	} else {
		rightRumbleTime = remainingRightTime;
	}
	
	if (leftDuration > remainingLeftTime) {
		leftRumbleTime = leftDuration;
		leftStartTime  = currTime;
	} else {
		leftRumbleTime = remainingLeftTime;
	}
	
	if (rightDuration < 0) {
		rightDuration = 0;
		rightPower = 0;
	}
	if (leftDuration < 0) {
		leftDuration = 0;
		leftPower = 0;
	}
	if ((leftDuration == 0 && rightDuration == 0 ) or  (rightPower == 0 && leftPower == 0)) {
		PS3.setRumbleOff();
	} else {
		PS3.setRumbleOn(rightRumbleTime/20, rightPower, leftRumbleTime/20, leftPower);
	}
	
	if (PS3.getButtonPress(PS)) {
		PS3.disconnect();
	}
	
	
}