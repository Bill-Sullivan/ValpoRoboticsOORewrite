#pragma once
#include "Vacuum.hpp"

void Vacuum::doThing() {
	if (PS3.getButtonPress(suckButton)) {
		vacuumMotor.writeMicroseconds(VACUUM_SPEED);
	} else {
		vacuumMotor.writeMicroseconds(1500 + 0);
	}
	return;
}
	
void Vacuum::doNotConnectedThing() {
	vacuumMotor.writeMicroseconds(1500);
	return;
}

void Vacuum::setup() {	 	
	vacuumMotor.attach(pin, 1000, 2000);
	return;
}

Vacuum::Vacuum(uint8_t _pin, ButtonEnum _suckButton, uint16_t _vacuumSpeed) {
	pin         = _pin;
	suckButton  = _suckButton;
	vacuumSpeed = _vacuumSpeed;
	return;
}


