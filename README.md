Robotic-Football-All-In-Many
=====
Use Instructions:

This is the multi-file code for the robotic football team. The design philosophy behind this project is to divide the code amoung a number of classes to make it easy to maintain and share code between robots. The abilities of the robot to be programmed are then chosen from a list of define statements in config.hpp, like so:

In config.hpp:
````c++
#define QUARTERBACK
//#define LINEMAN
//#define RECIEVER
//#define RUNNINGBACK
//#define CENTER
//#define NONQB_OMNI
//#define KICKER

//#define BASIC_DRIVETRAIN
//#define OMNIWHEEL_DRIVETRAIN
//#define CENTER_PERIPHERALS
//#define QB_PERIPHERALS
//#define KICKER_PERIPHERALS
//#define RECEIVER_PERIPHERALS
//#define LED_STRIP
//#define TACKLE

//#define CIM_MOTOR
//#define _775_MOTOR
//#define BANEBOTS_MOTOR

#define BAG_MOTOR
````
This example would create a robot that uses a bag motor omniwheel drivetrain (specifically our quarterback), with the led strip, quarterback arm, tackle sensor enabled. 
In ErrorHandeling.hpp there are a list of error cases that the compiler goes through to make sure no incompatable options are chosen.

Aternatively you can manually pick what options you want to enable. This can be useful when developing a new robot or diagnosing problems with individual parts on an existing robot. 

In config.hpp:
````c++
//#define QUARTERBACK
//#define LINEMAN
//#define RECIEVER
//#define RUNNINGBACK
//#define CENTER
//#define NONQB_OMNI
//#define KICKER

#define PERF_BOARD_SHIELD
//#define PCB_SHIELD

//#define BASIC_DRIVETRAIN    //uncomment for 2 drive wheels
//#define DUAL_MOTORS
//#define LR_TACKLE_PERIPHERALS         //uncomment for special handicap for the tackles
//#define OMNIWHEEL_DRIVETRAIN  //uncomment for omniwheel robots
#define NEW_OMNIWHEEL_DRIVETRAIN

//#define CENTER_PERIPHERALS  //uncomment for special features of center 
#define QB_PERIPHERALS      //uncomment for special QB features
//#define IR_MAST
//#define QB_TRACKING
//#define KICKER_PERIPHERALS  //uncomment for special Kicker features
//#define RECEIVER_PERIPHERALS  
#define LED_STRIP       //uncomment for LED functionality
#define TACKLE          //uncomment for tackle sensor functionality
//#define ROTATION_LOCK

//#define CIM_MOTOR
//#define _775_MOTOR
//#define BANEBOTS_MOTOR

#define BAG_MOTOR
````

This example does the same thing as the above example.

#### Useful Libraries
---
1. (PS3 Integration) [USB HostShield 2.0](https://github.com/felis/USB_Host_Shield_2.0)
2. (Omniwheel Rotation Locking) [Adafruit BNO055](https://github.com/adafruit/Adafruit_BNO055)

#### Controls
---
  - **Basic Drivetrain**
    - _Up/Down Left Joystick_ - Forward and Backward movement
    - _Left/Right Right Joystick_ - Turning
    - _R2_ - activates "boost" 
    - _Start_ - Puts robot in "kids mode". The speed is reduced, boost is disabled, and the leds will change
    - _Select _- Calibration mode - disables drivetrain while changes are made
      - _Up/Down D-Pad_ - compensates for drag left or right
      - _Select_ - exit Calibration Mode to regular drive mode
  - **Center**
    - Center currently uses basic drivetrain
    - _TRIANGLE_ - raise the center release servo
    - _CROSS_ - lower the center release servo
  - **Omniwheel Drivetrain**
    - _Up/Down/Left/Right Left Joystick_ - Lateral movement in any direction
    - _Up/Down/Left/Right D-Pad_- Lateral Movement along compass directions at full power
    - _Left/Right Right Joystick_ - Turning - as of version 1.0.3 this will disable rotation correction
    - _R3_ (Right Joystick Press) - Re-engage rotation correction
    - _R2_ - slow down speed
    - _L1_ - reverse directions (make back of robot front and vise versa)
    - Throwing
      - _SQUARE_ - Handoff throw
      - _CROSS_ - Reciever handoff throw/weak toss
      - _CIRCLE_ - mid range throw
      - _TRIANGLE_ - max power throw
      - _R1_ - return thrower to down position
      - _L2_ - hold to enable throw offset 
        - _Up/Down D-Pad_ - adjust power of all throws but triangle
  - **Kicker**
    - Kicker - currently uses basic drivetrain
    - _CROSS_ - kick
    - _TRIANGLE_ - reload
	
	Controls for the current MRDC Robots:
	[Ernie's Controls](ErnieControls.md)
	
	MarvinControls.md
	
	ParkerControls.md	
	
__________________________________________________________________

To create a new peripheral 

First copy the example peripheral folder to where you want to place your peripheral usually somewhere in MRDCPeripherals or RoboticFootballPeripherals


Second implement the fallowing methods 
each peripheral's instance of each method will run sequentally with the robot's other peripherals if any
            
The Setup               method should contain code to run once when the microcontroller turns on

The doThing             method should contain code to run continuously when the controller is connected

The doNotConnectedThing method should contain code to run continuously when the controller is disconnected and should stop any motors or other devices that could hurt a human opperator

Third rename your class in its decleration and in the /class in the comment box up top.

Third include your peripherals .hpp file in either RoboticFootballLibraries.hpp or the appropreate MRDC robot RobotNameLibraries.hpp file i.e: ErnieLibraries.hpp

Fourth in Robot.hpp add your Peripheral to peripheralVec

To do this look for a series of statements in the setup method that look roughtly like this:

In config.hpp:
````c++
#if defined(YOUR_PERIPHERAL) 
  peripheralVec.push_back(new YourPeripheral);
#endif
````

and replace YOUR_PERIPHERAL with your peripherals name in a similar format 

and replace YourPeripheral  with your peripherals name in a similar format 

The code you wrote in the your peripheral should now run