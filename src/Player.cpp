#include <iostream>
#include <math.h>
#include "Player.h"
#include "Motor.h"

using namespace std;

    Player::Player(double minY, double maxY, int A1, int A2, int B1, int B2) {
        // Creating motor objects
        rotateMotor = Motor(A1, A2, B1, B2); // Creating & initializing rotateMotor object
        lateralMotor = Motor(A1, A2, B1, B2); // Creating & initializing lateralMotor object

        pos.at(0) = 0; // X = 0
        pos.at(1) = 0; // Y = 0
        
        posRange[0] = minY; // Minimum x range set to minX
        posRange[1] = maxY; // Maximum x range set to maxX
        
        rotationRad = 0; // Rotation in radians = 0

        rotationRange[0] = -M_PI / 2; // Minimum rotation of player set to -90 (-pi/2)
        rotationRange[1] = M_PI / 2; // Maximum rotation of player set to 90 (pi/2)
        
        movementInterval = 4; // milisecond delay between pulses. Constant value.
    }
    
    void Player::rotateTo(double radians) {
        double degrees = radians * 180 / M_PI; // Conversion from radians to degrees
        int steps = degrees / rotateMotor.degreePerStep; // Conversion from degrees to stops using a motor's degrees per step
        if (steps < 0) {
            rotateMotor.backward(movementInterval, steps);
        } else {
            rotateMotor.forward(movementInterval, fabs(steps));
        }
    }
    
    void Player::moveTo(double mili) {
        if (rangeCheck(mili) == false) {
            cout << "Player cannot move to " << mili << " because the range of this player is " << posRange[0] << " - " << posRange[1] << endl;
            return;
        }
        double pulleyCircumference = 10.68; // Circumference of the pulleys. Measured in milimeters.
        double pulleyRadius =  1.7; // Radius of the pulleys. Measured in milimeters.
        
        double rad = mili / pulleyRadius; // Conversion from milimeters to radians
        double degrees = rad * 180 / M_PI; // Conversion from radians to degrees
        int steps = degrees / rotateMotor.degreePerStep; // Conversion from degrees to steps using a motor's degrees per step
        cout << "Steps necessary: " << steps << endl;
        if (steps < 0) {
            lateralMotor.backward(movementInterval, steps);
        } else {
            lateralMotor.forward(movementInterval, fabs(steps));
        }
    }
    
    double Player::timeToMove(double targetY) {
        if (rangeCheck(targetY) == false) {
            return -1;
        }
        
        double pulleyRadius = 1.7;
        double deltaY = fabs(pos[1] - targetY); // Calculating the change in y needed
        double degrees = deltaY / pulleyRadius; // Calculating the degrees of rotation needed
        double steps = degrees / lateralMotor.degreePerStep; // Determine steps needed
        double stepPerSecond = 1000 / movementInterval; // Determining steps per second, based off of movementInterval
        double totalSeconds = steps * stepPerSecond; // The number of seconds needed to move from point a to point b.
        return totalSeconds;
        
    }
    
    double Player::timeToRotate(double targetTheta) {
        double deltaRad = fabs(rotationRad - targetTheta); // Calculating the change in radians needed
        double degrees = deltaRad * M_PI / 180; // Converting from radians to degrees
        double steps = degrees / rotateMotor.degreePerStep; // Determine steps needed
        double stepPerSecond = 1000 / movementInterval; // Determining steps per second, based off of movementInterval
        double totalSeconds = steps * stepPerSecond; // The number of seconds needed to move from poitn a to point b
        return totalSeconds;
    }

    bool Player::rangeCheck(double posY) {
        if (posY < posRange[0] || posY > posRange[1]) { // If the location to be moved to is outside of the player's range
            return false; // Player cannot be moved to location
        } else {
            return true; // Player can be moved to location
        }
    }

