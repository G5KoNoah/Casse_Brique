#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Ball.h"
#include "Brick.h"

using namespace std;

class GameWindow
{
public:
	sf::RenderWindow* oWindow;
    sf::VideoMode oVideoMode;
    sf::Clock oClock;

    map<string, sf::Texture> textureMap;

    sf::Texture texture;
	sf::Texture textureCannon;
	sf::Texture textureBall;
	sf::Texture backGround1;
	sf::Texture backGround2;

    int screenW;
	int screenH;
    int gameWidth;
    float fDeltaTime;
    bool fire;
    Ball* ball;
    GameObject* cannon;

	std::map<std::string, GameObject*> borderList;
    vector<Brick*> brickList;

    sf::Vector2i localPosition;

	GameWindow();

    bool loadLevelFromTxt(const string& filename);
    void Shoot();
    void Display();
    void Update();
};

