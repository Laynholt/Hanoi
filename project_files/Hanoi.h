#ifndef _HANOI_H_
#define _HANOI_H_

#include "Menu.h"


class Hanoi : public Menu
{
private:
	bool back_to_menu;


private:
	int16_t pin;
	float horisontal_width, vertical_height;

	int16_t FOR_3D;

private:
	// Стержни
	sf::RectangleShape horisontal;
	std::vector<sf::RectangleShape> vertical;

	// Указатель
	sf::CircleShape triangle;

public:
	Hanoi();

	void Loop();
};

#endif // !_HANOI_H_

