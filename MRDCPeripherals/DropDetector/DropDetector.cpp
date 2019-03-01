#pragma once
#include "DropDetector.hpp"

long unsigned int* pEchoStart_2;
long unsigned int* pEchoStart_3;
long unsigned int* pEchoLength_2;
long unsigned int* pEchoLength_3;
bool* pTriggered_2;
bool* pTriggered_3;

void startMeasureEchoLength_2();
void startMeasureEchoLength_3();
void measureEchoLength_2();
void measureEchoLength_3();

void measureEchoLength_2() {	
    *pEchoLength_2 = micros() - *pEchoStart_2;
    *pTriggered_2  = false;
    
	/*
	Serial.println("echo");
	Serial.println(*pEchoStart_2);
	Serial.println(*pEchoLength_2);
	*/
	attachInterrupt(digitalPinToInterrupt(ECHO_PIN_2), startMeasureEchoLength_2, RISING);
}
void measureEchoLength_3() {	
    *pEchoLength_3 = micros() - *pEchoStart_3;
    *pTriggered_3  = false;
    
	attachInterrupt(digitalPinToInterrupt(ECHO_PIN_3), startMeasureEchoLength_3, RISING);
}

void startMeasureEchoLength_2() {
	*pEchoStart_2 = micros();
	attachInterrupt(digitalPinToInterrupt(ECHO_PIN_2), measureEchoLength_2, FALLING);
}
void startMeasureEchoLength_3() {
	*pEchoStart_3 = micros();
	attachInterrupt(digitalPinToInterrupt(ECHO_PIN_3), measureEchoLength_3, FALLING);
}

void DropDetector::trigger() {
  if (!triggered) {
	digitalWrite(trigPin, HIGH);	    
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
	
	timeTriggered = micros();
    triggered = true;
  }
}

int DropDetector::getDistance() {
  int distance = echoLength / 58;
  /*
  if (echoLength != 0) {
    Serial.print("echoLength: ");
    Serial.println(echoLength);
    Serial.println(distance);
  }
  */
  return distance;
	
}

void DropDetector::doThing() {	
  if (micros()-timeTriggered > TRIGGER_TIMEOUT) {
    triggered=false;
  }
  trigger();
  int distance = getDistance();     
  if (distance > CLIFF_THRESHOLD) { 
    //PS3.setRumbleOn(10, 255, 0, 0);
	if (LEDon == false) {
		if (echoPin == 2) {
		  PS3.setLedOn(LED2);
		} else if (echoPin == 3) {
		  PS3.setLedOn(LED3);
		}	
		LEDon = true;
	}
	Serial.print(echoPin);
    Serial.println(" There Is a Cliff");
  } else {
    //PS3.setRumbleOn(0,0,0,0);
	if (LEDon  == true) {
		if (echoPin == 2) {
		  PS3.setLedOff(LED2);
		} else if (echoPin == 3) {
		  PS3.setLedOff(LED3);
		}
		
		LEDon = false;
	}
	Serial.print(echoPin);
    Serial.println(" No Cliff");
  } 
  
  return;
}
	
void DropDetector::doNotConnectedThing() {
	return;
}

void DropDetector::setup() {		
  if (echoPin == 2) {
	  pEchoStart_2  = &(this->echoStart);
	  pEchoLength_2 = &(this->echoLength);
	  pTriggered_2  = &(this->triggered);
  }
  if (echoPin == 3) {
	  pEchoStart_3  = &(this->echoStart);
	  pEchoLength_3 = &(this->echoLength);
	  pTriggered_3  = &(this->triggered);
  }
  
  
  
  // put your setup code here, to run once:
  pinMode(echoPin, INPUT);
  LEDon = false;
    
  if (echoPin == 2) {
	  attachInterrupt(digitalPinToInterrupt(echoPin), startMeasureEchoLength_2, RISING);
  }
  if (echoPin == 3) {
	  attachInterrupt(digitalPinToInterrupt(echoPin), startMeasureEchoLength_3, RISING);
  }
  
  pinMode(trigPin, OUTPUT);

  triggered = false;
  return;
}

DropDetector::DropDetector(uint8_t _echoPin, uint8_t _trigPin) {
	echoPin = _echoPin;
	trigPin = _trigPin;
	return;
}


