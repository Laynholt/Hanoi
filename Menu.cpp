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


	float l, k;
	bool m = false;
	l = k = 0.0f;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

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
	}

	else
	{
		rect.setScale(sf::Vector2f(1.0f, 1.0f));
	}
}
