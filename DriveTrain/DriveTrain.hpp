#pragma once

/**
 * \class DriveTrain
 *
 * \ingroup DriveTrain
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This class is the parent class for all other drive trains
 *
 * This class is the parent class for all other drive trains
 * 
 * The only way this class should be used is as a parent class for other classes
 * 
 *
 * \note Attempts at zen rarely work.
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

#include "../StandardHeader.hpp"

class DriveTrain {
public:
	/**	
	*
	* \brief the implementation of eStop should implement what happens when the controller disconnects
	* Make sure this code results in the robot stopping or we will break anouther door 
	*/
	virtual void eStop() override;
	/**	
	*
	* \brief the implementation of doThing should implement what happens when the controller is connected
	*/
	virtual void doThing() override;
	/**	
	*
	* \brief the implementation of setup should implement setup code
	*/
	virtual void setup() override;
};
