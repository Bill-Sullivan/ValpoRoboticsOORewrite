#define BASIC_DRIVETRAIN    //uncomment for 2 drive wheels
//#define DUAL_MOTORS
//#define LR_TACKLE_PERIPHERALS         //uncomment for special handicap for the tackles
//#define OMNIWHEEL_DRIVETRAIN  //uncomment for omniwheel robots


//#define CENTER_PERIPHERALS  //uncomment for special features of center 
//#define QB_PERIPHERALS      //uncomment for special QB features
//#define IR_MAST
//#define QB_TRACKING
//#define KICKER_PERIPHERALS  //uncomment for special Kicker features
//#define RECEIVER_PERIPHERALS  
//#define LED_STRIP       //uncomment for LED functionality
//#define TACKLE          //uncomment for tackle sensor functionality
//#define ROTATION_LOCK

//#define CIM_MOTOR
//#define _775_MOTOR
//#define BANEBOTS_MOTOR

#define BAG_MOTOR

//#define TEST_DRIVETRAIN

#if !defined(MAX_TOTAL_PERIPERALS)
	#define MAX_TOTAL_PERIPERALS 10
#endif

#if !defined(CENTER_PERIPHERALS) && !defined(QB_PERIPHERALS) && !defined(IR_MAST)  && !defined(QB_TRACKING) && !defined(KICKER_PERIPHERALS) && !defined(RECEIVER_PERIPHERALS) && !defined(LED_STRIP) && !defined(TACKLE) && !defined(ROTATION_LOCK)
	#define NO_PERIPHERALS_DEFINED
#endif
