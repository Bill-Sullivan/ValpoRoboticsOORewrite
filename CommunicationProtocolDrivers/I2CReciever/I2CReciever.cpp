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

/*
  Bus pirate I2C commands
  {0x10 0x41 0x03 0 0 0xA6]
  {0x10 0x41 0x03 0 0 0x5A]
  {0x10 0x41 0x03 0 0 0x00] 
  {0x10 0x41 0x03 0 0 0x20]
*/

void I2CReciever::readMessage() {
  unsigned long timeSinceLastByteRead;
  MessageStruct tmpMessage;  
  if (messageAvaliable) {
      Serial.println("Read addr");
      if (Wire.available()) {
        tmpMessage.regAddress = Wire.read();
      }
      Serial.println("Read len");
      timeSinceLastByteRead = micros();
      while (!Wire.available()) {
        if(micros() - timeSinceLastByteRead > TIMEOUT_TIME) {
          Wire.flush();
          messageAvaliable = false;
          return;
        }
      }
      tmpMessage.len = Wire.read();
      Serial.println("Read data");
      for (int bytesRead = 0; bytesRead < tmpMessage.len; bytesRead++) {
        while (!Wire.available()) {
          if(micros() - timeSinceLastByteRead > TIMEOUT_TIME) {
            Wire.flush();
            messageAvaliable = false;
            Serial.println(bytesRead);
            return;            
          }
        }
        tmpMessage.msgBuffer[bytesRead] = Wire.read();
        Serial.println(bytesRead);
        Serial.println(tmpMessage.msgBuffer[bytesRead]);
      }
      message = tmpMessage;
      
      Serial.println(message.msgBuffer[0]);
      Serial.println(message.msgBuffer[1]);
      Serial.println(message.msgBuffer[2]);
      
      Serial.println("Done");
            
      // consider removing if more than one set of commands is ever used
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
