#ifndef _MENU_H_
#define _MENU_H_

#include "Library.h"

class Menu
{
private:
	sf::Text autor;
	sf::Sound click, scroll;
	sf::SoundBuffer click_buffer, scroll_buffer;

	int16_t _old_choose_disk;
	int16_t _old_choose_3d;
	int16_t _old_choose_music;

	int16_t _old_choose_scroll;

	bool go_to_game;

protected:
	bool disable_music;
	bool disable_3d;
	int16_t number_of_disks;

protected:
	// Ошибки
	bool font_error;
	bool texture_error;
	bool music_error;
	bool scroll_error;
	bool click_error;

protected:
	// Окно
	sf::RenderWindow window;
	sf::Event event;

	// Текст
	sf::Font font;
	sf::Text text;

	// Фон
	sf::Texture texture;
	sf::Sprite sprite;

	// Музыка
	sf::Music music;

public:
	Menu();

	int16_t menu();

private:
	void activate_button(sf::RectangleShape& rect, int16_t number_of_rect, bool is_settings, int16_t n_settings_button);
	void settings();
};

#endif // !_MENU_H_
