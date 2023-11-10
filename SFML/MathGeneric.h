#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>


namespace Math {
	sf::Vector2f Normalize(sf::Vector2f);
	float arcTan(sf::Vector2i vector, int X, int Y);
};