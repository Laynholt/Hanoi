#include "Menu.h"

Menu::Menu(Music& music)
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

	rect.resize(3);
}

void Menu::create(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	flags.go_to_game = flags.go_to_settings = false;

	rect.clear();
	col.clear();
	titles.clear();

	col.push_back(sf::Color(255, 137, 39, 255));
	col.push_back(sf::Color(0, 162, 232, 255));
	col.push_back(sf::Color(255, 174, 231, 255));

	for (int16_t i = 0; i < 3; i++)
	{
		// Поплашки
		rect[i].setFillColor(col[i]);
		rect[i].setSize(sf::Vector2f(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 6));
		rect[i].setPosition(sf::Vector2f(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4 + (SCREEN_HEIGHT / 6 + 10) * i));
	}


	titles.push_back(L"Играть");
	titles.push_back(L"Настройки");
	titles.push_back(L"Выйти");

	if (!flags.from_settings)
	{
		if (music.music.Playing)
		{
			music.music.pause();
		}

		if (!music.music.openFromFile("recources/music/Space-Music-Astro.ogg"))
		{
			std::wcout << "\nMusic error!" << std::endl;
			music.music_error = true;
		}

		if (!music.music_error && !music.disable_music)
		{
			music.music.play();
			music.music.setLoop(true);
			music.music.setVolume(MUSIC_VOLUME + music.music_volume);
		}
	}
	flags.from_settings = false;

	if (!click_error) { click.setBuffer(click_buffer); click.setVolume(MUSIC_VOLUME + music.music_volume); }
	if (!scroll_error) { scroll.setBuffer(scroll_buffer); scroll.setVolume(MUSIC_VOLUME + music.music_volume); }
}

void Menu::update(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	std::wstring str;

	float l, k;
	bool m = false;
	l = k = 0.0f;

	
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		actions(window, music, flags);

		// Экшенс
		for (int16_t i = 0; i < 3; i++)
		{
			activate_button(i, window, music, flags);
		}
	}

	window.clear();

	// Отображение фона
	if (!texture_error)
	{
		window.draw(sprite);
		sprite.move(sf::Vector2f(l, k));
	}
	// Сдвиг фона вправо вниз
	if (m == 0)
	{
		l += 0.01f;
		k += 0.01f;

		if (l >= 0.2f) { m = 1; }
	}
	// Сдвиг фона влево вверх
	else if (m == 1)
	{
		l -= 0.01f;
		k -= 0.01f;

		if (l <= -0.2f) { m = 0; }
	}

	// Отображение пунктов меню
	for (int16_t i = 0; i < 3; i++)
	{
		window.draw(rect[i]);

		// Текст
		if (!font_error)
		{
			text.setString(titles[i]);
			text.setCharacterSize(60);
			text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - text.getCharacterSize() * titles[i].length() / 4 - i * 10,
				SCREEN_HEIGHT / 4 + (SCREEN_HEIGHT / 6 + 10) * i + 10));
			text.setStyle(sf::Text::Bold);
			window.draw(text);
		}
	}

	if (!font_error)
	{
		text.setString(L"Громкость: " + std::to_wstring((int16_t)MUSIC_VOLUME + (int16_t)music.music_volume));
		text.setCharacterSize(20);
		text.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 40));
		window.draw(text);


		autor.setCharacterSize(20);
		str = L"ver. ~release 1.2";
		autor.setString(str);
		autor.setPosition(sf::Vector2f(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 70));
		window.draw(autor);

		str = L"Created by Laynholt |> 2020";
		autor.setString(str);
		autor.setPosition(sf::Vector2f(SCREEN_WIDTH - 320, SCREEN_HEIGHT - 40));
		window.draw(autor);
	}
}


void Menu::activate_button(int16_t i, sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	sf::Vector2i mouse;

	mouse = sf::Mouse::getPosition(window);

	if (mouse.x >= rect[i].getPosition().x && mouse.x <= (rect[i].getPosition().x + rect[i].getSize().x) &&
		mouse.y >= rect[i].getPosition().y && mouse.y <= (rect[i].getPosition().y + rect[i].getSize().y))
	{
		rect[i].setScale(sf::Vector2f(1.1f, 1.0f));

		if (i != _old_choose_scroll)
		{
			if (!scroll_error) { scroll.setVolume(MUSIC_VOLUME + music.music_volume); scroll.play(); }
			_old_choose_scroll = i;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus())
		{
			if (i == 0)
			{
				flags.go_to_game = true;
				flags.go_to_menu = false;
			}
			else if (i == 1)
			{
				flags.go_to_settings = true;
				flags.go_to_menu = false;
			}
			else if (i == 2)
				window.close();
		}
	}

	else
	{
		rect[i].setScale(sf::Vector2f(1.0f, 1.0f));
	}
}

int16_t Menu::actions(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	// Нажатие левой кнопки для звуков
	if (event.type == sf::Event::EventType::MouseButtonPressed)
		if (event.mouseButton.button == sf::Mouse::Left && window.hasFocus())
			if (!click_error) { click.play(); }
	// Нажатие Esc для звуков
	if (event.type == sf::Event::EventType::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape && window.hasFocus())
			if (!click_error) { click.play(); }
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
