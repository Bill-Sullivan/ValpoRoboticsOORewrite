#pragma once
#include "DropDetector.hpp"

long unsigned int* pEchoStart;
long unsigned int* pEchoLength; 
bool* pTriggered;

void startMeasureEchoLength();
void measureEchoLength();

void measureEchoLength() {	
    *pEchoLength = micros() - *pEchoStart;
    *pTriggered = false;
    
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), startMeasureEchoLength, RISING);
}

void startMeasureEchoLength() {
	//Serial.println("start");
	*pEchoStart = micros();
	attachInterrupt(digitalPinToInterrupt(ECHO_PIN), measureEchoLength, FALLING);
}

void DropDetector::trigger() {
  if (!triggered) {
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
	timeTriggered = micros();
    triggered = true;
  }
}

int DropDetector::getDistance() {
  int distance = echoLength / 58;

  if (echoLength != 0) {
    Serial.print("echoLength: ");
    Serial.println(echoLength);
    Serial.println(distance);
  }
  
  return distance;
	
}

void DropDetector::doThing() {	
  if (micros()-timeTriggered > TRIGGER_TIMEOUT) {
	  triggered==false;
  }
  trigger();
  int distance = getDistance(); 
  if (distance > CLIFF_THRESHOLD) { 
    //PS3.setRumbleOn(10, 255, 0, 0);
    Serial.println("There Is a Cliff");
  } else {
    //PS3.setRumbleOn(0,0,0,0);
    Serial.println("No Cliff");
  }  
  return;
}
	
void DropDetector::doNotConnectedThing() {
	return;
}

void DropDetector::setup() {	
  pEchoStart  = &(this->echoStart);
  pEchoLength = &(this->echoLength);
  pTriggered  = &(this->triggered);
  
  // put your setup code here, to run once:
  pinMode(ECHO_PIN, INPUT); 
  
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), startMeasureEchoLength, RISING);
    
  pinMode(TRIG_PIN, OUTPUT);

  triggered = false;
  return;
}

DropDetector::DropDetector() {
	return;
}


