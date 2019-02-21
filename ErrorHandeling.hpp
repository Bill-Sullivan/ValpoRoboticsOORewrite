//Error handling for what parts of the code are enabled
#ifdef BASIC_DRIVETRAIN
#ifdef OMNIWHEEL_DRIVETRAIN
#error Two drivetrains are enabled!
#endif
#ifdef ROTATION_LOCK
#error Rotation lock is not normally used with a basic drivetrain...
#endif
#ifdef QB_PERIPHERALS
#error Quarterback peripherals enabled with basic drivetrain. Quarterback requires an omniwheel drive
#ifdef CENTER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#ifdef RECEIVER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#ifdef KICKER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#endif
 
#ifdef RECEIVER_PERIPHERALS
#warning You are making a receiver with a basic drivetrain. Make sure this is right.
#ifdef CENTER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#ifdef QB_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#ifdef KICKER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#endif
#endif
 
#ifdef OMNIWHEEL_DRIVETRAIN
#ifdef DUAL_MOTORS
#error dual motors with an omniwheel? perposterous!
#endif
#ifdef CENTER_PERIPHERALS
#error The center does not have an omniwheel drive, last I checked...
#ifdef QB_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#ifdef RECEIVER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#ifdef KICKER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#endif
#ifdef KICKER_PERIPHERALS
#error Kicker does not use an omniwheel drive!
#ifdef CENTER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#ifdef RECEIVER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#ifdef QB_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#endif
#ifdef RECEIVER_PERIPHERALS
#warning You are making a receiver with an omniwheel drivetrain. Make sure this is right.
#ifdef CENTER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#ifdef QB_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#ifdef KICKER_PERIPHERALS
#error Multiple peripherals enabled!
#endif
#endif
#endif

#ifdef QB_TRACKING
#ifndef QB_PERIPHERALS
#error You enabled QB tracking, but no QB peripherals!
#endif
#endif

#ifndef BASIC_DRIVETRAIN
#ifndef OMNIWHEEL_DRIVETRAIN
#ifndef NEW_OMNIWHEEL_DRIVETRAIN
#ifndef AUTONOMOUS_DRIVE
#warning "You don't have a drivetrain enabled! Don't expect this robot to drive!"
#endif
#endif
#endif
#endif


#if !defined(PERF_BOARD_SHIELD) && !defined(PCB_SHIELD)
  #error "Specify a shield type"
#endif  
