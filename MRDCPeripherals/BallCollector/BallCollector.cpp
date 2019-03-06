#pragma once
#include "BallCollector.hpp"

#define DELAY 200

void ServoBallCollector::doThing() {
	static bool forwardDelayFlag;
	static bool backwardDelayFlag;
	
	static long unsigned int timer;
	
	if (PS3.getButtonClick(forwardButton)) {
		Serial.println("forward");
		collector.attach(pin, 500,3000);
		collector.write(135);
		forwardDelayFlag = true;
		backwardDelayFlag = false;
		
		timer = millis();
		Serial.println(timer);
	} else if (PS3.getButtonClick(backwordButton)) {
		
		Serial.println("back");
		collector.attach(pin, 500,3000);
		collector.write(45);
		
		forwardDelayFlag  = false;
		backwardDelayFlag = true;
		
		timer = millis();
	}
	
	if ((timer + DELAY) < millis() && (forwardDelayFlag  == true || backwardDelayFlag == true)) {
		Serial.println("done");
		Serial.println(millis());
		Serial.println(timer + DELAY);
		
		forwardDelayFlag  = false;
		backwardDelayFlag = false;
		
		collector.detach();
	} else if (forwardDelayFlag  == true || backwardDelayFlag == true) { 
		Serial.println("millis");
		Serial.println(millis());
		Serial.println(timer + DELAY);
	}
	
	
	
  return;
}
	
void ServoBallCollector::doNotConnectedThing() {
	collector.detach();
	return;
}

void ServoBallCollector::setup() {
	return;
}

ServoBallCollector::ServoBallCollector(uint8_t _pin, ButtonEnum _forwardButton, ButtonEnum _backwordButton) {
	pin = _pin;
	forwardButton = _forwardButton;
	backwordButton = _backwordButton;
	return;
}


