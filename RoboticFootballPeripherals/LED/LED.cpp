#pragma once
#include "LED.hpp"

void LED::setColor(char color) {
	if (color == RED) {
		digitalWrite(RED_LED,   HIGH);
		digitalWrite(GREEN_LED, LOW);
		digitalWrite(BLUE_LED, LOW);
	}
	if (color == GREEN) {
		digitalWrite(RED_LED,   LOW);
		digitalWrite(GREEN_LED, HIGH);
		digitalWrite(BLUE_LED, LOW);
	}
	if (color == BLUE) {
		digitalWrite(RED_LED,   LOW);
		digitalWrite(GREEN_LED, LOW);
		digitalWrite(BLUE_LED, HIGH);
	}
}

void LED::setup() {
	tackledColor = RED;
	#if defined(TACKLE)
		notTackeledColor = RECIEVER_COLOR;
	#else
		notTackeledColor = LINEMAN_COLOR;
	#endif
	
	  //define pins for LEDs as outputs
	pinMode(BLUE_LED,  OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	pinMode(RED_LED,   OUTPUT);
	flashLed();                   // call the function to test functionality of all three LED colors individually
	setColor(notTackeledColor);
}

void LED::flashLed() {
		//flash the leds
		setColor(GREEN);
		delay(300);
		setColor(BLUE);
		delay(300);
		setColor(RED);
		delay(300);
		setColor(GREEN);
		delay(300);
		setColor(BLUE);
	}