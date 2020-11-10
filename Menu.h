#ifndef _MENU_H_
#define _MENU_H_

#include "Library.h"

class Menu
{

protected:
	// Окно
	sf::RenderWindow window;
	sf::Event event;

public:
	Menu();

	int16_t menu();
};

#endif // !_MENU_H_
