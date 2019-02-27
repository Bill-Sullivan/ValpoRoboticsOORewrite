/*
  __  __      _       ____   __     __            _   _     
U|' \/ '|uU  /"\  uU |  _"\ u\ \   /"/u  ___     | \ |"|    
\| |\/| |/ \/ _ \/  \| |_) |/ \ \ / //  |_"_|   <|  \| |>   
 | |  | |  / ___ \   |  _ <   /\ V /_,-. | |    U| |\  |u   
 |_|  |_| /_/   \_\  |_| \_\ U  \_/-(_/U/| |\u   |_| \_|    
<<,-,,-.   \\    >>  //   \\_  //   .-,_|___|_,-.||   \\,-. 
 (./  \.) (__)  (__)(__)  (__)(__)   \_)-' '-(_/ (_")  (_/  
                           nnnmmm
            \||\       ;;;;%%%@@@@@@       \ //,
             V|/     %;;%%%%%@@@@@@@@@@  ===Y//
             68=== ;;;;%%%%%%@@@@@@@@@@@@    @Y
             ;Y   ;;%;%%%%%%@@@@@@@@@@@@@@    Y
             ;Y  ;;;+;%%%%%%@@@@@@@@@@@@@@@    Y
             ;Y__;;;+;%%%%%%@@@@@@@@@@@@@@i;;__Y
            iiY"";;   "uu%@@@@@@@@@@uu"   @"";;;>
                   Y     "UUUUUUUUU"     @@
                   `;       ___ _       @
                     `;.  ,====\\=.  .;'
                       ``""""`==\\=='
                              `;=====
                                ===  

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

#define VACUUM
#define VACUUM_ARM
#define BOWLING_BALL_ARM

#define BRIDGE_MODE_ENABLED

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
