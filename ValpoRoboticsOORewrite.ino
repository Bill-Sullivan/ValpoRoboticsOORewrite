#include "Robot.hpp"
#include "StandardHeader.hpp"

#pragma GCC optimize ("-O2")

Robot robot;

double approxAverage (double new_value) {
    static double oldValue = 0;
    double alpha = 0.8;
    oldValue = (alpha * new_value) + (1.0 - alpha) * oldValue;
    return oldValue;
}

void setup () { 
	robot.setup();
	
}

//#define PROFILING
void loop () {
#if defined(PROFILING)
  #define NUM_LOOPS 1000
  static int loopCounter = 0;
  static unsigned long startLoopTime = micros();
#endif
	robot.loop();
 #if defined(PROFILING)
  if (loopCounter >= NUM_LOOPS) {
    loopCounter = 0;
    unsigned long loopTime = micros() - startLoopTime;
    Serial.println(loopTime/NUM_LOOPS);
    startLoopTime = micros();
  } else {
    loopCounter++;
  }
  #endif
}
