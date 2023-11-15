#include "InputManager.h"
#include "GameObject.h"
#include "GameWindow.h"

#include <iostream>
#include <SFML/Graphics.hpp>

InputManager::InputManager(GameWindow* window){
	game = window;
}

void InputManager::EventCheck(){
	game->localPosition = sf::Mouse::getPosition(*game->oWindow);
	//EVENT

	while (game->oWindow->pollEvent(oEvent))
	{
		if (oEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			game->oWindow->close();
		}

		else if (oEvent.type == sf::Event::MouseButtonReleased) {
			if (oEvent.mouseButton.button == sf::Mouse::Left) {
				if (game->page == "game" && !game->fire) {
					if (game->localPosition.y < game->cannon->positionY)
						game->Shoot();
				}
				else if (game->page == "win") {
					game->currentLevel += 1;
					game->comptDefeat = 1;
					game->ResetBall();
					game->loadLevelFromTxt();
					game->page = "game";
				}
				else if (game->page == "home") {
					game->currentLevel = 1;
					game->comptDefeat = 1;
					game->ResetBall();
					game->page = "game";
				}
				else  if (game->page == "lose") {
					game->page = "home";
				}
			}
		}
	}


}