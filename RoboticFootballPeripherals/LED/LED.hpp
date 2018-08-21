#pragma once

/**
 * \class LED
 *
 * \ingroup Peripheral
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This class controls the robots LEDs
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

#if defined(PERF_BOARD_SHIELD)
	#define RED_LED         11          //Red LED control is wired to pin 11
	#define GREEN_LED       12          //Green LED control is wired to pin 12
	#define BLUE_LED        13          //Blue LED control is wired to pin 13
#elif defined(PCB_SHIELD)
	#error "Ask Jackob what pin drives what LED, correct the gessword that is the next three definitions than delete this error"
	#define RED_LED         A1          //Red LED control is wired to pin 11
	#define GREEN_LED       A2          //Green LED control is wired to pin 12
	#define BLUE_LED        A3          //Blue LED control is wired to pin 13
#endif

#define GREEN 'g'
#define RED 'r'
#define BLUE 'b'

#define RECIEVER_COLOR BLUE
#define LINEMAN_COLOR GREEN
  
  
  
  
class LED  {
protected:	
public:
	/**	
	* \brief color the robot should be when tackled
	*/
	char tackledColor;
	/**	
	* \brief color the robot should be when not tackled
	*/
    char notTackeledColor;
	/**	
	* \brief sets initial values of variables
	*/
	void setup();
	/**	
	* \brief sets the color of the LED 
	* \param[in] color The color the LED should be
	* RED   = 'r'
	* BLUE  = 'b'
	* GREEN = 'g'
	*/
	void setColor(char color);
	/**	
	* \brief flash the leds in a perticular pattern	
	* pattern usually runs once when the microcontroller turns on
	* Used to determine if leds are working
	*/
	void flashLed();
};

#include "LED.cpp"