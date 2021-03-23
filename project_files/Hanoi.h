#ifndef _HANOI_H_
#define _HANOI_H_

#include "Window.h"

#define SCALE 1.0f
#define SCALE_STEP 0.15f

#define DISK_HEIGHT_DEP_OF_HEIGHT 0.15f

class Hanoi : public Window
{
private:
	// Ошибки
	bool sound_error;
	bool congrats_error;
	bool disk_sound_error;

private:
	int16_t pin;
	float horisontal_width, vertical_height;

	std::vector<float> full_heights;

	int16_t count;
	int16_t count_built_tower;
	int16_t started_tower;
	int16_t best_count;

	int16_t FOR_3D;

private:
	// Плашка на которой будет лежать текст
	sf::RectangleShape rect_for_text;

	// Диски
	std::vector<sf::RectangleShape> disks;
	std::vector<std::stack<sf::RectangleShape>> stacks;

	// Стержни
	float vertical_x;
	sf::RectangleShape horisontal;
	std::vector<sf::RectangleShape> vertical;

	// Указатель
	float _radius;
	sf::CircleShape triangle;

	// Звуки
	sf::Sound wrong_sound;
	sf::Sound disk_sound;
	sf::Sound congrats_sound;
	sf::SoundBuffer sound_buffer1, sound_buffer2, sound_buffer3;

public:
	Hanoi(Music& music, Flags_for_game& flags);

	void create(sf::RenderWindow& window, Music& music, Flags_for_game& flags) override;
	void update(sf::RenderWindow& window, Music& music, Flags_for_game& flags) override;
	int16_t actions(sf::RenderWindow& window, Music& music, Flags_for_game& flags) override;

private:
	void restart(sf::RenderWindow& window, Music& music, Flags_for_game& flags);

	void draw_tower(sf::RenderWindow& window);
	bool move_disk(int8_t from_pin, int8_t to_pin, int16_t new_pin);
	void counting_built_towers(Music& music, Flags_for_game& flags);
};

#endif // !_HANOI_H_

