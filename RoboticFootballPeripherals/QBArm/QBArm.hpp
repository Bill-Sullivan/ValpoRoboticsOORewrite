#pragma once

/**
* \class TestClass
*
* \ingroup PackageName
* (Note, this needs exactly one \defgroup somewhere)
*
* \brief Provide an example
*
* This class is meant as an example.  It is not useful by itself
* rather its usefulness is only a function of how much it helps
* the reader.  It is in a sense defined by the person who reads it
* and otherwise does not exist in any real form.
*
* \note Attempts at zen rarely work.
*
* \author (last to touch it) $Author: bv Bill Sullivan$
*
* \version $Revision: 1.0 $
*
* \date $Date: 2018/04/14 14:16:20 $
*
*
* Created on:
*
* $Id: doxygen-howto2.html,v 1.5 2018/04/14 14:16:20 bv Exp $
*
*/

// both of these headers locations maybe diffrent depending on where your peripheral is
#include "../../StandardHeader.hpp" // This includes the standard header, which has the libraries needed in every file, and deals with the PS3 Controller stuff
#include "../../Peripheral.hpp"    // this inculdes the parent class of all peripherals

#include <Servo.h>

#define QB_THROWER            5

#define TRIANGLE_THROW        175
#define CIRCLE_THROW          125
#define CROSS_THROW           108

#define SQUARE_THROW          102
#define RELOAD_THROW          88

class QBArm : public Peripheral {
private:
	//place variables that need to be accesed by multiple methods here
	Servo qbThrower;
public:
	QBArm() {
		qbThrower.attach(QB_THROWER);
		qbThrower.writeMicroseconds(1500);
	}

	void qbThrowerCTRL();

	void doThing() {
		// code for what should happen every loop goes here
		qbThrowerCTRL();

		return;
	}
	void doNotConnectedThing() {
		// code for what should happen when the controller disconeects 
		qbThrower.writeMicroseconds(1500);

		return;
	}
};


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