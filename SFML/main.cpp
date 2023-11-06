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
    GameObject* rectangle = new GameObject(0, 0, 50, 150, sf::Color::Red);
    GameObject* circle = new GameObject(70, 60, 100, sf::Color::Yellow);
    //GameLoop
    while (oWindow.isOpen())
    {
        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();
        }

        //UPDATE


        //DRAW
        oWindow.clear();
        oWindow.draw(*rectangle->oShape);
        oWindow.draw(*circle->oShape);
        oWindow.draw(*game->oShape);

        oWindow.display();
    }

    return 0;
}

