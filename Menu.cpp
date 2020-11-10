#include "Menu.h"

Menu::Menu()
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Towers of Hanoi", sf::Style::Titlebar);
	window.setFramerateLimit(60);

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
}

int16_t Menu::menu()
{
	float l, k;
	bool m = false;

	l = k = 0.0f;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		if (!texture_error)
		{
			window.draw(sprite);
			sprite.move(sf::Vector2f(l, k));
		}

		if (m == 0)
		{
			l += 0.01f;
			k += 0.01f;

			if (l >= 0.2f) { m = 1; }
		}

		else if (m == 1)
		{
			l -= 0.01f;
			k -= 0.01f;

			if (l <= -0.2f) { m = 0; }
		}

		window.display();
	}

	return 0;
}
