#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "TextCard.h"
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

    int screenW;
	int screenH;
    int gameWidth;
    float fDeltaTime;
    bool fire;
    Ball* ball;
    GameObject* cannon;
    GameObject* home;
    GameObject* win;
    GameObject* lose;

    int currentLevel;
    int shotsLeft;
	std::map<std::string, TextCard*> cardsList;
    std::map<std::string, GameObject*> borderList;
    vector<Brick*> brickList;

    sf::Vector2i localPosition;

    string page = "home";


	GameWindow();

    bool loadLevelFromTxt();
    void Shoot();

    void Display();
    void DisplayGame();

    void Update();
    void ResetBall();

    bool Win();
    bool Defeat();

};

