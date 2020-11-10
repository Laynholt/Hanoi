#ifndef _MENU_H_
#define _MENU_H_

#include "Library.h"

class Menu
{

protected:
	// Ошибки
	bool texture_error;

protected:
	// Окно
	sf::RenderWindow window;
	sf::Event event;

	// Фон
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Menu();

	int16_t menu();
};

#endif // !_MENU_H_
