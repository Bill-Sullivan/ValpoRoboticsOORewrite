#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <stdint.h>

#include "Peripheral.hpp"
#include "tackle.hpp"

#if !defined(PS3_VARS)
	//Include libraries
	#include <PS3BT.h>
	#include <usbhub.h>
	USB Usb;
	USBHub Hub1(&Usb);
	BTD Btd(&Usb);
	PS3BT PS3(&Btd);
	
	#define PS3_VARS
#endif


  #define RED_LED         11          //Red LED control is wired to pin 11
  #define GREEN_LED       12          //Green LED control is wired to pin 12
  #define BLUE_LED        13          //Blue LED control is wired to pin 13
  
  #define GREEN 'g'
  #define RED 'r'
  #define BLUE 'b'
  
  #define RECIEVER_COLOR BLUE
  #define LINEMAN_COLOR GREEN
  
  
  
  
class LED : public Peripheral {
	private:
	TackleSensor tackleSensor;
	
	
	char tackledColor = RED;
	
	#if defined(TACKLE)
		notTackeledColor = RECIEVER_COLOR;
	#elsif
		notTackeledColor = LINEMAN_COLOR;
	#endif
	
	void handelTackle() {
	#if defined(TACKLE)
		if (tackleSensor.checkTackle()) {
			setColor(tackledColor);
		} else {
			setColor(notTackeledColor);
		}
	}
	#elsif 
		setColor(notTackeledColor);
	#endif
	}
	
	public:
	void doNotConnectedThing() {
		setColor(BLUE);
	}
	void doThing() {
		handelTackle();
	}
	void setColor(char color) {
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
	
	
	LED() {
		  //define pins for LEDs as outputs
		pinMode(BLUE_LED,  OUTPUT);
		pinMode(GREEN_LED, OUTPUT);
		pinMode(RED_LED,   OUTPUT);
		flashLed();                   // call the function to test functionality of all three LED colors individually
	}
	void flashLed() {
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
};
