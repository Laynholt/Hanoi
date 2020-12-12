#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Library.h"
#include "Music.h"

struct Flags_for_game
{
public:
	bool go_to_game;
	bool go_to_menu;
	bool go_to_settings;

	bool from_settings;

	bool disable_3d;
	int16_t number_of_disks;

	Flags_for_game()
	{
		go_to_game = false;
		go_to_menu = true;
		go_to_settings = false;

		from_settings = false;

		disable_3d = false;
		number_of_disks = 0;
	}
};

class Window
{
public:
	Window();

	virtual void create(sf::RenderWindow& window, Music& music, Flags_for_game& flags) = 0;
	virtual void update(sf::RenderWindow& window, Music& music, Flags_for_game& flags) = 0;
	virtual int16_t actions(sf::RenderWindow& window, Music& music, Flags_for_game& flags) = 0;

protected:
	sf::Event event;

	// Текст
	sf::Font font;
	sf::Text text;

	// Фон
	sf::Texture texture;
	sf::Sprite sprite;

protected:
	// Ошибки
	bool font_error;
	bool texture_error;


};
#endif // !_WINDOW_H_
