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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            delete game.objectList[7]; 
            game.objectList[7] = new GameObject(game.localPosition.x, game.localPosition.y, 100, 100, sf::Color::Cyan, 0, 0);
        }

        //Draw
        game.Display();
    }

    return 0;
}

