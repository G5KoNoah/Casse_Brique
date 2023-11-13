#pragma once

#include "GameObject.h";

class Ball : public GameObject
{
public:

	Ball(float posX, float posY, int rad, sf::Color color);
	void EnterCollision() override;
	void Bounce(string side);
};

