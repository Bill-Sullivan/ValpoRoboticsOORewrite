#pragma once

/**
 * \class Center
 *
 * \ingroup Peripheral
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This class controls the centers dropper arm
 * this class controlls the dropper arm that drops the football on a snap
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

#define CENTER_RELEASE        5     // the ball release servo is wired to pin 5
#define CENTER_RELEASE_DOWN   120   // these are the angles between 0 and 180 to set servo for releasing and holding the ball
#define CENTER_RELEASE_UP     70    



class Center : public Peripheral {
private:
	void centerCtrl();
	Servo centerRelease;                // define servo object for ball release 
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
	*
	* \brief sets initial values of variables
	*/
	void setup();
	
	Center();
};



#include "center.cpp"