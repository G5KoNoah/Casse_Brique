#include "GameWindow.h"
#include <iostream>
#include <fstream>

using namespace std;


GameWindow::GameWindow()
{
	string line;
	int row = 0;

	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	screenW = desktopMode.width;
	screenH = desktopMode.height;
	gameWidth = screenW / 3;
	fDeltaTime = 0;
	fire = false;
	//Creating window
	oWindow = new sf::RenderWindow(desktopMode, "Usopp's Breakout", sf::Style::Default);
	oWindow->setFramerateLimit(60);

	currentLevel = 1;

	borderList["BorderLeft"] = new GameObject(0, 0, gameWidth, screenH, sf::Color::White, "bg2.png", 0, 0);//bordure gauche
	borderList["BorderRight"] = new GameObject(gameWidth * 2, 0, gameWidth, screenH, sf::Color::White, "bg1.png", 0, 0);//bordure droite
	borderList["BorderTop"] = new GameObject(gameWidth, 0, gameWidth, -10, sf::Color::Red, "", 0, 0);//bordure haut
	borderList["BorderBottom"] = new GameObject(gameWidth, screenH, gameWidth, 10, sf::Color::Red, "", 0, 0);//bordure bas

	cardsList["Win"] = new TextCard("Level Complete", "win.png", sf::Color::Red, textureMap);
	cardsList["Lose"] = new TextCard("Game Over", "lose.png", sf::Color::Red, textureMap);
	cardsList["Home"] = new TextCard("Welcome", "home.png", sf::Color::Red, textureMap);

	cannon = new GameObject(screenW / 2 + screenH / 220, screenH - 150, gameWidth / 8, screenH / 8, sf::Color::White, "cannon.png", 0.5, 1);//cannon
	ball = new Ball(screenW / 2 + screenH / 220, screenH - 150, screenH / 110, sf::Color::White, "ball.png");//balle
	

	for (const auto& pair : borderList) {
		pair.second->setObjectTexture(textureMap);
	}

	cannon->setObjectTexture(textureMap);
	ball->setObjectTexture(textureMap);

}

void GameWindow::Shoot(){

	ball->SetDirection(0, 0);

	ball->SetDirection(localPosition.x - ball->positionX, localPosition.y - ball->positionY);
	fire = true;
}

void GameWindow::Display() {
	oWindow->clear();
	if (page == "home") {
		cardsList["Home"]->Display(*oWindow);
	}
	else if (page == "win") {

		cardsList["Win"]->Display(*oWindow);
	}
	else if (page == "lose") {

		cardsList["Lose"]->Display(*oWindow);
	}
	else {
		DisplayGame();
	}
	oWindow->display();
}

void GameWindow::DisplayGame() {
	ball->Draw(*oWindow);
	cannon->Draw(*oWindow);
	
	for (const auto& pair : borderList) {
		(pair.second)->Draw(*oWindow);
	}
	
	for (int i = 0; i < brickList.size(); i++) {
		brickList[i]->Draw(*oWindow);
	}


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
				shotsLeft -= 1;
				ResetBall();

				if (Win()) {
					page = "win";
					cardsList["Win"]->SetText("LEVEL " + to_string(currentLevel) + " COMPLETE !");
				}
				else if (Defeat()) {
					page = "lose";
				}
			}
		}
	}
	for(int i =0; i< brickList.size();i++){
		ball->Collision(brickList[i]);
		brickList[i]->Collision(ball);
	}

	int brickListLength = brickList.size();
	int i = 0;
	while ( i < brickListLength) {

		if (brickList[i]->hp < 1) {
			std::cout << "destroyed ";
			delete brickList[i];
			brickList.erase(brickList.begin() + i);
			brickListLength -= 1;
		}
		else {
			i += 1;
		}
	}
}

void GameWindow::ResetBall() {
	fire = false;
	delete ball;
	ball = new Ball(screenW / 2 + screenH / 220, screenH - 150, screenH / 110, sf::Color::White, "ball.png");
	ball->setObjectTexture(textureMap);
}

bool GameWindow::loadLevelFromTxt() {
	string fileName = "level/level"+ to_string(currentLevel) + ".txt";
	if (brickList.size() != 0) {
		while (brickList.size() != 0) {
			delete brickList[brickList.size() - 1];
			brickList.pop_back();

		}
	}

	ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Couldn't open TXT file." << endl;
		return false;
	}

	string line;
	int row = 0;

	getline(file, line);
	shotsLeft = stoi(line);

	while (getline(file, line)) {
		int lineSize = min(int(line.size()), 10);
	

		for (size_t i = 0; i < lineSize; ++i) {
			int life = line[i] - '0';  // Convertir le caractère en entier

			// Ajouter la brique à la rangée
			brickList.push_back(new Brick(gameWidth + i * gameWidth / 10,screenH/10 + row * 25, gameWidth / 10, 25, sf::Color::White, "brick.png", 0, 0, life));
			brickList[brickList.size() - 1]->setObjectTexture(textureMap);
		}

		//Ajouter la rangée à la liste globale
		++row;
	}
	return true;
}

bool GameWindow::Win() {
	if (brickList.size()==0) {
		return true;
	}
	else {
		return false;
	}
}

bool GameWindow::Defeat() {
	if (shotsLeft <= 0) {
		return true;
	}
	return false;
}
