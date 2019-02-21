#pragma once
#include "ButtonMotorMover.hpp"

void ButtonMotorMover::doThing() {
	if (PS3.getButtonPress(forward)) {
		motor.writeMicroseconds(1500 + speed);
	} else if (PS3.getButtonPress(backword)) {
		motor.writeMicroseconds(1500 - speed);
	} else {
		motor.writeMicroseconds(1500 + 0);
	}
	return;
}
	
void ButtonMotorMover::doNotConnectedThing() {
	motor.writeMicroseconds(1500);
	return;
}

void ButtonMotorMover::setup() {
	motor.attach(pin, 1000, 2000);
	return;
}

ButtonMotorMover::ButtonMotorMover(uint8_t _pin, ButtonEnum _forward, ButtonEnum _backword, uint16_t _speed) {
	pin 	 = _pin;
	forward  = _forward;
	backword = _backword;
	speed	 = _speed;
	return;
}
