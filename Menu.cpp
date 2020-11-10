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
					go_to_game = true;
				else if (number_of_rect == 1)
					settings();
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

void Menu::settings()
{
	bool go_to_menu = false;
	_old_choose_scroll = -1;

	sf::RectangleShape rect_count_disks;
	std::vector<sf::RectangleShape> rect_nums_disks(4);
	sf::RectangleShape rect_3d;
	sf::RectangleShape rect_music;
	std::vector <sf::RectangleShape> rect_on_off_3d(2);
	std::vector <sf::RectangleShape> rect_on_off_music(2);

	std::vector<sf::Color> col;

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

	std::wstring str;

	while (window.isOpen() && !go_to_menu)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::EventType::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left && window.hasFocus())
					if (!click_error) { click.play(); }

			if (event.type == sf::Event::EventType::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape && window.hasFocus())
					if (!click_error) { click.play(); go_to_menu = true; }
		}

		window.clear();

		window.draw(sprite);

		// Рисуем прямоугольник Количества дисков и надпись
		window.draw(rect_count_disks);
		if (!font_error)
		{
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

		window.display();
	}
}
