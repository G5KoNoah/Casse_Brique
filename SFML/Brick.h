#pragma once

#include "GameObject.h";

class Brick : public GameObject
{
public:
	int hp;

	Brick(float posX, float posY, int sA, int sB, sf::Color color, string filename, float oriX, float oriY, int hits = 1);
	~Brick();

	void EnterCollision(string side) override;
	void ColorSetOnHP();
};

