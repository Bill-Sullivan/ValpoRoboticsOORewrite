#pragma once
#include "PressureSensor.hpp"


void PressureSensor::doThing() {	
	if (digitalRead(sensorInputPin) == LOW) {
		digitalWrite(compresorOnPin, LOW);
	} else if (digitalRead(sensorInputPin) == HIGH) {
		digitalWrite(compresorOnPin, HIGH);
	}	
	return;
}
	
void PressureSensor::doNotConnectedThing() {
	digitalWrite(compresorOnPin, LOW);
	return;
}

void PressureSensor::setup() {	
	pinmode(compresorOnPin, output);
	pinmode(sensorInputPin, input);
	
	return;
}

PressureSensor::PressureSensor(uint8_t _compresorOnPin, uint8_t _sensorInputPin) {
	compresorOnPin = _compresorOnPin;
	sensorInputPin = _sensorInputPin;
	
	return;
}


