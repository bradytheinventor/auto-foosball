//Motor.h
#ifndef MOTOR_H_
#define MOTOR_H_

class Motor {
private:
	//store the GPIO pin states needed to execute a particular movement
	int stepCount;
	int stepCounter;

    int seq[8][4] = {
        {1,0,0,1},
        {1,0,0,0},
        {1,1,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,1,1},
        {0,0,0,1}
    };
	int pins[4];

public:
	Motor(int A1, int A2, int B1, int B2);
	void step(int direction);
	void forward(int interval, int steps);
	void backward(int interval, int steps);
};

#endif
