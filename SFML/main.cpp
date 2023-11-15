#include "GameObject.h"
#include "GameWindow.h"
#include "InputManager.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
int main(int argc, char** argv)
{
    GameWindow game;
    InputManager inputs(&game) ;


    //GameLoop
    game.loadLevelFromTxt();

    while (game.oWindow->isOpen())
    {
        //EVENTS
        inputs.EventCheck();

        //UPDATES
        if (game.page == "game") {
            game.Update();
        }


        //DRAW
        game.Display();

        game.fDeltaTime = game.oClock.restart().asSeconds();
    }

    return 0;
}