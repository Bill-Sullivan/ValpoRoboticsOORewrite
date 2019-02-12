#pragma once
#include "BasicDrive.hpp"

void BasicDriveController::eStop() {
	leftMotor.writeMicroseconds(1500);
	rightMotor.writeMicroseconds(1500);
}

void BasicDriveController::handelInputs() {
	if (kidsMode == false) {
		if (PS3.getButtonPress(R2)) {
			handicap = ALTERNATE_HANDICAP; // TURBO!!!!!!!!!!!!!!
		}
		else {
			#ifdef LR_TACKLE_PERIPHERALS
				handicap = 1;
			#else
				handicap = DEFAULT_HANDICAP;
			#endif
		}	
	} else if (kidsMode == true) {
        handicap = KID_HANDICAP;
    }
	
	if (PS3.getButtonClick(SELECT))
	{
		if (PS3.getButtonPress(L1)) {
			if (driveCtrl == ARCADE_DRIVE) {
				driveCtrl = TANK_DRIVE;
				EEPROM.write(0, TANK_DRIVE);
				Serial.println("TANK_DRIVE");
			}
			else if (driveCtrl == TANK_DRIVE) {
				driveCtrl = ARCADE_DRIVE;
				EEPROM.write(0, ARCADE_DRIVE);
				Serial.println("ARCADE_DRIVE");
			}
		}
	}
	if (PS3.getButtonClick(START))
	{ // switches between normal driving mode
	// and kid mode
		if (kidsMode == false)
		{
			kidsMode = true;
			PS3.setLedRaw(9);               // ON OFF OFF ON
			PS3.setRumbleOn(5, 255, 5, 255);// vibrate both, then left, then right
			handicap = KID_HANDICAP;
		}
		else if (kidsMode == true)
		{
			kidsMode = false;
			PS3.setLedRaw(1);               // OFF OFF OFF ON
			PS3.setRumbleOn(5, 255, 5, 255);// vibrate both, then left, then right
			handicap = DEFAULT_HANDICAP;				
		}
	}
	if (PS3.getButtonClick(R1)) {       //This inverts the driving for tank drive.
		
		if (inverting == 0) {
			inverting = 1;
			PS3.setRumbleOn(10, 255, 10, 255);
			Serial.println("dont invert Driving");
		}		
		else if (inverting == 1) {
			inverting = 0;
			PS3.setRumbleOn(10, 255, 10, 255);
			Serial.println("invert Driving");
		}
	}
	
	leftInputY = map(PS3.getAnalogHat(LeftHatY), 0, 255, -90, 90);  // Recieves PS3
    // forward/backward input
    rightInputX = map(PS3.getAnalogHat(RightHatX), 0, 255, 90, -90); // Recieves PS3
    // horizontal input and
    // sets it to an inverted
    // scale of 90 to -90
	
	rightInputY = map(PS3.getAnalogHat(RightHatY), 0, 255, -90, 90); // Recieves PS3 forward/backward input
	
	if (abs(leftInputY) < 8) leftInputY = 0;                            // deals with the stickiness
    if (abs(rightInputX) < 8) rightInputX = 0;                            // of PS3 joysticks
	if (abs(rightInputY) < 8) rightInputY = 0;
}

void BasicDriveController::invertInputs() {
	int swapVar;
	if (driveCtrl == tank) {
		if (inverting == 1) {
			swapVar = leftInputY;
			leftInputY = rightInputY;
			rightInputY = swapVar;
		}
	}
	//commented out because driving backward won't work well on our current robots
	else if (driveCtrl == arcade) {
		if (inverting == 1) {
			leftInputY = map(leftInputY,   -90, 90, 90, -90);  // Recieves PS3
			rightInputX = map(rightInputX, -90, 90, 90, -90);  // Recieves PS3
		}
	}		
}

const void BasicDriveController::arcadeDrive() {
	int throttleL, throttleR;
	static int16_t drive, turn = 0;
 
    
 
    if ((leftInputY == 0) && (rightInputX == 0))
    { // if no input this should ensure that
      // the motors actually stop, and skip the rest
      // of the drive function
      eStop();
      return;
    }
 
    // Instead of following some sort of
    // equation to slow down acceleration
    // We just increment the speed by one
    // towards the desired speed.
    // The acceleration is then slowed
    // because of the loop cycle time
 
    if (drive < leftInputY)		 drive++;				// Accelerates
    else if (drive > leftInputY) drive--;               // Decelerates
 
    if (turn < rightInputX)		{ turn++; } 
    else if (turn > rightInputX) { turn--; }
 
    throttleL = LEFT_MOTOR_REVERSE * ((drive + turn) / handicap) + motorCorrect;
    // This is the final variable that
    // decides motor speed.
    throttleR = RIGHT_MOTOR_REVERSE * ((drive - turn) / handicap ) + motorCorrect;
 
    if (throttleL > MAX_DRIVE) throttleL = MAX_DRIVE;
    else if (throttleL < -MAX_DRIVE)throttleL = -MAX_DRIVE;
    if (throttleR > MAX_DRIVE) throttleR = MAX_DRIVE;
    else if (throttleR < -MAX_DRIVE)throttleR = -MAX_DRIVE;
 
    leftMotor.write(throttleL + 90);                // Sending values to the speed controllers
    rightMotor.write(throttleR + 90);
}

const void BasicDriveController::tankDrive() {
	int throttleL, throttleR;
	static int8_t leftDrive, rightDrive = 0;
	
  // forward/backward input
  // sets it to an inverted
  // scale of 90 to -90
                                            
  if (abs(leftInputY) < 8) leftInputY = 0;    // deals with the stickiness
  if (abs(rightInputY) < 8) rightInputY = 0;  // of PS3 joysticks
  
  if ((leftInputY == 0) && (rightInputY == 0))
  { // if no input this should ensure that
    // the motors actually stop, and skip the rest
    // of the drive function      
    eStop();
    return;
  }
  
  // Instead of following some sort of
  // equation to slow down acceleration
  // We just increment the speed by one
  // towards the desired speed.
  // The acceleration is then slowed
  // because of the loop cycle time
  
  if (leftDrive < leftInputY)      { leftDrive++; }               // Accelerates
  else if (leftDrive > leftInputY) { leftDrive--; }               // Decelerates
	
  
  if (rightDrive < rightInputY)      rightDrive++;
  else if (rightDrive > rightInputY) rightDrive--;
  
  throttleL = LEFT_MOTOR_REVERSE  * ((leftDrive) / handicap) + motorCorrect;
  // This is the final variable that
  // decides motor speed.
  throttleR = RIGHT_MOTOR_REVERSE * ((rightDrive) / handicap ) + motorCorrect;
	
  
  if (throttleL > MAX_DRIVE) 		throttleL = MAX_DRIVE;
  else if (throttleL < -MAX_DRIVE)throttleL = -MAX_DRIVE;
  if (throttleR > MAX_DRIVE) 		throttleR = MAX_DRIVE;
  else if (throttleR < -MAX_DRIVE)throttleR = -MAX_DRIVE;
  
	
  leftMotor.write(throttleL + 90);                // Sending values to the speed controllers
  rightMotor.write(throttleR + 90);	
}

void BasicDriveController::setup() {
  Serial.println("BasicDriveController Setup");
	#if !defined(DUAL_MOTORS)
	leftMotor.attach(LEFT_MOTOR, 1000, 2000);	
	rightMotor.attach(RIGHT_MOTOR, 1000, 2000);
	#else 
	leftMotor.attach( LEFT_MOTOR,  LEFT_MOTOR2, 1000, 2000);	
	rightMotor.attach(RIGHT_MOTOR, RIGHT_MOTOR2, 1000, 2000);	
	#endif
	
	leftMotor.writeMicroseconds(1500);            //stopped
	rightMotor.writeMicroseconds(1500);
	
	
  if (ARCADE_DRIVE == EEPROM.read(0)) {
    driveCtrl = arcade;
  }
  if (TANK_DRIVE == EEPROM.read(0)) {
    driveCtrl = tank;
  }
	
	else {
		driveCtrl = arcade;
		EEPROM.write(0, ARCADE_DRIVE);
	}
	
	kidsMode = DRIVING;
	inverting = 0;
	motorCorrect = 0;
	handicap = DEFAULT_HANDICAP;
}

void BasicDriveController::doThing() {
		handelInputs();
		invertInputs();
		if (driveCtrl == ARCADE_DRIVE) {
			arcadeDrive();
		}
		else if (driveCtrl = TANK_DRIVE) {
			tankDrive();
		}
	}