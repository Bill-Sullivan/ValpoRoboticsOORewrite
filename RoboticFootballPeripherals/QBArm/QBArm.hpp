#pragma once

/**
 * \class QBArm
 *
 * \ingroup Peripheral
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This class controls the quaterback's arm
 *
 * \author  <!-- ((last to touch it) --> Bill Sullivan
 *
 * \version $Revision: 1.0 
 *
 * \date  2018/08/15 14:16:20
  <!-- YYYY/MM/DD -->
 * 
 *
 * Created on: 2018/04/14 14:16:20
 */

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
	/**	
	* \brief QBArm motor is modeled as a servo
	*/
	Servo qbThrower;
	/**	
	* \brief reponds to controller input and controls the QBArm foot
	*/
	void qbThrowerCTRL();
public:	
	/**
	* \brief ensure the robot enters a safe state when connection to the controller is lost
	*/
	void doNotConnectedThing();
	/**	
	* \brief the implementation of doThing should implement what happens when the controller is connected
	*/
	void doThing();
	/**	
	* \brief sets initial values of variables
	*/
	void setup();
};

#include "QBArm.cpp"