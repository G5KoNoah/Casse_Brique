#include "GameObject.h"

#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int heightScreen = desktopMode.height;
    int widthScreen = desktopMode.width;
    //Création d'une fenêtre
    sf::RenderWindow oWindow(desktopMode, "Breakout", sf::Style::Default); 
    oWindow.setFramerateLimit(60);

    //Création d'un cercle de radius 100
    sf::CircleShape oCircle(100.f);
    //A la position 0, 0
    oCircle.setPosition(0.f, 0.f);
    //Et de couleur verte
    oCircle.setFillColor(sf::Color::Green);


    //Création d'un rectangle de taille 50, 50
    sf::RectangleShape oRectangle(sf::Vector2f(50.f, 50.f));
    //A la position 100, 100
    oRectangle.setPosition(100.f, 100.f);
    //Et de couleur rouge
    oRectangle.setFillColor(sf::Color::Red);
    int gameWidth = widthScreen / 3;
   
    GameObject* game = new GameObject(gameWidth, 0, gameWidth, heightScreen, sf::Color::White);
    GameObject* rectangle = new GameObject((gameWidth*1.5)-25, heightScreen-150, 50, 150, sf::Color::Red);
    GameObject* circle = new GameObject((gameWidth * 1.5) - 25, heightScreen - 150, 50, sf::Color::Yellow);


    //GameLoop
    sf::Clock oClock;
    float fDeltaTime = 0;
    bool fire = false;
    sf::Vector2i localPosition;
    while (oWindow.isOpen())
    {
        localPosition = sf::Mouse::getPosition(oWindow);
        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !fire) {

            fire = true;
        }
        //UPDATE


        oWindow.clear();
        oWindow.draw(*game->oShape);
        oWindow.draw(*rectangle->oShape);
        if (fire) {
            circle->ObjectMove(fDeltaTime, localPosition, widthScreen, heightScreen);
            oWindow.draw(*circle->oShape);
        }
        //DRAW

 

        rectangle->ObjectRotate(localPosition,0.5, 1);
        oWindow.display();
        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}

