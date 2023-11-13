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

void GameObject::Draw(sf::RenderWindow& oWindow) {
	oWindow.draw(*oShape);
}

void GameObject::SetDirection(float fX, float fY) {
	sf::Vector2f vector = sf::Vector2f(fX, fY);
	vDirection = Math::Normalize(vector);
}

void GameObject::ObjectMove(float fDeltatime ) {


	
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
	if (side=="bottom" && vDirection.y > 0) {
		vDirection.y = -vDirection.y;
	}
	else if (side == "up" && vDirection.y < 0) {
		vDirection.y = -vDirection.y;
	}
	else if (side=="left" && vDirection.x < 0) {
		vDirection.x = -vDirection.x;
	}
	else if (side == "right" && vDirection.x > 0) {
		vDirection.x = -vDirection.x;
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