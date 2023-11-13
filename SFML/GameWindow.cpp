#include "GameWindow.h"
#include <iostream>
using namespace std;


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

	
	borderList["BorderLeft"] = new GameObject(0, 0, gameWidth, screenH, sf::Color::White, 0, 0);//bordure gauche
	borderList["BorderRight"] = new GameObject(gameWidth * 2, 0, gameWidth, screenH, sf::Color::White, 0, 0);//bordure droite
	borderList["BorderTop"] = new GameObject(gameWidth, 0, gameWidth, -10, sf::Color::Red, 0, 0);//bordure haut
	borderList["BorderBottom"] = new GameObject(gameWidth, screenH, gameWidth, 10, sf::Color::Red, 0, 0);//bordure bas

	cannon = new GameObject((gameWidth * 1.5) - 25, screenH - 150, 50, 150, sf::Color::Magenta, 0.5, 1);//cannon

	ball = new Ball((gameWidth * 1.5) - 25, screenH - 150, 10, sf::Color::Yellow);//balle

	brickList.push_back(new Brick((gameWidth * 1.4) - 25, screenH / 4, 150, 50, sf::Color::Green, 0, 0, 4));
}

void GameWindow::Shoot(){

	ball->SetDirection(0, 0);

	ball->SetDirection(localPosition.x - ball->positionX, localPosition.y - ball->positionY);
	fire = true;
}

void GameWindow::Display() {
	oWindow->clear();

	ball->Draw(*oWindow);
	cannon->Draw(*oWindow);
	
	for (const auto& pair : borderList) {
		(pair.second)->Draw(*oWindow);
	}
	
	for (int i = 0; i < brickList.size(); i++) {
		brickList[i]->Draw(*oWindow);
	}
	
	oWindow->display();

}

void GameWindow::Update() {
	
	cannon->ObjectRotate(localPosition);

	if (fire) {
		ball->ObjectMove(fDeltaTime);
	}

	for(const auto& pair : borderList){
		if (ball->Collision(pair.second)) {
			if (pair.first == "BorderBottom") {
				fire = false;
				delete ball;
				ball = new Ball((gameWidth * 1.5) - 25, screenH - 150, 10, sf::Color::Yellow);
			}
		}
	}
	for(int i =0; i< brickList.size();i++){
		ball->Collision(brickList[i]);
	}

	int brickListLength = brickList.size();
	int i = 0;
	while ( i < brickListLength) {
		brickList[i]->Collision(ball);
		if (brickList[i]->hp < 1) {
			std::cout << "detruit";
			delete brickList[i];
			brickList.erase(brickList.begin() + i);
			brickListLength -= 1;
		}
		else {
			i += 1;
		}
	}


}
