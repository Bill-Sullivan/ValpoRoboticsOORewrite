// mode definitions
#undef DRIVING
#define DRIVING         1

#undef CALIBRATION
#define CALIBRATION     2

#undef KID
#define KID             3

#undef MAX_DRIVE
#define MAX_DRIVE             84    // limited because of issues with calibrating victors to full 0-180 range

#if defined(OMNIWHEEL_DRIVETRAIN)|| defined(NEW_OMNIWHEEL_DRIVETRAIN)
	#undef DEFAULT_HANDICAP
	#define DEFAULT_HANDICAP      1   // when not using boost, drive full speed
	#undef ALTERNATE_HANDICAP
	#define ALTERNATE_HANDICAP    3   // when using boost, divide speed by 3
	#undef KID_HANDICAP
	#define KID_HANDICAP          7     // when in kids mode, speed is divided by 7

	#define MAX_TURN              14	
#else
	#undef DEFAULT_HANDICAP
	#define DEFAULT_HANDICAP      3   // when using boost, divide speed by 3
	#undef ALTERNATE_HANDICAP
	#define ALTERNATE_HANDICAP    1   // when not using boost, drive full speed
	#undef KID_HANDICAP
	#define KID_HANDICAP          5     // when in kids mode, speed is divided by 5

	#define MAX_TURN              14  
#endif