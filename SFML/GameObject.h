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

	GameObject(float posX, float posY, int sA, int sB, sf::Color color);
	GameObject(float posX, float posY, int rad, sf::Color color);

	void ObjectMove(float fDeltaTime, sf::Vector2i direction, int scrnW, int scrnH);
	void ObjectRotate(sf::Vector2i positionMouse, float fOriginX, float fOriginY);
private:
	void Initialize(float posX, float posY, sf::Color color);
};