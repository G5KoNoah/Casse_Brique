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
	vector<GameObject> objectList;
	
	GameWindow();
};

