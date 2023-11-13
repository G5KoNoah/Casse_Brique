#pragma once

# include <vector>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class GameObject
{
public:
	float positionX;
	float positionY;
	int size;
	int sizeHeight = 0;
	sf::Shape* oShape;
	sf::Color oColor;
	sf::Vector2f vDirection;
	float speed = 500.f;
	std::vector<GameObject*> objectCollision ;
	string side;


	GameObject(float posX, float posY, int sA, int sB, sf::Color color, float oriX, float oriY);
	GameObject(float posX, float posY, int rad, sf::Color color);
	void Draw(sf::RenderWindow& oWindow);
	void SetDirection(float fX, float fY);
	void ObjectMove(float fDeltaTime);
	void ObjectRotate(sf::Vector2i point);
	bool Collision(GameObject* touchedObject);
	void Bounce(string);
	virtual void EnterCollision( );
	virtual void StayCollision( );
	virtual void ExitCollision( );
	string SideCollision(GameObject* touchedObject);

private:
	void Initialize(float posX, float posY, sf::Color color);
};