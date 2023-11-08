#include "GameObject.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#define PI 3.14159265;

GameObject::GameObject(float posX, float posY, int sA, int sB, sf::Color color, float oriX, float oriY) {
	size = sA;
	sizeHeight = sB;

	oShape = new sf::RectangleShape(sf::Vector2f(size, sizeHeight));
	oShape->setOrigin(oriX * size, oriY * sizeHeight);
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

	positionX += normDirX * fDeltatime * speed;
	positionY += normDirY * fDeltatime * speed;
	oShape->setPosition(positionX, positionY);
}

void GameObject::ObjectRotate(sf::Vector2i point) {
	float deg = atan2(point.x - positionX,-( point.y - positionY)) * 180 / PI;
	oShape->setRotation(deg);
}

bool GameObject::Collision(GameObject touchedObject) {
	bool already = false;
	if (objectCollision.size() != 0) {
		for (int i = 0; objectCollision.size(); i++) {
			if (objectCollision[i] == touchedObject.oShape) {
				already = true;
			}
		}
	}

	if (oShape->getGlobalBounds().intersects(touchedObject.oShape->getGlobalBounds())) {

		if (!already) {
			Bounce(touchedObject);
			objectCollision.push_back(touchedObject.oShape);
		}

		return true;



	}
	if (already) {
		sf::Shape* valueToRemove = touchedObject.oShape;

		objectCollision.erase(std::remove(objectCollision.begin(), objectCollision.end(), valueToRemove), objectCollision.end());
	}


	return false;
}

//put in Ball.cpp
void GameObject::Bounce(GameObject touchedObject) {
	if (touchedObject.positionY > positionY + sizeHeight || touchedObject.positionY + touchedObject.sizeHeight < positionY) {
		// Collision depuis le haut
		std::cout << "Collision, verticale" << std::endl;
		setDirectionY = -setDirectionY;
	}
	else if (touchedObject.positionX > positionX || touchedObject.positionX < positionX) {
		// Collision depuis la gauche
		std::cout << "Collision, horizontale" << std::endl;
		setDirectionX = -setDirectionX;
	}


}


//Start()
// 
//Stay()
//Exit()