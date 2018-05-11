Robotic-Football-All-In-One
=====

This is the multi-file code for the robotic football team. The design philosophy behind this project is to divide the code amoung a number of classes file to make it easy to maintain and share code between robots. The abilities of the robot to be programmed are then chosen from a list of define statements in config.hpp, like so:

In config.hpp:
````c++
//#define BASIC_DRIVETRAIN
#define OMNIWHEEL_DRIVETRAIN
//#define CENTER_PERIPHERALS
#define QB_PERIPHERALS
//#define KICKER_PERIPHERALS
//#define RECEIVER_PERIPHERALS
#define LED_STRIP
#define TACKLE
````
This example would create a robot that uses an omniwheel drivetrain (specifically our quarterback), with the led strip and tackle sensor enabled. At the end of the file are a list of error cases that the compile goes through to make sure no incompatable options are shown.

#### Useful Libraries
---
1. (PS3 Integration) [USB HostShield 2.0](https://github.com/felis/USB_Host_Shield_2.0)
2. (Omniwheel Rotation Locking) [Adafruit BNO055](https://github.com/adafruit/Adafruit_BNO055)
3. (STL for arduino) [StandardCplusplus](https://github.com/maniacbug/StandardCplusplus)

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