#pragma once

# include <vector>
#include <SFML/Graphics.hpp>

#include "GameObject.h"

using namespace std;

class GameWindow
{
public:
	sf::RenderWindow oWindow;
    sf::VideoMode oVideoMode;
    int screenW;
	int screenH;
    int gameWidth;
	vector<GameObject> objectList;
	
    sf::Clock oClock;
    float fDeltaTime = 0;
    bool fire = false;
    sf::Vector2i localPosition;
    sf::Vector2i directionBall;

	GameWindow();
};

