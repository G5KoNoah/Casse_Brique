#include "GameObject.h"
#include "GameWindow.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
int main(int argc, char** argv)
{
    GameWindow game;

    //GameLoop

    while (game.oWindow->isOpen())
    {
		game.localPosition = sf::Mouse::getPosition(*game.oWindow);
        //EVENT

        while (game.oWindow->pollEvent(game.oEvent))
        {
            if (game.oEvent.type == sf::Event::Closed)
                game.oWindow->close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !game.fire) {
            game.Shoot();
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// left key is pressed: move our character
            game.objectList[4]->setDirectionX = -1;
            game.objectList[4]->ObjectMove(game.fDeltaTime);
		}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			game.objectList[4]->setDirectionX = 1;
			game.objectList[4]->ObjectMove(game.fDeltaTime);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            game.objectList[4]->setDirectionY = -1;
            game.objectList[4]->ObjectMove(game.fDeltaTime);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            game.objectList[4]->setDirectionY = 1;
            game.objectList[4]->ObjectMove(game.fDeltaTime);
        }
        //Draw
        game.Display();
    }

    return 0;
}

