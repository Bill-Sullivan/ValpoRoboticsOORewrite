#pragma once

/**
 * \class AutonomousBasicDrive
 *
 * \ingroup DriveTrain
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This class allows the robots drivetrain to be controled over I2C
 *
 * \author  <!-- ((last to touch it) --> Bill Sullivan
 *
 * \version $Revision: 1.0 
 *
 * \date  2019/2/10 14:16:20
  <!-- YYYY/MM/DD -->
 * 
 *
 * Created on: 2019/2/10 14:16:20
 */


#include "../../../StandardHeader.hpp"
#include "../../SharedDefinitions.hpp"

#include "../../../CommunicationProtocolDrivers/I2CReciever/I2CReciever.hpp"
#include "../BasicDrive.hpp"

class AutonomousBasicDrive : public BasicDriveController {
protected:
	bool autonomous;
  I2CReciever reciever;
  void handelCommands();
  void handelInputs();
  
public:
  /**	
	*
	* \brief doThing controls the calls functions that handel inputs and control motors 
	* calls functions that handel inputs and places those inputs into variables to be used later
	* Then selects which control mode to use based on user input
	* then calls a drivetrain funcion
	*/
	void doThing();
	/**	
	*
	* \brief sets initial values of variables and motors
	*/
	void setup();
};

#include "AutonomousBasicDrive.cpp"