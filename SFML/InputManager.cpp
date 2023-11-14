#include "InputManager.h"
#include "GameObject.h"
#include "GameWindow.h"

#include <iostream>
#include <SFML/Graphics.hpp>

InputManager::InputManager(GameWindow* window){
	game = window;
}

void InputManager::ButtonPressed(){
	game->localPosition = sf::Mouse::getPosition(*game->oWindow);
	//EVENT

	while (game->oWindow->pollEvent(oEvent))
	{
		if (oEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			game->oWindow->close();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !game->fire) {
		if (game->localPosition.y < game->cannon->positionY)
			game->Shoot();
	}
}