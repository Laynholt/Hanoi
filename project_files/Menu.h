#ifndef _MENU_H_
#define _MENU_H_

#include "Window.h"

class Menu : public Window
{
private:
	sf::Text autor;
	sf::Sound click, scroll;
	sf::SoundBuffer click_buffer, scroll_buffer;

	int16_t _old_choose_scroll;

	bool scroll_error;
	bool click_error;

private:
	std::vector<sf::RectangleShape> rect;
	std::vector<sf::Color> col;
	std::vector<std::wstring> titles;

public:
	Menu(Music& music);

	void create(sf::RenderWindow& window, Music& music, Flags_for_game& flags) override;
	void update(sf::RenderWindow& window, Music& music, Flags_for_game& flags) override;
	int16_t actions(sf::RenderWindow& window, Music& music, Flags_for_game& flags) override;

private:
	void activate_button(int16_t number_of_rect, sf::RenderWindow& window, Music& music, Flags_for_game& flags);
};

#endif // !_MENU_H_
