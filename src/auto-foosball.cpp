#include <iostream>
#include "Motor.h"
using namespace std;

int main() {
	//create objects
	Motor m = Motor(0, 1, 2, 3);

	//main program loop
	while(1) {
		m.forward(10, 100);
		m.backward(10, 100);
	}

	return 0;
}
