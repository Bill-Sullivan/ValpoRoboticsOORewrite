#pragma once
#include "NewOmniDrive.hpp"

void NewOmniDrive::eStop() {
	motor1.writeMicroseconds(1500);
	motor2.writeMicroseconds(1500);
	motor3.writeMicroseconds(1500);
	motor4.writeMicroseconds(1500);
}

void NewOmniDrive::handelInputs() {
	leftInputY  = map(PS3.getAnalogHat(LeftHatY), 0, 255, -90, 90);  // Recieves PS3 forward/backward input
	leftInputX  = map(PS3.getAnalogHat(LeftHatX), 0, 255, -90, 90);  // Recieves PS3 forward/backward input)
		
    rightInputX = map(PS3.getAnalogHat(RightHatX), 0, 255, -MAX_TURN, MAX_TURN); // Recieves PS3 rotation input 
	
	
	if (abs(leftInputY) < 8) leftInputY = 0;                            // deals with the stickiness
	if (abs(leftInputX) < 8) leftInputX = 0;							// of PS3 joysticks
    if (abs(rightInputX) < 8) rightInputX = 0;
}

void NewOmniDrive::drive() {
	int motor1Drive, motor2Drive, motor3Drive, motor4Drive;
	static int rightLeft, forwardBackword, turn;
	static int motor1Input, motor2Input, motor3Input, motor4Input;
	
	if (forwardBackword < leftInputY)		forwardBackword++;		// Accelerates
    else if (forwardBackword > leftInputY) forwardBackword--;     // Decelerates
	
	if (rightLeft < leftInputX)		rightLeft++;				// Accelerates
    else if (rightLeft > leftInputX) rightLeft--;             // Decelerates
	
	if (turn < rightInputX)		turn++;				// Accelerates
    else if (turn> rightInputX)	turn--;             // Decelerates	
	
	motor1Drive	= ((-1*forwardBackword +           - turn) / handicap) + motorCorrect + 90;
	motor2Drive = ((                   + rightLeft - turn) / handicap) + motorCorrect + 90;
	motor3Drive = ((   forwardBackword +           - turn) / handicap) + motorCorrect + 90;
	motor4Drive = ((                   - rightLeft - turn) / handicap) + motorCorrect + 90;
	
	if (motor1Drive < 5)motor1Drive = 5;
	else if (motor1Drive > 175)motor1Drive = 175;
	if (motor2Drive < 5)motor2Drive = 5;
	else if (motor2Drive > 175)motor2Drive = 175;
	if (motor3Drive < 5)motor3Drive = 5;
	else if (motor3Drive > 175)motor3Drive = 175;
	if (motor4Drive < 5)motor1Drive = 5;
	else if (motor4Drive > 175)motor4Drive = 175;
	
	if (motor1Drive > motor1Input)motor1Input++;
	else if (motor1Drive < motor1Input)motor1Input--;
	if (motor2Drive > motor2Input)motor2Input++;
	else if (motor2Drive < motor2Input)motor2Input--;
	if (motor3Drive > motor3Input)motor3Input++;
	else if (motor3Drive < motor3Input)motor3Input--;
	if (motor4Drive > motor4Input)motor4Input++;
	else if (motor4Drive < motor4Input)motor4Input--;
	
	motor1.write(motor1Input);
	motor2.write(motor2Input);
	motor3.write(motor3Input);
	motor4.write(motor4Input);
}

void NewOmniDrive::setup() {
	motorCorrect = 0;
	inverting = 0;
	motorReverse = 0;
	turnHandicap = 1;
	
	handicap = DEFAULT_HANDICAP;
	
	motor1.attach(MOTOR_1, 1000, 2000);
	motor1.writeMicroseconds(1500);
	motor2.attach(MOTOR_2, 1000, 2000);
	motor2.writeMicroseconds(1500);
	motor3.attach(MOTOR_3, 1000, 2000);
	motor3.writeMicroseconds(1500);
	motor4.attach(MOTOR_4, 1000, 2000);
	motor4.writeMicroseconds(1500);			
}

void NewOmniDrive::doThing() {
		handelInputs();
		drive();		
	}