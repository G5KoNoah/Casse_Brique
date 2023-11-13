#include "MathGeneric.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 3.14159265;

sf::Vector2f Math::Normalize(sf::Vector2f vector) {
	sf::Vector2f cache = vector;
	vector.x /= sqrt(cache.x * cache.x + cache.y * cache.y);
	vector.y /= sqrt(cache.x * cache.x + cache.y * cache.y);
	return vector;
}

float Math::arcTan(sf::Vector2i vector, int X, int Y) {
	float deg = atan2(vector.x - X, -(vector.y - Y)) * 180 / PI;
	return deg;
}

bool Math::between(float value, float min, float max) {
	if (value < max and value > min) {
		return true;
	}
	else {
		return false;
	}
}