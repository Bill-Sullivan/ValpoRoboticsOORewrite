#pragma once

#include "../../StandardHeader.hpp"

#include <Servo.h>


#define RED_LED         11          //Red LED control is wired to pin 11
#define GREEN_LED       12          //Green LED control is wired to pin 12
#define BLUE_LED        13          //Blue LED control is wired to pin 13

#define GREEN 'g'
#define RED 'r'
#define BLUE 'b'

#define RECIEVER_COLOR BLUE
#define LINEMAN_COLOR GREEN
  
  
  
  
class LED  {
	private:	
	public:
  char tackledColor = RED;
  
  #if defined(TACKLE)
    char notTackeledColor = RECIEVER_COLOR;
  #else
    char notTackeledColor = LINEMAN_COLOR;
  #endif
  
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
