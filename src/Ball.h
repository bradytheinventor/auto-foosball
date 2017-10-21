//
//  Ball.hpp
//  
//
//  Created by Douglas Zuercher on 10/21/17.
//

#ifndef Ball_h
#define Ball_h

#include <stdio.h>
#include <vector>

class Ball {
private:
    double radius; // Radius length of the ball
    
    std::vector<double> position = std::vector<double>(2); // (X, Y) for ball position
    std::vector <double> velocity = std::vector<double>(2); // (velocityX, velocityY)
public:
    Ball(); // Empty ball constructor
    Ball(double xPos, double yPos);
    double getXPos(); // Returns the x position of the ball
    double getYPos(); // Returns the y position of the ball
    double getXVel(); // Returns the x velocity of the ball
    double getYVel(); // Returns the y velocity of the ball
    
    void setXPos(double posX); // Set the x position of the ball - should only be used by the camera
    void setYPos(double posY); // Set the y position of the bal; - should only be used by the camera
    void setXVel(double velX); // Set the x velocity of the ball - should only be used by the camera
    void setYVel(double velY); // Set the y velocity of the ball - should only be used by the camera
    
};
#endif /* Ball_h */
