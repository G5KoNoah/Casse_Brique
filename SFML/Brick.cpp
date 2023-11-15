#include "Brick.h"
#include <iostream>
Brick::Brick(float posX, float posY, int sA, int sB, sf::Color color, string filename, float oriX, float oriY, int hits) :GameObject(posX, posY, sA, sB, color, filename, oriX, oriY) {
	hp = hits;

}

void Brick::EnterCollision(string side) {
	hp -= 1;
	std::cout << "brick" << endl;
	ColorSetOnHP();
}

void Brick::ColorSetOnHP() {
	switch (hp) {
		case 1:
			oColor = sf::Color::Red;
			break;
		case 2:
			oColor = sf::Color::Yellow;
			break;
		case 3:
			oColor = sf::Color::Blue;
			break;
		default:
			oColor = sf::Color::Magenta;
			break;
	}

	oShape->setFillColor(oColor);
}

Brick::~Brick() {

}