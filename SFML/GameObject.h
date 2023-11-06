#pragma once

# include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class GameObject
{
public:
	int positionX;
	int positionY;
	int size;
	int sizeHeight = 0;
	sf::Shape* oShape;
	sf::Color oColor;

	GameObject(int posX, int posY, int sA, int sB, sf::Color color);
	GameObject(int posX, int posY, int rad, sf::Color color);
};