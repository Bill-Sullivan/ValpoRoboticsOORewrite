#include "Robot.hpp"
#include "StandardHeader.hpp"

Robot robot;

void setup () {
  pinMode (13, OUTPUT);
  
	robot.setup();
	Serial.println(" \n setup Over Start Loop");
}

void loop () {
	robot.loop();
	//Serial.println(" \n Loop over ");

  if (PS3.PS3Connected) {
    //Serial.print(F("\r\nPS3 Connected"));

    if (PS3.getButtonClick(CIRCLE)) {
      Serial.println("Start Pressed");
      
      digitalWrite(13, digitalRead(13) ^ 1);   // toggle LED pin
    } 
  }
}
