#include "GameObject.h"
#include "GameWindow.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
int main(int argc, char** argv)
{
    GameWindow game;

    //GameLoop

    while (game.oWindow.isOpen())
    {
		game.localPosition = sf::Mouse::getPosition(game.oWindow);
        //EVENT
        sf::Event oEvent;

        while (game.oWindow.pollEvent(game.oEvent))
        {
            if (game.oEvent.type == sf::Event::Closed)
                game.oWindow.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !game.fire) {
            game.Shoot();
        }

        //Draw
        game.Display();
    }

    return 0;
}

