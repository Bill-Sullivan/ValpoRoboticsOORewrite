#pragma once

/**
 * \class Kicker
 *
 * \ingroup Peripheral
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This class controls the kicker peripheral
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

#include "../../StandardHeader.hpp"

#include <Servo.h>

#include "../../Peripheral.hpp"


#define KICKER_MOTOR          5     // Kicker motor is wired to pin 5
	//these are the speeds for kicking and reload the kicker foot
#define KICKER_POWER          175   
#define KICKER_RELOAD         85

class Kicker : public Peripheral {
private:
	/**	
	* \brief reponds to controller input and controls the kicker foot
	*/
	void kickerCtrl();
	/**	
	* \brief kicker motor is modeled as a servo
	*/
	Servo kicker;                       // Define motor object for the kicker motor
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

#include "kicker.cpp"