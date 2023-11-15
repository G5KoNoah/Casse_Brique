#include <iostream>

#include "Ball.h"
Ball::Ball(float posX, float posY, int rad, sf::Color color, string filename) :GameObject(posX, posY, rad, color, filename) {

}

void Ball::EnterCollision(string side){
	Bounce(side);
}



//put in Ball.cpp
void Ball::Bounce(string side) {
	if ((side == "bottom" && vDirection.y > 0) || (side == "up" && vDirection.y < 0)) {
		vDirection.y = -vDirection.y;
	}
	else if ((side == "left" && vDirection.x < 0) || (side == "right" && vDirection.x > 0)) {
		vDirection.x = -vDirection.x;
	}
}