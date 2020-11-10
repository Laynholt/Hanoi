#ifndef _MENU_H_
#define _MENU_H_

#include "Library.h"

class Menu
{

protected:
	// ������
	bool font_error;
	bool texture_error;

protected:
	// ����
	sf::RenderWindow window;
	sf::Event event;

	// �����
	sf::Font font;
	sf::Text text;

	// ���
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Menu();

	int16_t menu();

	void activate_button(sf::RectangleShape& rect, int16_t number_of_rect, bool is_settings, int16_t n_settings_button);
};

#endif // !_MENU_H_
