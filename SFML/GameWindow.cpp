#include "GameWindow.h"

using namespace std;

typedef enum 
{
	BorderLeft,
	BorderRight,
	BorderTop,
	BorderBottom,

	Ball,
	Cannon,
	TestRectangle,
	TestRectangleTwo
};

GameWindow::GameWindow()
{
	

	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	screenW = desktopMode.width;
	screenH = desktopMode.height;
	gameWidth = screenW / 3;
	fDeltaTime = 0;
	fire = false;
	//Creating window
	oWindow = new sf::RenderWindow(desktopMode, "Breakout", sf::Style::Default);
	oWindow->setFramerateLimit(60);

	objectList = {
		//borders
		new GameObject(0, 0, gameWidth, screenH, sf::Color::White, 0, 0),
		new GameObject(gameWidth * 2, 0, gameWidth, screenH, sf::Color::White, 0, 0),
		new GameObject(gameWidth , 0, gameWidth, -10, sf::Color::Red, 0, 0),
		new GameObject(gameWidth, screenH, gameWidth, 10, sf::Color::Red, 0, 0),


		new GameObject((gameWidth * 1.5) - 25, screenH - 150, 10, sf::Color::Yellow),//ball
		new GameObject((gameWidth * 1.5) - 25, screenH - 150, 50, 150, sf::Color::Magenta, 0.5, 1),//cannon
		new GameObject((gameWidth * 1.4) - 25, screenH / 4, 150, 50, sf::Color::Red, 0, 0),//colision rectangle
		new GameObject((gameWidth * 1.4) - 25, screenH / 4, 100, 100, sf::Color::Cyan, 0, 0)//testing rect 2
	};
}

void GameWindow::Shoot(){
		objectList[Ball]->SetDirection(localPosition.x - objectList[Ball]->positionX, localPosition.y - objectList[Ball]->positionY);
		fire = true;
}

void GameWindow::Display() {
	oWindow->clear();

	if (fire) {
		objectList[Ball]->ObjectMove(fDeltaTime);
		oWindow->draw(*objectList[Ball]->oShape);
	}

	for (int i = 0; i < objectList.size(); i++) {

		oWindow->draw(*objectList[i]->oShape);
		if (objectList[i] == objectList[Cannon] || objectList[i] == objectList[Ball]) {
			continue;
		}else if (objectList[Ball]->Collision(objectList[i])) {
			if (objectList[i] == objectList[BorderBottom]){
				fire = false;
				delete objectList[Ball];
				objectList[Ball] = new GameObject((gameWidth * 1.5) - 25, screenH - 150, 10, sf::Color::Yellow);
			}else{
				objectList[Ball]->Bounce(objectList[Ball]->side);
			}
		}

		// makes the cyan test rectangle detect all collisions except his own
		if (objectList[i] == objectList[TestRectangleTwo]) {
			continue;
		}else objectList[TestRectangleTwo]->Collision(objectList[i]);
	
	}
	objectList[Cannon]->ObjectRotate(localPosition);
	oWindow->display();

	fDeltaTime = oClock.restart().asSeconds();
}