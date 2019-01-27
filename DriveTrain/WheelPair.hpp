#include <Servo.h>

class Motor {
	private:
	Servo motor1;
	#if defined(DUAL_MOTORS)
	Servo motor2;
	#endif
	
	public:
	int attach(int pin) {
		attach(pin, 1000, 2000);
	}
	
	int attach(int pin, int lowWidth, int highWidth) {
		motor1.attach(pin, lowWidth, highWidth);
		#if defined(DUAL_MOTORS)
		motor2.attach(pin, lowWidth, highWidth);
		#endif
	}
	int write(int angle) {
		motor1.write(angle);
		#if defined(DUAL_MOTORS)
		motor2.write(angle);		
		#endif
	} 
	
	int writeMicroseconds(int angle) {
		motor1.writeMicroseconds(angle);
		#if defined(DUAL_MOTORS)
		motor2.writeMicroseconds(angle);
		#endif
	}	
};