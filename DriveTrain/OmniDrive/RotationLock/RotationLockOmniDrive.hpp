#pragma once

/**
 * \class RotationLock
 *
 * \ingroup Peripheral
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief This class should handel rotation lock, it doesn'table
 * someone should fix that
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

#include "../../../StandardHeader.hpp"

#include <Servo.h>
#include <EEPROM.h>


#include "../OmniDrive.hpp"

class RotationLock : public omniDriveConrtoller {
	// no idea how this works we may redo the whole thing anyway
private:
public:
};