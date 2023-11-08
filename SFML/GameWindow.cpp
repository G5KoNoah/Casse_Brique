#include "GameWindow.h"

GameWindow::GameWindow()
{
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	screenW = desktopMode.width;
	screenH = desktopMode.height;
	gameWidth = screenW / 3;
	fDeltaTime = 0;
	fire = false;
	//Creating window
	sf::RenderWindow oWindow(desktopMode, "Breakout", sf::Style::Default);
	oWindow.setFramerateLimit(120);

	objectList["borderLeft"] = new GameObject(0, 0, gameWidth, screenH, sf::Color::White, 0, 0);
	objectList["borderRight"] = new GameObject(gameWidth * 2, 0, gameWidth, screenH, sf::Color::White, 0, 0);
	objectList["borderTop"] = new GameObject(gameWidth , 0, gameWidth, -10, sf::Color::Red, 0, 0);
	objectList["borderBottom"] = new GameObject(gameWidth, screenH, gameWidth, 10, sf::Color::Red, 0, 0);

	objectList["canon"] = new GameObject((gameWidth * 1.5) - 25, screenH - 150, 50, 150, sf::Color::Red, 0.5, 1);
	objectList["ball"] = new GameObject((gameWidth * 1.5) - 25, screenH - 150, 10, sf::Color::Yellow);
	objectList["rectangleCollision"] = new GameObject((gameWidth * 1.4) - 25, screenH / 4, 150, 50, sf::Color::Red, 0, 0);

}

void GameWindow::Shoot(){
		delete objectList["ball"];
		objectList["ball"] = new GameObject((gameWidth * 1.5) - 25, screenH - 150, 10, sf::Color::Yellow);
		objectList["ball"]->setDirectionX = localPosition.x - objectList["ball"]->positionX;
		objectList["ball"]->setDirectionY = localPosition.y - objectList["ball"]->positionY;
		fire = true;
}

void GameWindow::Display() {
	oWindow.clear();
	for (int i = 0; i < objectList.size(); i++) {
		oWindow.draw(*objectList[i].oShape);
		if (objectList["ball"]->Collision(objectList[i].oShape)) {
			objectList["ball"]->Bounce(borderGame[i]);
		}
	}
	if (objectList["ball"]->Collision(*objectList["borderBottom"])) {
		fire = false;
	}

	for (int i = 0; i < oBricks.size(); i++) {
		oWindow.draw(*oBricks[i].oShape);
		if (objectList["ball"]->Collision(oBricks[i].oShape)) {
			objectList["ball"]->Bounce(oBricks[i]);
		}
		else {
			objectList["ball"]->ExitCollision();
		}
	}

	oWindow.draw(*objectList["canon"]->oShape);
	oWindow.draw(*objectList["rectangleCollision"]->oShape);

	if (fire) {
		objectList["ball"]->ObjectMove(fDeltaTime, localPosition);
		oWindow.draw(*objectList["ball"]->oShape);
	}

	objectList["canon"]->ObjectRotate(localPosition);
	oWindow.display();

	fDeltaTime = oClock.restart().asSeconds();
}