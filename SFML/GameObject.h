#pragma once

# include <vector>
#include <SFML/Graphics.hpp>

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
	int setDirectionX = 0;
	int setDirectionY = 0;
	GameObject(float posX, float posY, int sA, int sB, sf::Color color);
	GameObject(float posX, float posY, int rad, sf::Color color);

	void ObjectMove(float fDeltaTime, sf::Vector2i direction);
	void ObjectRotate(sf::Vector2i point);
private:
	void Initialize(float posX, float posY, sf::Color color);
};