#include "TextCard.h"

#include <iostream>

using namespace std;

TextCard::TextCard( string txt, string filename, sf::Color color, map<string, sf::Texture>& textureMap) {

	textColor = color;
	text.setString(txt);
	text.setCharacterSize(150);

	if (!font.loadFromFile("font/font.ttf")) {
		// Gestion de l'erreur si la police ne peut pas être chargée
		cout << "erreur font";
	}
	else {
		text.setFont(font);
	}
	
	// choix de la couleur du texte
	text.setFillColor(color);

	// choix du style du texte
	text.setStyle(sf::Text::Bold);

	background = new GameObject(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, sf::Color::White, filename, 0, 0);
	background->setObjectTexture(textureMap);
}

void TextCard::Display(sf::RenderWindow& cWindow) {
	background->Draw(cWindow);
	cWindow.draw(text);
}

void TextCard::SetText(std::string newTxt) {
	text.setString(newTxt);
}