#pragma once
#include "center.hpp"


void Center::centerCtrl()
{
  if (PS3.getButtonClick(TRIANGLE)) centerRelease.write(CENTER_RELEASE_UP);
  else if (PS3.getButtonClick(CROSS)) centerRelease.write(CENTER_RELEASE_DOWN);
}

void Center::setup() {
	centerRelease.attach(CENTER_RELEASE);   // attach ball release servo to its pin
	centerRelease.write(CENTER_RELEASE_UP); // 
	return;
}

void Center::doNotConnectedThing() {
	return;
}

void Center::doThing() {
	centerCtrl();
}

Center::Center() {
	
}