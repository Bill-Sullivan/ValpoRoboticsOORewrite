#pragma once
#include "AirCannonRamRod.hpp"

void AirCannonRamRod::doThing() {
	if (PS3.getButtonPress(ramButton)) {
		rammer.write(RAM_POSITION);
	} else if (PS3.getButtonPress(ramButton)) {
		rammer.write(RETURN_POSITION);
	}
	return;
}
	
void AirCannonRamRod::doNotConnectedThing() {
	// since this is a litteral servo the safest thing to do is to not have the servo move.
	return;
}

void AirCannonRamRod::setup() {
	
	return;
}

AirCannonRamRod::AirCannonRamRod() {
	
	return;
}


