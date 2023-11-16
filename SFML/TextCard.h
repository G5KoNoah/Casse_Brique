#pragma once

#include "GameObject.h"

#include <SFML/Graphics.hpp>
#include <string>

class TextCard
{
public:
	sf::Text text;
	sf::Color textColor;
	sf::Font font;
	GameObject* background;

	TextCard(string txt, string filename, sf::Color color, map<string, sf::Texture>& textureMap);

	void Display(sf::RenderWindow& cWindow);
	void SetText(std::string newTxt);
};

