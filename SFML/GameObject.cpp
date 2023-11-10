#include "GameObject.h"
#include "MathGeneric.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>




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

void GameObject::ObjectMove(float fDeltatime ) {


	sf::Vector2f vDirection = sf::Vector2f(setDirectionX, setDirectionY);
	vDirection = Math::Normalize(vDirection);
	positionX += vDirection.x * fDeltatime * speed;
	positionY += vDirection.y * fDeltatime * speed;
	
	oShape->setPosition(positionX, positionY);
}

void GameObject::ObjectRotate(sf::Vector2i point) {
	float deg = Math::arcTan(point, positionX, positionY);
	oShape->setRotation(deg);
}

bool GameObject::Collision(GameObject* touchedObject) {
	bool already = false;
	if (objectCollision.size() != 0) {
		for (int i = 0; i < objectCollision.size(); i++) {
			if (objectCollision[i] == touchedObject) {
				already = true;
			}
		}
	}

	if (oShape->getGlobalBounds().intersects(touchedObject->oShape->getGlobalBounds())) {
		side = SideCollision(touchedObject);
		if (!already) {
			objectCollision.push_back(touchedObject);
			EnterCollision();
			return true;
		}else{
			StayCollision();
		}


	}else{
		if (already) {
			ExitCollision();
			GameObject* valueToRemove = touchedObject;
			objectCollision.erase(std::remove(objectCollision.begin(), objectCollision.end(), valueToRemove), objectCollision.end());
		}
	}



	return false;
}
void GameObject::EnterCollision(){
	std::cout << "Start Collision"<<endl;
}

void GameObject::StayCollision() {
	std::cout << "Stay Collision"<<endl;
}

void GameObject::ExitCollision() {
	std::cout << "Exit Collision"<<endl;
}


//put in Ball.cpp
void GameObject::Bounce(string side) {
	if (side=="bottom" && setDirectionY > 0) {
		setDirectionY = -setDirectionY;
	}
	else if (side == "up" && setDirectionY < 0) {
		setDirectionY = -setDirectionY;
	}
	else if (side=="left" && setDirectionX < 0) {
		setDirectionX = -setDirectionX;
	}
	else if (side == "right" && setDirectionX > 0) {
		setDirectionX = -setDirectionX;
	}
}

string GameObject::SideCollision(GameObject* touchedObject){
	if (touchedObject->positionY > positionY + sizeHeight) {
		//std::cout << "Collision en bas" << std::endl;
		return "bottom";
	}
	else if (touchedObject->positionY + touchedObject->sizeHeight < positionY) {
		//std::cout << "Collision en haut" << std::endl;
		return "up";

	}else if(touchedObject->positionX > positionX){
		//std::cout << "Collision a droite" << std::endl;
		return "right";
	}
	else if (touchedObject->positionX < positionX) {
		//std::cout << "Collision a gauche" << std::endl;
		return "left";
	}
	return "";
}

//Start()
// 
//Stay()
//Exit()