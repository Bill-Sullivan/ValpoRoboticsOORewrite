#pragma once

/**
 * \class Peripheral
 *
 * \ingroup Peripheral
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This class is the parent class for all other drive trains
 *
 * This class is the parent class for all other drive trains
 * 
 * The only way this class should be used is as a parent class for other classes
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

#include "StandardHeader.hpp"

#include <Servo.h>


class Peripheral {
  protected:
  Peripheral () {}  
	public:
	/**
	* \brief ensure the robot enters a safe state when connection to the controller is lost
	*/
	virtual void doNotConnectedThing();
	/**	
	* \brief the implementation of doThing should implement what happens when the controller is connected
	*/
	virtual void doThing();
	/**	
	*
	* \brief sets initial values of variables
	*/
	virtual void setup();
};
