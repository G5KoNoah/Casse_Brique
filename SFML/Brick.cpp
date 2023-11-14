#include "Brick.h"
#include <iostream>
Brick::Brick(float posX, float posY, int sA, int sB, sf::Color color, float oriX, float oriY, int hits) :GameObject(posX, posY, sA, sB, color, oriX, oriY) {
	hp = hits;
}

void Brick::EnterCollision() {
	hp -= 1;
	std::cout << "brick" << endl;
	ColorSetOnHP();
}

void Brick::ColorSetOnHP() {
	if (hp == 1)
		oColor = sf::Color::Red;
	else if (hp == 2)
		oColor = sf::Color::Yellow;
	else if (hp == 3)
		oColor = sf::Color::Blue;
	else
		oColor = sf::Color::Magenta;
	oShape->setFillColor(oColor);

}

Brick::~Brick() {

}