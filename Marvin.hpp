#pragma once

#define BASIC_DRIVETRAIN
#define PERF_BOARD_SHIELD
#define DUAL_MOTORS

#define CIM_MOTOR

#define VACUUM
#define VACUUM_ARM
#define BOWLING_BALL_ARM

#if defined(VACUUM)
  #define VACUUM_PIN       7
  #define VACUUM_BUTTON    UP
  #define VACUUM_SPEED     2000
#endif

#if defined(VACUUM_ARM)
  #define VACUUM_ARM_PIN            5
  #define VACUUM_ARM_DOWN_BUTTON    CROSS
  #define VACUUM_ARM_UP_BUTTON      TRIANGLE
  #define VACUUM_ARM_SPEED          60
#endif

#if defined(BOWLING_BALL_ARM)
  #define BOWLING_BALL_ARM_PIN            6
  #define BOWLING_BALL_ARM_DOWN_BUTTON    CIRCLE
  #define BOWLING_BALL_ARM_UP_BUTTON      SQUARE
  #define BOWLING_BALL_ARM_SPEED          60
#endif
