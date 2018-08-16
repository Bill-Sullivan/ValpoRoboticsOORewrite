#pragma once
#include "BasicDrive.hpp"


void BasicDriveController::eStop() {
	leftMotor.writeMicroseconds(1500);
	rightMotor.writeMicroseconds(1500);
	
	#ifdef DUAL_MOTORS
	leftMotor2.writeMicroseconds(1500);
	rightMotor2.writeMicroseconds(1500);
	#endif
}

void BasicDriveController::handelInputs() {
	if (state == DRIVING) {
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
	} else if (state == KID) {
        handicap = KID_HANDICAP;
    }
	
	if (PS3.getButtonClick(SELECT)) //Switch between tank drive and arcade mode. 0 is arcade 1 is tank
	{
		if (PS3.getButtonPress(L1)) {
			//if (driveCtrl == (void (*)())arcadeDrive) {
			if (driveCtrl == ARCADE_DRIVE) {
				driveCtrl = TANK_DRIVE;
				EEPROM.write(0, TANK_DRIVE);
				Serial.println("TANK_DRIVE");
			}
			//else if (driveCtrl == (void (*)())tankDrive) {
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
		if (state == DRIVING)
		{
			state = KID;
			PS3.setLedRaw(9);               // ON OFF OFF ON
			PS3.setRumbleOn(5, 255, 5, 255);// vibrate both, then left, then right
			handicap = KID_HANDICAP;
		}
		else if (state == KID)
		{
			state = DRIVING;
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
}

const void BasicDriveController::arcadeDrive() {
	int xInput, yInput, throttleL, throttleR;
	static int16_t drive, turn;
	  
    yInput = map(PS3.getAnalogHat(LeftHatY), 0, 255, -90, 90);  // Recieves PS3
    // forward/backward input
    xInput = map(PS3.getAnalogHat(RightHatX), 0, 255, 90, -90); // Recieves PS3
    // horizontal input and
    // sets it to an inverted
    // scale of 90 to -90
 
    if (abs(yInput) < 8) yInput = 0;                            // deals with the stickiness
    if (abs(xInput) < 8) xInput = 0;                            // of PS3 joysticks
 
    if ((yInput == 0) && (xInput == 0))
    { // if no input this should ensure that
      // the motors actually stop, and skip the rest
      // of the drive function
      leftMotor.writeMicroseconds(1500);
      rightMotor.writeMicroseconds(1500);
	  #ifdef DUAL_MOTORS
          leftMotor2.writeMicroseconds(1500);
          rightMotor2.writeMicroseconds(1500);
      #endif
      return;
    }
 
    // Instead of following some sort of
    // equation to slow down acceleration
    // We just increment the speed by one
    // towards the desired speed.
    // The acceleration is then slowed
    // because of the loop cycle time
 
    if (drive < yInput)		 drive++;				// Accelerates
    else if (drive > yInput) drive--;               // Decelerates
 
    if (turn < xInput)		{ turn++; } 
    else if (turn > xInput) { turn--; }
 
    throttleL = LEFT_MOTOR_REVERSE * ((drive + turn) / handicap) + motorCorrect;
    // This is the final variable that
    // decides motor speed.
    throttleR = RIGHT_MOTOR_REVERSE * ((drive - turn) / handicap ) + motorCorrect;
 
    if (throttleL > MAX_DRIVE) throttleL = MAX_DRIVE;
    else if (throttleL < -MAX_DRIVE)throttleL = -MAX_DRIVE;
    if (throttleR > MAX_DRIVE) throttleR = MAX_DRIVE;
    else if (throttleR < -MAX_DRIVE)throttleR = -MAX_DRIVE;
 
	static int counter = 0;
	if (counter++ > 1000){
		counter = 0;
		Serial.println(counter);
		Serial.println(xInput);
	}
	Serial.println(throttleL + 90);
 
    leftMotor.write(throttleL + 90);                // Sending values to the speed controllers
    rightMotor.write(throttleR + 90);
    #ifdef DUAL_MOTORS
      leftMotor2.write(throttleL + 90);                // Sending values to the speed controllers
      rightMotor2.write(throttleR + 90);
    #endif
}

const void BasicDriveController::tankDrive() {
	int rightInput, leftInput, throttleL, throttleR;
	static int8_t leftDrive, rightDrive = 0;
    if (inverting == 0) {
      leftInput = map(PS3.getAnalogHat(LeftHatY), 0, 255, -90, 90);   // Recieves PS3 forward/backward input
      rightInput = map(PS3.getAnalogHat(RightHatY), 0, 255, -90, 90); // Recieves PS3 forward/backward input
    }
    else if (inverting == 1) {
      leftInput = map(PS3.getAnalogHat(RightHatY), 0, 255, 90, -90);  // Recieves PS3 forward/backward input
      rightInput = map(PS3.getAnalogHat(LeftHatY), 0, 255, 90, -90);  // Recieves PS3 forward/backward input
    }
 
    // forward/backward input
    // sets it to an inverted
    // scale of 90 to -90
                                              
    if (abs(leftInput) < 8) leftInput = 0;    // deals with the stickiness
    if (abs(rightInput) < 8) rightInput = 0;  // of PS3 joysticks
 
    if ((leftInput == 0) && (rightInput == 0))
    { // if no input this should ensure that
      // the motors actually stop, and skip the rest
      // of the drive function      
      leftMotor.writeMicroseconds(1500);
      rightMotor.writeMicroseconds(1500);
	  #ifdef DUAL_MOTORS
          leftMotor2.writeMicroseconds(1500);
          rightMotor2.writeMicroseconds(1500);
      #endif
      return;
    }
 
    // Instead of following some sort of
    // equation to slow down acceleration
    // We just increment the speed by one
    // towards the desired speed.
    // The acceleration is then slowed
    // because of the loop cycle time

    if (leftDrive < leftInput)      { leftDrive++; }               // Accelerates
    else if (leftDrive > leftInput) { leftDrive--; }               // Decelerates
	
 
    if (rightDrive < rightInput)      rightDrive++;
    else if (rightDrive > rightInput) rightDrive--;                //Since this is tank drive it is not actually turning
 
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

    #ifdef DUAL_MOTORS
      leftMotor2.write(throttleL + 90);                // Sending values to the speed controllers
      rightMotor2.write(throttleR + 90);
    #endif
}

void BasicDriveController::setup() {
	leftMotor.attach(LEFT_MOTOR, 1000, 2000);
	leftMotor.writeMicroseconds(1500);            //stopped
	rightMotor.attach(RIGHT_MOTOR, 1000, 2000);
	rightMotor.writeMicroseconds(1500);
	#ifdef DUAL_MOTORS
		leftMotor2.attach(LEFT_MOTOR2, 1000, 2000);
		leftMotor2.writeMicroseconds(1500);
		rightMotor2.attach(RIGHT_MOTOR2, 1000, 2000);
		rightMotor2.writeMicroseconds(1500);
	#endif
		if (EEPROM.read(0) == ARCADE_DRIVE || EEPROM.read(0) == TANK_DRIVE) {
			driveCtrl = EEPROM.read(0);
		}
		else {
			driveCtrl = ARCADE_DRIVE;
			EEPROM.write(0, ARCADE_DRIVE);
		}
		
		state = DRIVING;
		inverting = 0;
		motorCorrect = 0;
		handicap = DEFAULT_HANDICAP;
}

void BasicDriveController::doThing() {
		handelInputs();
		if (driveCtrl == ARCADE_DRIVE) {
			arcadeDrive();
		}
		else if (driveCtrl = TANK_DRIVE) {
			tankDrive();
		}
	}