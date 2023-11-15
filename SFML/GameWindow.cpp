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
	oWindow = new sf::RenderWindow(desktopMode, "Breakout", sf::Style::Default);
	oWindow->setFramerateLimit(60);


	if (!font.loadFromFile("font/font.ttf")) {
		// Gestion de l'erreur si la police ne peut pas être chargée
		std::cout << "erreur font";
	}
	text.setFont(font);

	setCharacter("BIENVENUE");

	// choix de la couleur du texte
	text.setFillColor(sf::Color::Red);

	// choix du style du texte
	text.setStyle(sf::Text::Bold);

	text.setPosition(screenW / 3, screenH / 2);

	borderList["BorderLeft"] = new GameObject(0, 0, gameWidth, screenH, sf::Color::White, "bg2.png", 0, 0);//bordure gauche
	borderList["BorderRight"] = new GameObject(gameWidth * 2, 0, gameWidth, screenH, sf::Color::White, "bg1.png", 0, 0);//bordure droite
	borderList["BorderTop"] = new GameObject(gameWidth, 0, gameWidth, -10, sf::Color::Red, "", 0, 0);//bordure haut
	borderList["BorderBottom"] = new GameObject(gameWidth, screenH, gameWidth, 10, sf::Color::Red, "", 0, 0);//bordure bas

	cannon = new GameObject(screenW / 2 + screenH / 220, screenH - 150, gameWidth / 8, screenH / 8, sf::Color::White, "cannon.png", 0.5, 1);//cannon

	ball = new Ball(screenW / 2 + screenH / 220, screenH - 150, screenH / 110, sf::Color::White, "ball.png");//balle

	home = new GameObject(0, 0, screenW, screenH, sf::Color::White, "home.png", 0, 0);//cannon

	win = new GameObject(0, 0, screenW, screenH, sf::Color::White, "win.png", 0, 0);//cannon

	lose = new GameObject(0, 0, screenW, screenH, sf::Color::White, "lose.png", 0, 0);//cannon

	for (const auto& pair : borderList) {
		pair.second->setObjectTexture(textureMap);
	}

	cannon->setObjectTexture(textureMap);
	ball->setObjectTexture(textureMap);
	home->setObjectTexture(textureMap);
	win->setObjectTexture(textureMap);
	lose->setObjectTexture(textureMap);

	/*
	for (int i = 0; i < loadingList.size(); i++) {
		if (!texture.loadFromFile("img/" + loadingList[i].textureFilename))
		{
			std::cout << "erreur texture";
		}
		textureCannon.setSmooth(true);
		loadingList[i].setTexture(texture);

	}
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
	*/
}


void GameWindow::Shoot(){

	ball->SetDirection(0, 0);

	ball->SetDirection(localPosition.x - ball->positionX, localPosition.y - ball->positionY);
	fire = true;
}

void GameWindow::Display() {
	oWindow->clear();
	if (page == "home") {
		DisplayHome();
	}
	else if (page == "win") {
		DisplayWin();
	}
	else if (page == "lose") {
		DisplayLose();
	}
	else {
		DisplayGame();
	}
	oWindow->display();
}
void GameWindow::DisplayHome() {
	home->Draw(*oWindow);
	oWindow->draw(text);

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

void GameWindow::DisplayWin() {
	win->Draw(*oWindow);
	oWindow->draw(text);
}


void GameWindow::DisplayLose() {
	lose->Draw(*oWindow);
	oWindow->draw(text);
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
				comptDefeat += 1;
				ResetBall();
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

	if (Win()) {
		page = "win";
		setCharacter("LEVEL " + to_string(currentLevel) + " : TERMINE");
	}
	else if (Defeat()) {
		setCharacter("DOMMAGE");
		page = "lose";
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
			int del = brickList.size();
			delete brickList[del];
		}

	}

	ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Erreur lors de l'ouverture du fichier TXT." << endl;
		return false;
	}

	string line;
	int row = 0;

	while (getline(file, line)) {
		int lineSize = min(int(line.size()), 10);
	

		for (size_t i = 0; i < lineSize; ++i) {
			int life = line[i] - '0';  // Convertir le caractère en entier

			// Ajouter la brique à la rangée
			brickList.push_back(new Brick(gameWidth + i * gameWidth / 10,screenH/10 + row * 25, gameWidth / 10, 25, sf::Color::White, "brick.png", 0, 0, life));
			brickList[brickList.size() - 1]->setObjectTexture(textureMap);
		}

		//  Ajouter la rangée à la liste globale
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
	if (comptDefeat > condDefeat) {
		return true;
	}
	return false;
}

void GameWindow::setCharacter(string txt) {
	text.setString(txt);
	std::cout << txt.size();
	text.setCharacterSize(((screenW/3)/(txt.size()))*3);
}