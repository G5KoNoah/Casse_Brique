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

	// sf::SoundBuffer buffer;
	// if (!buffer.loadFromFile("sound.wav"))
	// 	return -1;

	// sf::Sound sound;
	// sound.setBuffer(buffer);
	// sound.play();

    //GameLoop
    game.loadLevelFromTxt("level/level1.txt");

    while (game.oWindow->isOpen())
    {
        //EVENTS
        inputs.EventCheck();

        //UPDATES
        game.Update();

        //DRAW
        game.Display();

        game.fDeltaTime = game.oClock.restart().asSeconds();
    }

    return 0;
}