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
    GameObject* home;
    GameObject* win;
    GameObject* lose;

    int currentLevel = 1;
	std::map<std::string, GameObject*> borderList;
    vector<Brick*> brickList;

    sf::Vector2i localPosition;

    sf::Font font;
    sf::Text text;

    string page = "home";

    int comptDefeat = 1;
    int condDefeat = 1;

	GameWindow();

    bool loadLevelFromTxt();
    void Shoot();

    void Display();
    void DisplayHome();
    void DisplayGame();
    void DisplayWin();
    void DisplayLose();

    void Update();
    void ResetBall();

    bool Win();
    bool Defeat();

    void setCharacter(string txt);
};

