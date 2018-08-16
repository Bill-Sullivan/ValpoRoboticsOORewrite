#pragma once
#include "QBArm.hpp"

void QBArm::qbThrowerCTRL()
{
	if (PS3.getButtonPress(TRIANGLE))    qbThrower.write(TRIANGLE_THROW);

	else if (PS3.getButtonPress(CIRCLE)) qbThrower.write(CIRCLE_THROW);
	else if (PS3.getButtonPress(CROSS))  qbThrower.write(CROSS_THROW );
	else if (PS3.getButtonPress(SQUARE)) qbThrower.write(SQUARE_THROW);
	else if (PS3.getButtonPress(R1))
	{
		qbThrower.write(RELOAD_THROW);
	}
	else qbThrower.writeMicroseconds(1500);
}

void QBArm::setup() {
	qbThrower.attach(QB_THROWER);
	qbThrower.writeMicroseconds(1500);
}

void QBArm::doThing() {		
	qbThrowerCTRL();
	return;
}

void QBArm::doNotConnectedThing() {		
	qbThrower.writeMicroseconds(1500);
	return;
}