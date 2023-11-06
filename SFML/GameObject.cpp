#include "GameObject.h"
#include <SFML/Graphics.hpp>
GameObject::GameObject(int posX, int posY, int sA, int sB, sf::Color color) {
	positionX = posX;
	positionY = posY;
	size = sA;
	sizeHeight = sB;
	oColor = color;
	oShape = new sf::RectangleShape(sf::Vector2f(size, sizeHeight));
	oShape->setPosition(posX, posY);
	oShape->setFillColor(oColor);
}


GameObject::GameObject(int posX, int posY, int rad, sf::Color color) {
	positionX = posX;
	positionY = posY;
	size = rad;
	sizeHeight = NULL;
	oColor = color;

	oShape = new sf::CircleShape(rad);
	oShape->setPosition(posX, posY);
	oShape->setFillColor(oColor);
}
