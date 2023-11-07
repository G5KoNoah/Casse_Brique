#include "GameObject.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#define PI 3.14159265;

GameObject::GameObject(float posX, float posY, int sA, int sB, sf::Color color) {
	size = sA;
	sizeHeight = sB;
	oShape = new sf::RectangleShape(sf::Vector2f(size, sizeHeight));
	oShape->setOrigin(0.5 * size, 1 * sizeHeight);
	Initialize(posX, posY, color);
}

GameObject::GameObject(float posX, float posY , int rad, sf::Color color) {
	size = rad;
	sizeHeight = NULL;
	oShape = new sf::CircleShape(rad);
	oShape->setOrigin(size, size);
	Initialize(posX, posY, color);
}

void GameObject::Initialize(float posX, float posY, sf::Color color)
{	
	positionX = posX;
	positionY = posY;
	oColor = color;
	oShape->setPosition(positionX, positionY);
	oShape->setFillColor(oColor);
}

void GameObject::ObjectMove(float fDeltatime, sf::Vector2i direction ) {



	float norm = sqrt( setDirectionX *setDirectionX + setDirectionY*setDirectionY);
	float normDirX = (setDirectionX) / norm;
	float normDirY = (setDirectionY) / norm;

	positionX += normDirX * fDeltatime * 500.f;
	positionY += normDirY * fDeltatime * 500.f;
	oShape->setPosition(positionX, positionY);
}

void GameObject::ObjectRotate(sf::Vector2i point) {
	float deg = atan2(point.x - positionX,-( point.y - positionY)) * 180 / PI;
	oShape->setRotation(deg);
}
