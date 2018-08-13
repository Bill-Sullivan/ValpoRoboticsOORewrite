#pragma once

#include <Arduino.h>
#include <stdint.h>

#if !defined(PS3_VARS)
	//Include libraries
	#include <PS3BT.h>
	#include <usbhub.h>
	USB Usb;
	USBHub Hub1(&Usb);
	BTD Btd(&Usb);
	PS3BT PS3(&Btd);
	
	#define PS3_VARS
#endif