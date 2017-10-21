//Motor.cpp
#include <wiringPi.h>
#include "Motor.h"

//load motor GPIO pins on object creation
Motor::Motor(int A1, int A2, int B1, int B2) {
	//set up wiringPi GPIO interface
	wiringPiSetup();

	//load GPIO pins
	pins[0] = A1;
	pins[1] = A2;
	pins[2] = B1;
	pins[3] = B2;

	//set GPIO pins to output mode
	pinMode(pins[0], OUTPUT);
	pinMode(pins[1], OUTPUT);
	pinMode(pins[2], OUTPUT);
	pinMode(pins[3], OUTPUT);
    
    //set step count and step counter
    stepCount = 8;
    stepCounter = 0;

}

//update motor GPIO pins to execute motor step
void Motor::step(int direction) {
	//write GPIO values to pins
	for(int p = 0; p < 4; p++) {
		digitalWrite(pins[p], seq[stepCounter][p]);
	}

	//update counter to track GPIO values
	stepCounter += direction;

	//apply bounds to counter
	if(stepCounter > stepCount) {
		stepCounter = 0;
	} else if(stepCounter < 0) {
		stepCounter = stepCount + direction;
	}
}

//step motor CW by a given number of steps (looking at shaft)
void Motor::forward(int interval, int steps) {
	for(int i = 0; i < steps; i++) {
		step(1);
		delay(interval);
	}
}

//step motor CCW by a given number of steps (looking at shaft)
void Motor::backward(int interval, int steps) {
	for(int i = 0; i < steps; i++) {
		step(-1);
		delay(interval);
	}
}
