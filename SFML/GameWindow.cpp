#include "GameWindow.h"

GameWindow::GameWindow()
{
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	screenW = desktopMode.width;
	screenH = desktopMode.height;
	gameWidth = screenW / 3;
	//Creating window
	sf::RenderWindow oWindow(desktopMode, "Breakout", sf::Style::Fullscreen);
	oWindow.setFramerateLimit(120);


}