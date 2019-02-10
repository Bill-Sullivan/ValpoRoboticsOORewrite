#pragma once

#include <Wire.h>
#include <stdint.h>
#include <Arduino.h>

#define BUFFER_SIZE 10

typedef struct MessageStruct {
  uint8_t regAddress;
  uint8_t len;
  int8_t msgBuffer[BUFFER_SIZE];
} MessageStruct;

class I2CReciever {
  protected:

  public:
    MessageStruct message;
    bool messageAvaliable;
    unsigned long lastTimeWriten;
    void setup();
    void printMessage();
    void readMessage();
};

#include "I2CReciever.cpp"
