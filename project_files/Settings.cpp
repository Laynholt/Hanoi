#include "Settings.h"

Settings::Settings(Music& music)
{
	// Подключаем звук клика
	click_error = false;
	if (!click_buffer.loadFromFile("recources/sounds/click1.ogg"))
	{
		std::wcout << L"\nSound click error!" << std::endl;
		click_error = true;
	}

	else { click.setVolume(MUSIC_VOLUME + music.music_volume); }

	// Подключаем звук скролла
	scroll_error = false;
	if (!scroll_buffer.loadFromFile("recources/sounds/scroll2.ogg"))
	{
		std::wcout << L"\nSound scroll error!" << std::endl;
		scroll_error = true;
	}

	else { scroll.setVolume(MUSIC_VOLUME + music.music_volume); }

	_old_choose_scroll = -1;
	_old_choose_disk = _old_choose_3d = _old_choose_music = 0;

	rect_nums_disks.resize(4);
	rect_on_off_3d.resize(2);
	rect_on_off_music.resize(2);
}

void Settings::create(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	flags.from_settings = true;
	flags.go_to_menu = flags.go_to_game = false;

	_old_choose_scroll = -1;

	col.clear();

	col.push_back(sf::Color(0, 162, 232, 255));
	col.push_back(sf::Color(232, 220, 0, 255));
	col.push_back(sf::Color(34, 177, 76, 255));
	col.push_back(sf::Color(150, 16, 106, 255));

	col.push_back(sf::Color(0, 64, 128, 255));
	col.push_back(sf::Color(128, 64, 0, 255));

	col.push_back(sf::Color(138, 234, 152, 255));
	col.push_back(sf::Color(200, 188, 241, 255));

	// Статичные
	// Плашка количество дисков
	rect_count_disks.setSize(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 6));
	rect_count_disks.setPosition(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 12));
	rect_count_disks.setFillColor(sf::Color(255, 137, 39, 255));

	// Плашка 3D
	rect_3d.setSize(sf::Vector2f(SCREEN_WIDTH / 4 - 10, SCREEN_HEIGHT / 6));
	rect_3d.setPosition(sf::Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2));
	rect_3d.setFillColor(sf::Color(200, 191, 231, 255));

	// Плашка Музыки
	rect_music.setSize(sf::Vector2f(SCREEN_WIDTH / 4 - 10, SCREEN_HEIGHT / 6));
	rect_music.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 + 10, SCREEN_HEIGHT / 2));
	rect_music.setFillColor(sf::Color(163, 73, 164, 255));

	// Динамические
	for (int16_t i = 0; i < 4; i++)
	{
		rect_nums_disks[i].setSize(sf::Vector2f(SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6 - 10));
		rect_nums_disks[i].setPosition(sf::Vector2f((SCREEN_HEIGHT / 6 + 10) * i + SCREEN_WIDTH / 4 + SCREEN_HEIGHT / 12, 7 * SCREEN_HEIGHT / 24));
		rect_nums_disks[i].setFillColor(col[i]);
	}

	float _x;
	for (int16_t i = 0; i < 2; i++)
	{
		rect_on_off_3d[i].setSize(sf::Vector2f(SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6 - 10));

		_x = SCREEN_WIDTH / 4 + rect_3d.getSize().x / 10 + i * (rect_on_off_3d[0].getSize().x + 10);

		rect_on_off_3d[i].setPosition(sf::Vector2f(_x, 17 * SCREEN_HEIGHT / 24));
		rect_on_off_3d[i].setFillColor(col[4 + i]);

		rect_on_off_music[i].setSize(sf::Vector2f(SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6 - 10));
		rect_on_off_music[i].setPosition(sf::Vector2f(_x + rect_3d.getSize().x + 20, 17 * SCREEN_HEIGHT / 24));
		rect_on_off_music[i].setFillColor(col[6 + i]);
	}

	if (!click_error) { click.setBuffer(click_buffer); click.setVolume(MUSIC_VOLUME + music.music_volume); }
	if (!scroll_error) { scroll.setBuffer(scroll_buffer); scroll.setVolume(MUSIC_VOLUME + music.music_volume); }
}

void Settings::update(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	std::wstring str;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		actions(window, music, flags);

		// Экшены
		for (int16_t i = 0; i < 4; i++)
		{
			activate_button(rect_nums_disks[i], i, 0, window, music, flags);
		}
		for (int16_t i = 0; i < 2; i++)
		{
			activate_button(rect_on_off_3d[i], i, 1, window, music, flags);
			activate_button(rect_on_off_music[i], i, 2, window, music, flags);
		}
	}

	window.clear();

	if (!texture_error) window.draw(sprite);

	if (!font_error)
	{
		text.setStyle(sf::Text::Bold);
		text.setString(L"Громкость: " + std::to_wstring((int16_t)MUSIC_VOLUME + (int16_t)music.music_volume));
		text.setCharacterSize(20);
		text.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 40));
		window.draw(text);
		text.setCharacterSize(60);
	}

	// Рисуем прямоугольник Количества дисков и надпись
	window.draw(rect_count_disks);
	if (!font_error)
	{
		text.setStyle(sf::Text::Regular);
		str = L"Количество дисков";
		text.setString(str);
		text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - text.getCharacterSize() * str.length() / 4 - 30,
			rect_count_disks.getSize().y - 40));
		window.draw(text);
	}

	// Рисуем прямоугольник 3Д и надпись
	window.draw(rect_3d);
	if (!font_error)
	{
		str = L"3D";
		text.setString(str);
		text.setPosition(sf::Vector2f(rect_3d.getPosition().x - text.getCharacterSize() * str.length() / 4 + rect_3d.getSize().x / 2,
			rect_3d.getPosition().y + 10));
		window.draw(text);
	}

	// Рисуем прямоугольник Музыка и надпись
	window.draw(rect_music);
	if (!font_error)
	{
		str = L"Музыка";
		text.setString(str);
		text.setPosition(sf::Vector2f(rect_music.getPosition().x + text.getCharacterSize() * str.length() / 4 - 50,
			rect_music.getPosition().y + 10));
		window.draw(text);
	}

	// Рисуем выбор количества дисков
	for (int16_t i = 0; i < 4; i++)
	{
		if (i == _old_choose_disk)
		{
			rect_nums_disks[i].setOutlineThickness(5);
			rect_nums_disks[i].setOutlineColor(sf::Color::White);
		}
		else
		{
			rect_nums_disks[i].setOutlineThickness(0);
		}

		window.draw(rect_nums_disks[i]);

		if (!font_error)
		{
			str = std::to_wstring(3 + i);
			text.setString(str);
			text.setPosition(sf::Vector2f(rect_nums_disks[i].getPosition().x - text.getCharacterSize() * str.length() / 4 + rect_nums_disks[i].getSize().x / 2,
				rect_nums_disks[i].getPosition().y + 10));
			window.draw(text);
		}
	}

	// Рисуем вкл откл ползунков
	for (int16_t i = 0, j = 1; i < 2; i++, j--)
	{
		if (i == _old_choose_3d)
		{
			rect_on_off_3d[i].setOutlineThickness(5);
			rect_on_off_3d[i].setOutlineColor(sf::Color::White);
		}
		else { rect_on_off_3d[i].setOutlineThickness(0); }

		if (i == _old_choose_music)
		{
			rect_on_off_music[i].setOutlineThickness(5);
			rect_on_off_music[i].setOutlineColor(sf::Color::White);
		}
		else { rect_on_off_music[i].setOutlineThickness(0); }

		// 3D надпись
		window.draw(rect_on_off_3d[i]);
		if (!font_error)
		{
			str = std::to_wstring(j);
			text.setString(str);
			text.setPosition(sf::Vector2f(rect_on_off_3d[i].getPosition().x - text.getCharacterSize() * str.length() / 4 + rect_on_off_3d[i].getSize().x / 2,
				rect_on_off_3d[i].getPosition().y + 10));
			window.draw(text);
		}

		// Музыка надпись
		window.draw(rect_on_off_music[i]);
		if (!font_error)
		{
			str = std::to_wstring(j);
			text.setString(str);
			text.setPosition(sf::Vector2f(rect_on_off_music[i].getPosition().x - text.getCharacterSize() * str.length() / 4 + rect_on_off_music[i].getSize().x / 2,
				rect_on_off_music[i].getPosition().y + 10));
			window.draw(text);
		}
	}
}

void Settings::activate_button(sf::RectangleShape& rect, int16_t number_of_rect, int16_t n_settings_button, sf::RenderWindow& window, Music& music,
	Flags_for_game& flags)
{
	sf::Vector2i mouse;

	mouse = sf::Mouse::getPosition(window);

	if (mouse.x >= rect.getPosition().x && mouse.x <= (rect.getPosition().x + rect.getSize().x) &&
		mouse.y >= rect.getPosition().y && mouse.y <= (rect.getPosition().y + rect.getSize().y))
	{
		rect.setScale(sf::Vector2f(1.0f, 1.1f));

		if (number_of_rect != _old_choose_scroll)
		{
			if (!scroll_error) { scroll.setVolume(MUSIC_VOLUME + music.music_volume); scroll.play(); }
			_old_choose_scroll = number_of_rect;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus())
		{
			if (n_settings_button == 0)
			{
				if (number_of_rect != _old_choose_disk)
				{
					_old_choose_disk = number_of_rect;
					flags.number_of_disks = 3 + number_of_rect;
				}
			}

			else if (n_settings_button == 1)
			{
				if (number_of_rect != _old_choose_3d)
				{
					_old_choose_3d = number_of_rect;

					if (number_of_rect == 1)
					{
						flags.disable_3d = true;
					}
					else { flags.disable_3d = false; }
				}
			}

			else if (n_settings_button == 2)
			{
				if (number_of_rect != _old_choose_music)
				{
					_old_choose_music = number_of_rect;

					if (number_of_rect == 1)
					{
						music.disable_music = true;
						if (music.music.Playing)
							music.music.stop();
					}

					else
					{
						music.disable_music = false;
						if (music.music.Paused)
							music.music.play();
					}
				}
			}
		}
	}

	else
	{
		rect.setScale(sf::Vector2f(1.0f, 1.0f));

		if (number_of_rect != _old_choose_disk && n_settings_button == 0)
			rect.setOutlineThickness(0);
		else if (number_of_rect != _old_choose_3d && n_settings_button == 1)
			rect.setOutlineThickness(0);
		else if (number_of_rect != _old_choose_music && n_settings_button == 2)
			rect.setOutlineThickness(0);
	}
}

int16_t Settings::actions(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	// Нажатие левой кнопки для звуков
	if (event.type == sf::Event::EventType::MouseButtonPressed)
		if (event.mouseButton.button == sf::Mouse::Left && window.hasFocus())
			if (!click_error) { click.play(); }
	// Нажатие Esc для звуков
	if (event.type == sf::Event::EventType::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape && window.hasFocus())
			if (!click_error) { click.play(); flags.go_to_menu = true; flags.go_to_settings = false; }
	if (event.type == sf::Event::EventType::KeyPressed)
		if (event.key.code == sf::Keyboard::M && window.hasFocus())
		{
			if (!music.mute)
			{
				music._buf_music_volume = music.music_volume;
				music.music_volume = -MUSIC_VOLUME;
				music.mute = true;
			}

			else
			{
				music.music_volume = music._buf_music_volume;
				music.mute = false;
			}

			if (!music.music_error) { music.music.setVolume(MUSIC_VOLUME + music.music_volume); }
			if (!click_error) { click.setVolume(MUSIC_VOLUME + music.music_volume); }
			if (!scroll_error) { scroll.setVolume(MUSIC_VOLUME + music.music_volume); }
		}

	// Громкость музыки
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (!music.mute)
		{
			if (event.mouseWheelScroll.delta >= 1.0f)
				music.music_volume += (music.music_volume < (100.0f - MUSIC_VOLUME)) ? 5.0f : (-5.0f);
			else if (event.mouseWheelScroll.delta <= -1.0f)
				music.music_volume -= (music.music_volume > (0.0f - MUSIC_VOLUME)) ? 5.0f : (-5.0f);

			if (!music.music_error) { music.music.setVolume(MUSIC_VOLUME + music.music_volume); }
			if (!click_error) { click.setVolume(MUSIC_VOLUME + music.music_volume); }
			if (!scroll_error) { scroll.setVolume(MUSIC_VOLUME + music.music_volume); }
		}
	}

	return 0;
}