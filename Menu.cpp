#include "Menu.h"

Menu::Menu()
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Towers of Hanoi", sf::Style::Titlebar);
	window.setFramerateLimit(60);

	// Подключение изображения для фона
	texture_error = false;
	if (!texture.loadFromFile("recources/textures/Mystars.png"))
	{
		std::wcout << L"\nTexture error!" << std::endl;
		texture_error = true;
	}

	if (!texture_error)
	{
		texture.setRepeated(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
	}

	// Подключение шрифта
	font_error = false;
	if (!font.loadFromFile("recources/fonts/comic.ttf"))
	{
		std::wcout << L"\nFont error!" << std::endl;
		font_error = true;
	}

	if (!font_error)
	{
		text.setFont(font);
	}

	// Подключаем музыку
	music_error = false;
	disable_music = false;
	if (!music.openFromFile("recources/music/Space-Music-Astro.ogg"))
	{
		std::wcout << L"\nMusic error!" << std::endl;
		music_error = true;
	}

	// Подключаем звук клика
	click_error = false;
	if (!click_buffer.loadFromFile("recources/sounds/click1.ogg"))
	{
		std::wcout << L"\nSound click error!" << std::endl;
		click_error = true;
	}

	// Подключаем звук скролла
	scroll_error = false;
	if (!scroll_buffer.loadFromFile("recources/sounds/scroll2.ogg"))
	{
		std::wcout << L"\nSound scroll error!" << std::endl;
		scroll_error = true;
	}

	number_of_disks = 0;
	go_to_game = false;

	_old_choose_scroll = -1;
	_old_choose_disk = _old_choose_3d = _old_choose_music = 0;
}

int16_t Menu::menu()
{
	std::vector<sf::RectangleShape> rect(3);
	std::vector<sf::Color> col;
	std::vector<std::wstring> titles;

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


	std::wstring str;

	if (!music.openFromFile("recources/music/Space-Music-Astro.ogg"))
	{
		std::wcout << "\nMusic error!" << std::endl;
		music_error = true;
	}

	if (!music_error && !disable_music)
	{
		music.play();
		music.setLoop(true);
		music.setVolume(50.0f);
	}

	if (!click_error) { click.setBuffer(click_buffer); }
	if (!scroll_error) { scroll.setBuffer(scroll_buffer); }

	float l, k;
	bool m = false;
	l = k = 0.0f;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Нажатие левой кнопки для звуков
			if (event.type == sf::Event::EventType::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left && window.hasFocus())
					if (!click_error) { click.play(); }
			// Нажатие Esc для звуков
			if (event.type == sf::Event::EventType::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape && window.hasFocus())
					if (!click_error) { click.play(); }

			// Экшенс
			for (int16_t i = 0; i < 3; i++)
			{
				activate_button(rect[i], i, false, 0);
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

		window.display();
	}

	if (music.Playing)
	{
		music.pause();
	}

	return 0;
}

void Menu::activate_button(sf::RectangleShape& rect, int16_t number_of_rect, bool is_settings, int16_t n_settings_button)
{
	sf::Vector2i mouse;

	mouse = sf::Mouse::getPosition(window);

	if (mouse.x >= rect.getPosition().x && mouse.x <= (rect.getPosition().x + rect.getSize().x) &&
		mouse.y >= rect.getPosition().y && mouse.y <= (rect.getPosition().y + rect.getSize().y))
	{
		if (!is_settings) { rect.setScale(sf::Vector2f(1.1f, 1.0f)); }
		else { rect.setScale(sf::Vector2f(1.0f, 1.1f)); }

		if (number_of_rect != _old_choose_scroll)
		{
			if (!scroll_error) { scroll.setVolume(50); scroll.play(); }
			_old_choose_scroll = number_of_rect;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus())
		{
			if (!is_settings)
			{
				if (number_of_rect == 0)
					;//go_to_game = true;
				else if (number_of_rect == 1)
					;//settings();
				else if (number_of_rect == 2)
					window.close();
			}
		}
	}

	else
	{
		rect.setScale(sf::Vector2f(1.0f, 1.0f));
	}
}
