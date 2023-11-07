#include "GameObject.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#define PI 3.14159265;

GameObject::GameObject(float posX, float posY, int sA, int sB, sf::Color color) {
	size = sA;
	sizeHeight = sB;
	oShape = new sf::RectangleShape(sf::Vector2f(size, sizeHeight));
	Initialize(posX, posY, color);
}

GameObject::GameObject(float posX, float posY, int rad, sf::Color color) {
	size = rad;
	sizeHeight = NULL;
	oShape = new sf::CircleShape(rad);
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

void GameObject::ObjectMove(float fDeltatime, sf::Vector2i direction, int scrnW, int scrnH ) {
	float norm = sqrt((direction.x) ^ 2 + (direction.y) ^ 2);
	float normDirX = (direction.x -	scrnW / 2 ) / norm;
	float normDirY = (direction.y - scrnH ) / norm;
	positionX += normDirX * fDeltatime * 10.f;
	positionY += normDirY * fDeltatime * 10.f;
	oShape->setPosition(positionX, positionY);
}

void GameObject::ObjectRotate(sf::Vector2i positionMouse, float fOriginX, float fOriginY) {

	oShape->setOrigin(fOriginX * size, fOriginY * sizeHeight);
	float deg = atan2(positionMouse.x - positionX,-( positionMouse.y - positionY)) * 180 / PI;
	oShape->setRotation(deg);
} //(fOriginX * size) - (fOriginY * sizeHeight)
