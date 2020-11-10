#ifndef _HANOI_H_
#define _HANOI_H_

#include "Menu.h"

#define SCALE 1.0f
#define SCALE_STEP 0.15f

#define DISK_HEIGHT_DEP_OF_HEIGHT 0.15f

class Hanoi : public Menu
{
private:
	bool back_to_menu;


private:
	int16_t pin;
	float horisontal_width, vertical_height;

	std::vector<float> full_heights;

	int16_t FOR_3D;

private:
	// Диски
	std::vector<sf::RectangleShape> disks;
	std::vector<std::stack<sf::RectangleShape>> stacks;

	// Стержни
	sf::RectangleShape horisontal;
	std::vector<sf::RectangleShape> vertical;

	// Указатель
	sf::CircleShape triangle;

public:
	Hanoi();

	void Loop();

private:
	int16_t actions();

	void restart();

	void draw_tower();
	bool move_disk(int8_t from_pin, int8_t to_pin, int16_t new_pin);
};

#endif // !_HANOI_H_

