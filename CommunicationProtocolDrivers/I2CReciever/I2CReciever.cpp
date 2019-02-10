#pragma once

#include <Arduino.h>
#include "I2CReciever.hpp"

bool* pMessageFlag;

void readIntoBuffer(int howMany) {
  *pMessageFlag = true;  
}

void I2CReciever::setup() {
  pMessageFlag = &messageAvaliable;
  messageAvaliable = false;
  Wire.begin(8);                  // join i2c bus with address #8
  Wire.onReceive(readIntoBuffer); // register event
}

void I2CReciever::readMessage() {
  if (messageAvaliable) {
      if (Wire.available()) {
        message.regAddress = Wire.read();
      }
            
      while (!Wire.available());
      message.len = Wire.read();

      for (int bytesRead = 0; bytesRead < message.len; bytesRead++) {
        while (!Wire.available());
        message.msgBuffer[bytesRead] = Wire.read();
      }
      
      Wire.flush();      
      messageAvaliable = false;
  }    
}

void I2CReciever::printMessage() {
  int bytesPrinted = 0;
  for (int bytesPrinted = 0; bytesPrinted < message.len; bytesPrinted++) {
    Serial.println(message.msgBuffer[bytesPrinted]);
  }
}
