#ifndef Player_h
#define Player_h
#include <stdio.h>
#include "Motor.h"
#include <vector>

class Player {
private:
    Motor rotateMotor; // 5V motor used for rotational movement
    Motor lateralMotor; // 12V motor used for lateral movement
    
    std::vector <double> posRange = std::vector<double>(2); // (minY, maxY) range of player
    std::vector <double> pos = std::vector<double>(2); // (X,Y) location of player
    std::vector <double> rotationRange = std::vector<double>(2); // Range of locations possible
    
    double rotationRad; // Rotation in radians of player
    double lateralSpeed; // Lateral speed
    double rotationSpeed; // Rotational speed
    double movementInterval; // Constant value provided to motor objects when moving motor
    
    bool rangeCheck(double posY);
    
public:
    Player(double minY, double maxY, int A1, int A2, int B1, int B2);
    void rotateTo(double radians);
    void moveTo(double mili);
    double timeToMove(double targetY);
    double timeToRotate(double targetTheta);
};

#endif /* Player_hpp */
