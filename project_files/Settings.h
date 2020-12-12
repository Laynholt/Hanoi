#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "Window.h"

class Settings : public Window
{
private:
	sf::Sound click, scroll;
	sf::SoundBuffer click_buffer, scroll_buffer;

	int16_t _old_choose_disk;
	int16_t _old_choose_3d;
	int16_t _old_choose_music;

	int16_t _old_choose_scroll;

	bool scroll_error;
	bool click_error;

private:
	sf::RectangleShape rect_count_disks;
	std::vector<sf::RectangleShape> rect_nums_disks;
	sf::RectangleShape rect_3d;
	sf::RectangleShape rect_music;
	std::vector <sf::RectangleShape> rect_on_off_3d;
	std::vector <sf::RectangleShape> rect_on_off_music;

	std::vector<sf::Color> col;

public:
	Settings(Music& music);

	void create(sf::RenderWindow& window, Music& music, Flags_for_game& flags) override;
	void update(sf::RenderWindow& window, Music& music, Flags_for_game& flags) override;
	int16_t actions(sf::RenderWindow& window, Music& music, Flags_for_game& flags) override;

private:
	void activate_button(sf::RectangleShape& rect, int16_t number_of_rect, int16_t n_settings_button, sf::RenderWindow& window, Music& music, Flags_for_game& flags);
};

#endif // !_SETTINGS_H_
