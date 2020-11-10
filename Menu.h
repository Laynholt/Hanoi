#ifndef _MENU_H_
#define _MENU_H_

#include "Library.h"

class Menu
{

protected:
	// ������
	bool texture_error;

protected:
	// ����
	sf::RenderWindow window;
	sf::Event event;

	// ���
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Menu();

	int16_t menu();
};

#endif // !_MENU_H_
