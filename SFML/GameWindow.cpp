#include "GameWindow.h"
#include <iostream>
#include <fstream>

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

	cannon = new GameObject(screenW / 2 + screenH / 220, screenH - 150, gameWidth / 8, screenH / 8, sf::Color::White, 0.5, 1);//cannon

	ball = new Ball(screenW / 2 + screenH / 220, screenH - 150, screenH / 110, sf::Color::White);//balle




	if (!textureCannon.loadFromFile("img/cannon.png"))
	{
		std::cout << "erreur texture";
	}
	textureCannon.setSmooth(true);
	cannon->setTexture(textureCannon);

	if (!textureBall.loadFromFile("img/ball.png"))
	{
		std::cout << "erreur texture";
	}
	textureBall.setSmooth(true);
	ball->setTexture(textureBall);

	if (!backGround1.loadFromFile("img/bg1.png"))
	{
		std::cout << "erreur texture";
	}
	backGround1.setSmooth(true);
	borderList["BorderRight"]->setTexture(backGround1);

	if (!backGround2.loadFromFile("img/bg2.png"))
	{
		std::cout << "erreur texture";
	}
	backGround2.setSmooth(true);
	borderList["BorderLeft"]->setTexture(backGround2);

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
	if(localPosition.y<cannon->positionY){
		cannon->ObjectRotate(localPosition);
	}


	if (fire) {
		ball->ObjectMove(fDeltaTime);
	}

	for(const auto& pair : borderList){
		if (ball->Collision(pair.second)) {
			if (pair.first == "BorderBottom") {
				fire = false;
				delete ball;
				ball = new Ball(screenW/2 + screenH / 220, screenH - 150, screenH/110, sf::Color::White);
				ball->setTexture(textureBall);
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

void GameWindow::LoadLevel1(){
	brickList.push_back(new Brick(gameWidth + gameWidth * 0.1, screenH * 0.3, gameWidth * 0.2, screenH / 20, sf::Color::Green, 0, 0, 4));
	brickList.push_back(new Brick(gameWidth + gameWidth * 0.7, screenH * 0.3, gameWidth * 0.2, screenH / 20, sf::Color::Green, 0, 0, 4));

	brickList.push_back(new Brick(gameWidth + gameWidth * 0.2, screenH * 0.5, gameWidth * 0.2, screenH / 20, sf::Color::Green, 0, 0, 4));
	brickList.push_back(new Brick(gameWidth + gameWidth * 0.6, screenH * 0.5, gameWidth * 0.2, screenH / 20, sf::Color::Green, 0, 0, 4));
	brickList.push_back(new Brick(gameWidth + gameWidth * 0.4, screenH * 0.55, gameWidth * 0.2, screenH / 20, sf::Color::Green, 0, 0, 4));
}