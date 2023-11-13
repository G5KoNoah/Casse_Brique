#include "GameObject.h"
#include "GameWindow.h"
#include "InputManager.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
int main(int argc, char** argv)
{
    GameWindow game;
    InputManager inputs(&game) ;
    //GameLoop

    while (game.oWindow->isOpen())
    {
        //EVENTS
        inputs.ButtonPressed();

        //UPDATES
        game.Update();

        //DRAW
        game.Display();

        game.fDeltaTime = game.oClock.restart().asSeconds();
    }

    return 0;
}

