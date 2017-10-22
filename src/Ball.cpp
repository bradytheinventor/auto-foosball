//
//  Ball.cpp
//  
//
//  Created by Douglas Zuercher on 10/21/17.
//

#include "Ball.h"

using namespace std;

Ball::Ball(double posX, double posY) {
    setXPos(posX); // Sets the ball's x position
    setYPos(posY); // Sets the ball's y position
}

double Ball::getXPos() {
    return position[0]; // Returns the x position of the ball
}

double Ball::getYPos() {
    return position[1]; // Returns the y position of the ball
}

double Ball::getXVel() {
    return velocity[0]; // Returns the x velocity of the ball
}

double Ball::getYVel() {
    return velocity[1]; // Returns the y velocity of the ball
}

void Ball::setXPos(double posX) {
    position.at(0) = posX; // Sets the x position of the ball to the input position
}

void Ball::setYPos(double posY) {
    position.at(1) = posY; // Sets the y position of the ball to the input position
}

void Ball::setXVel(double velX) {
    velocity.at(0) = velX; // Sets the x velocity of the ball to the input velocity
}

void Ball::setYVel(double velY) {
    velocity.at(1) = velY; // Sets the y velocity of the ball to the inptu velocity
}

void Ball::setRadius(double rad) {
    radius = rad; // Sets the ball's velocity
}
