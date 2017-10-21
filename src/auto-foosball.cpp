#include <iostream>
#include "Motor.h"
#include "Player.h"

using namespace std;

int main() {
	//create objects
	Motor m = Motor(0, 1, 2, 3);
    Player p = Player(0, 200, 0, 1, 2, 3);
    
    // Move player to 500mm location
    p.moveTo(-1);
    
    //main program loop
	while(1) {
        
//        m.forward(10, 100);
//        m.backward(10, 100);
	}
	return 0;
}
