#pragma once

/**
 * \class TackleSeansor
 *
 * \ingroup Peripheral
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This class controls the tackle sensor and its interaction with the LEDs
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
#include "../LED/LED.hpp"


#include "../../Peripheral.hpp"

#define GREEN 'g'
#define RED   'r'
#define BLUE  'b'

#if !defined(PS3_VARS)
	//Include libraries
	#include <PS3BT.h>
	#include <usbhub.h>
	USB Usb;
	USBHub Hub1(&Usb);
	BTD Btd(&Usb);
	PS3BT PS3(&Btd);
	
	#define PS3_VARS
#endif

#define TACKLE_INPUT    6           // Tackle sensor is wired to pin 6

class TackleSeansor : public Peripheral {
private:	
	/**
	* \brief pointer to the one LED object that a robot has
	* used to set the color of the leds when the robot is tackled 
	* and restor them when it recovers
	*/
	LED* led;

	/**
	* \brief uses tackle sensor to determine if robot is tackled
	*/
	bool checkTackled();	
	/**
	* \brief sets led color based if the robot is tackled
	*/
	void handelTackle();

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
	/**	
	*
	* \brief initilizes pointer to LED
	*/	
	TackleSeansor(LED* _pLED);
};

#include "tackle.cpp"