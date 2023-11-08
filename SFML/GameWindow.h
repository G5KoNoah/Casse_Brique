#pragma once

#include <map>
#include <SFML/Graphics.hpp>

#include "GameObject.h"

using namespace std;

class GameWindow
{
public:
	sf::RenderWindow oWindow;
    sf::VideoMode oVideoMode;
    sf::Clock oClock;
    sf::Event oEvent;
    
    int screenW;
	int screenH;
    int gameWidth;
    float fDeltaTime;;
    bool fire;

	map<const char*,GameObject*> objectList;
	

    sf::Vector2i localPosition;

	GameWindow();
    
    void Shoot();
    void Display();
};

