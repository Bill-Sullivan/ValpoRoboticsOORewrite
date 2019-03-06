/*
  __/\\\\\\\\\\\\\\\______________________________________________________
   _\/\\\///////////_______________________________________________________
   _\/\\\_____________________________________________/\\\_________________
    _\/\\\\\\\\\\\_______/\\/\\\\\\\____/\\/\\\\\\____\///_______/\\\\\\\\__
     _\/\\\///////_______\/\\\/////\\\__\/\\\////\\\____/\\\____/\\\/////\\\_
      _\/\\\______________\/\\\___\///___\/\\\__\//\\\__\/\\\___/\\\\\\\\\\\__
       _\/\\\______________\/\\\__________\/\\\___\/\\\__\/\\\__\//\\///////___
        _\/\\\\\\\\\\\\\\\__\/\\\__________\/\\\___\/\\\__\/\\\___\//\\\\\\\\\\_
         _\///////////////___\///___________\///____\///___\///_____\//////////__

      \WWWWWWW/
    _/`  o_o  `\_
   (_    (_)    _)
     \ '-...-' /
     (`'-----'`)
      `"""""""`

  Ernie Base Drive Code

    Parts List
  ---------------------------------
  Uses USBHostShield 2.0
  Arduino Mega ADK
  USB Bluetooth Dongle - some models not supported
  PS3 Controller - name brand recommended
  ---------------------------------
*/


#pragma once

#define BASIC_DRIVETRAIN
#define PERF_BOARD_SHIELD
#define DUAL_MOTORS

#define CIM_MOTOR

//#define DROP_DETECTOR_2
//#define DROP_DETECTOR_3


#define BRIDGE_MODE_ENABLED

#define BALL_SHOOTER // the flywheel thing
#define BOX_LIFTER   // the linear actuator that lifts the box.
#define BALL_PICKUP  // the motors that
#define SERVO_BALL_COLLECTOR // dont know if this will be a thing

#if defined(BALL_SHOOTER)
  #define BALL_SHOOTER_PIN 4
  #define SHOOT_BALL_FORWARD  TRIANGLE
  #define SHOOT_BALL_BACKWORD CROSS
  #define BALL_SHOOTER_POWER  500
#endif

#if defined(BOX_LIFTER) 
  #define BOX_ACTUATOR_PIN 5
  #define RAISE_BOX_BUTTON UP
  #define LOWER_BOX_BUTTON DOWN
  #define BOX_LIFT_SPEED 250
#endif 

#if defined(BALL_PICKUP) 
  #define BALL_PICKUP_PIN 6
  #define BALL_PICKUP_MOTOR_UP   SQUARE
  #define BALL_PICKUP_MOTOR_DOWN CIRCLE
  #define BALL_PICKUP_MOTOR_POWER 500 // speed which the motors move
#endif 


#if defined(SERVO_BALL_COLLECTOR) 
  #define SERVO_BALL_COLLECTOR_PIN                  12
  #define SERVO_BALL_COLLECTOR_CLOCKWISE_BUTTON     LEFT
  #define SERVO_BALL_COLLECTOR_ANTICLOCKWISE_BUTTON RIGHT
#endif
