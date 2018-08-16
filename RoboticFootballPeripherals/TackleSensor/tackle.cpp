#pragma once
#include "tackle.hpp"

bool TackleSeansor::checkTackled()  {			
	return !digitalRead(TACKLE_INPUT);			
}	

void TackleSeansor::handelTackle() {
if (checkTackled()) {
		led->setColor(led->tackledColor);
	} else {
		led->setColor(led->notTackeledColor);
	}
}

void TackleSeansor::doNotConnectedThing() {
	led->setColor(BLUE);			
}

void TackleSeansor::doThing() {
	handelTackle();
}

void TackleSeansor::setup() {
	pinMode(TACKLE_INPUT, INPUT); // define the tackle sensor pin as an input
	return;
}

TackleSeansor::TackleSeansor(LED* _pLED) {
	led = _pLED;		
}