#include "GameObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
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
    

    GameObject* borderLeft = new GameObject(0, 0, gameWidth, heightScreen, sf::Color::White, 0, 0);
    GameObject* borderRight = new GameObject(gameWidth*2, 0, gameWidth, heightScreen, sf::Color::White, 0, 0);
    GameObject* borderTop = new GameObject(gameWidth , 0, gameWidth, -10, sf::Color::Red, 0, 0);
    GameObject* borderBottom = new GameObject(gameWidth, heightScreen, gameWidth, 10, sf::Color::Red, 0, 0);

    vector<GameObject> game = {*borderLeft, *borderRight, *borderBottom, *borderTop};

    GameObject* canon = new GameObject((gameWidth*1.5)-25, heightScreen-150, 50, 150, sf::Color::Red, 0.5, 1);
    GameObject* circle = new GameObject((gameWidth * 1.5) - 25, heightScreen - 150, 10, sf::Color::Yellow);
    GameObject* rectangleCollision = new GameObject((gameWidth * 1.4) - 25, heightScreen - 150, 50, 150, sf::Color::Red,0,0);

    //GameLoop
    sf::Clock oClock;
    float fDeltaTime = 0;
    bool fire = false;
    sf::Vector2i localPosition;
    sf::Vector2i directionBall;
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
            circle = new GameObject((gameWidth * 1.5) - 25, heightScreen - 150, 10, sf::Color::Yellow);
            directionBall = localPosition;
            circle->setDirectionX = directionBall.x - circle->positionX;
            circle->setDirectionY = directionBall.y - circle->positionY;
            fire = true;
        }

        //Draw
        oWindow.clear();
        for (int i = 0; i < game.size();i++) {
            oWindow.draw(*game[i].oShape);
            if (circle->Collision(game[i].oShape)) {
                circle->Bounce();
            }
        }

        oWindow.draw(*canon->oShape);
        oWindow.draw(*rectangleCollision->oShape);

        if (fire) {
            circle->ObjectMove(fDeltaTime, directionBall);
            oWindow.draw(*circle->oShape);
        }
        
        canon->ObjectRotate(localPosition);
        oWindow.display();
        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}

