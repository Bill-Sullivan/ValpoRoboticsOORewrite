#pragma once
#include "kicker.hpp"

void Kicker::kickerCtrl()
{
  if (PS3.getButtonPress(CROSS)) kicker.write(KICKER_POWER);
  else if (PS3.getButtonPress(TRIANGLE)) kicker.write(KICKER_RELOAD);
  else kicker.writeMicroseconds(1500);
  return;
}

void Kicker::setup() {
		kicker.attach(KICKER_MOTOR, 1000, 2000);
		kicker.writeMicroseconds(1500);
		return;
	}
	
void Kicker::doNotConnectedThing() {
	return;
}

void Kicker::doThing() {
	kickerCtrl();
	return;
}

Kicker::Kicker() {
}