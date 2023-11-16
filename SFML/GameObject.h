#pragma once

# include <vector>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class GameObject
{
public:
	float positionX;
	float positionY;
	int size;
	int sizeHeight = 0;
	string textureFilename;
	sf::Texture* texture;

	sf::Shape* oShape;
	sf::Color oColor;
	sf::Vector2f vDirection;
	float speed = 500.f;
	std::vector<GameObject*> objectCollision;


	GameObject(float posX, float posY, int sA, int sB, sf::Color color, string filename, float oriX, float oriY);
	GameObject(float posX, float posY, int rad, sf::Color color, string filename);
	void Draw(sf::RenderWindow& oWindow);
	void SetDirection(float fX, float fY);
	void ObjectMove(float fDeltaTime);
	void ObjectRotate(sf::Vector2i point);
	bool Collision(GameObject* touchedObject);
	bool Interaction(GameObject* touchedObject);
	virtual void EnterCollision(string side);
	virtual void StayCollision();
	virtual void ExitCollision();
	string SideCollision(GameObject* touchedObject);
	void setObjectTexture(map<string, sf::Texture>& textureMap);

private:
	void Initialize(float posX, float posY, sf::Color color, string filename);
};