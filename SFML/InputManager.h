#pragma once
#include <SFML/Graphics.hpp>
class GameWindow;

class InputManager
{
public:
	GameWindow* game;
	sf::Event oEvent;

	InputManager(GameWindow* window);
	
	void EventCheck();
};

