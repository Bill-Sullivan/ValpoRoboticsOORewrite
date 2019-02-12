#pragma once 
#include "AutonomousBasicDrive.hpp"

void AutonomousBasicDrive::handelCommands() {  
  BasicDriveController::inverting = 0;
  BasicDriveController::driveCtrl = ARCADE_DRIVE;
  BasicDriveController::handicap  = DEFAULT_HANDICAP;
  BasicDriveController::kidsMode  = false;
    
  reciever.readMessage();
  
  BasicDriveController::rightInputY = reciever.message.msgBuffer[0];
  BasicDriveController::rightInputX = reciever.message.msgBuffer[1];
  BasicDriveController::leftInputY  = reciever.message.msgBuffer[2];
  
  //Serial.println(leftInputY);
  
  return;
}

void AutonomousBasicDrive::handelInputs() {
  if (PS3.getButtonClick(TRIANGLE)) {
    Serial.println("Entering Auto");
    autonomous = true;
  }
  if (PS3.getButtonClick(CIRCLE)) {
    Serial.println("Leaving Auto");
    autonomous = false;
  }
  
  return;
}

void AutonomousBasicDrive::doThing() {
  //Serial.println("AutonomousBasicDrive");
  handelInputs();
  if (autonomous) {
    handelCommands();
  } else {
    BasicDriveController::handelInputs();
  }
  BasicDriveController::arcadeDrive();
  
  //reciever.printMessage();  
  return;
}

void AutonomousBasicDrive::setup() {
  Serial.println("AutonomousBasicDrive Setup");
  reciever.setup();
  BasicDriveController::setup();
  autonomous = false;
  return;
}