#define ERNIE
//#define MARVIN
//#define PARKER

#if defined(ERNIE) || defined(MARVIN) || defined(PARKER)
  #define MRDC_ROBOT
#endif

#if defined(ERNIE)
  #include "Ernie.hpp"
#endif

#if defined(MARVIN)
  #include "Marvin.hpp"
#endif

#if defined(PARKER)
  #include "Parker.hpp"
#endif

//#define QUARTERBACK
//#define LINEMAN
//#define RECIEVER
//#define RUNNINGBACK
//#define CENTER
//#define NONQB_OMNI
//#define KICKER

//#define CIM_MOTOR
//#define _775_MOTOR
//#define BANEBOTS_MOTOR

//#define BAG_MOTOR

//#define HOMECOMMING_GAME
//#define STUDENTS
//#define ALUMNI

#define PERF_BOARD_SHIELD
//#define PCB_SHIELD

//#define BASIC_DRIVETRAIN    //uncomment for 2 drive wheels
//#define DUAL_MOTORS
//#define LR_TACKLE_PERIPHERALS         //uncomment for special handicap for the tackles
//#define OMNIWHEEL_DRIVETRAIN  //uncomment for omniwheel robots
//#define NEW_OMNIWHEEL_DRIVETRAIN

//#define CENTER_PERIPHERALS  //uncomment for special features of center 
//#define QB_PERIPHERALS      //uncomment for special QB features
//#define IR_MAST
//#define QB_TRACKING
//#define KICKER_PERIPHERALS  //uncomment for special Kicker features
//#define RECEIVER_PERIPHERALS  
//#define LED_STRIP       //uncomment for LED functionality
//#define TACKLE          //uncomment for tackle sensor functionality
//#define ROTATION_LOCK

#if defined(QUARTERBACK)
  #undef  OMNIWHEEL_DRIVETRAIN
  #define OMNIWHEEL_DRIVETRAIN
  #undef  QB_PERIPHERALS
  #define QB_PERIPHERALS
  #undef  LED_STRIP 
  #define LED_STRIP  
  #undef  TACKLE
  #define TACKLE
#endif


#if defined(LINEMAN)
  #undef  BASIC_DRIVETRAIN
  #define BASIC_DRIVETRAIN
  #undef  LED_STRIP 
  #define LED_STRIP 
#endif


#if defined(ERNIE)
  #undef  BASIC_DRIVETRAIN
  #define BASIC_DRIVETRAIN
  #undef  DUAL_MOTORS 
  #define DUAL_MOTORS 
#endif

#if defined(RECIEVER)
  #undef  BASIC_DRIVETRAIN
  #define BASIC_DRIVETRAIN
  #undef  LED_STRIP 
  #define LED_STRIP 
  #undef  TACKLE
  #define TACKLE
  #undef  NO_PERIPHERALS_DEFINED
  #define NO_PERIPHERALS_DEFINED
#endif

#if defined(CENTER)
  #undef  BASIC_DRIVETRAIN
  #define BASIC_DRIVETRAIN
  #undef  LED_STRIP 
  #define LED_STRIP 
  #undef  CENTER_PERIPHERALS
  #define CENTER_PERIPHERALS
#endif

#if defined(RUNNINGBACK)
  #undef  BASIC_DRIVETRAIN
  #define BASIC_DRIVETRAIN
  #undef  LED_STRIP 
  #define LED_STRIP 
  #undef  TACKLE
  #define TACKLE
#endif

#if defined(NONQB_OMNI)
  #undef  OMNIWHEEL_DRIVETRAIN
  #define OMNIWHEEL_DRIVETRAIN
  #undef  LED_STRIP 
  #define LED_STRIP 
  #undef  TACKLE
  #define TACKLE
#endif

#if defined(KICKER)
  #undef  BASIC_DRIVETRAIN
  #define BASIC_DRIVETRAIN
  #undef  KICKER_PERIPHERALS 
  #define KICKER_PERIPHERALS 
#endif


//#define TEST_DRIVETRAIN

#if !defined(MAX_TOTAL_PERIPERALS)
	#define MAX_TOTAL_PERIPERALS 10
#endif
/*
#if !defined(CENTER_PERIPHERALS) && !defined(QB_PERIPHERALS) && !defined(IR_MAST)  && !defined(QB_TRACKING) && !defined(KICKER_PERIPHERALS) && !defined(RECEIVER_PERIPHERALS) && !defined(LED_STRIP) && !defined(TACKLE) && !defined(ROTATION_LOCK)
	#define NO_PERIPHERALS_DEFINED
#endif
*/
#include "ErrorHandeling.hpp"
