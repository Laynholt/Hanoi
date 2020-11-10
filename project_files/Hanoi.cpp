#include "Hanoi.h"

Hanoi::Hanoi()
{
	pin = 0;

	back_to_menu = false;

	FOR_3D = (disable_3d == false) ? 10 : 1;
	horisontal_width = vertical_height = 0.0f;
}

void Hanoi::Loop()
{

	// Выводим меню
	menu();

	vertical.resize(3);

	// Стержни
	float vertical_x;

	horisontal_width = SCREEN_WIDTH * 0.8f;
	vertical_height = SCREEN_HEIGHT * 0.4f;
	vertical_x = SCREEN_WIDTH * 0.1f + horisontal_width / 6;

	horisontal.setSize(sf::Vector2f(horisontal_width, 5.0f));

	for (uint16_t i = 0; i < 3; i++)
	{
		vertical[i].setSize(sf::Vector2f(5.0f, vertical_height));
		vertical[i].setPosition(sf::Vector2f(vertical_x, SCREEN_HEIGHT * 0.4f));
		vertical_x += horisontal_width / 3;
	}

	// Указатель
	float _radius = ((SCREEN_HEIGHT > SCREEN_WIDTH) ? SCREEN_WIDTH : SCREEN_HEIGHT) * 0.05f;
	vertical_x = SCREEN_WIDTH * 0.1f + horisontal_width / 6;

	triangle.setRadius(_radius);
	triangle.setPointCount(3);
	triangle.setFillColor(sf::Color(222, 16, 94, 200));
	triangle.setPosition((pin * horisontal_width / 3) + vertical_x - _radius + vertical[0].getSize().x / 2, SCREEN_HEIGHT * 0.85f); // 0.81f

	while (window.isOpen())
	{
		vertical_x = SCREEN_WIDTH * 0.1f + horisontal_width / 6;

		// Возврат в меню
		if (back_to_menu)
		{
			menu();
			back_to_menu = false;
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// Фон
		if (!texture_error) window.draw(sprite);

		// Горизонт и указатель
		for (int16_t j = (FOR_3D > 1) ? -FOR_3D : 0; j < FOR_3D; j++)
		{
			horisontal.setPosition(sf::Vector2f(SCREEN_WIDTH * 0.1f + j, SCREEN_HEIGHT * 0.8f - j));
			window.draw(horisontal);
		}
		window.draw(triangle);

		// Вертикальные столбцы
		for (uint16_t i = 0; i < 3; i++)
		{
			for (int16_t j = 0; j < FOR_3D; j++)
			{
				window.draw(vertical[i]);
				vertical[i].setPosition(sf::Vector2f(vertical_x + j, SCREEN_HEIGHT * 0.4f - j));
			}
			vertical[i].setPosition(sf::Vector2f(vertical_x, SCREEN_HEIGHT * 0.4f));
			vertical_x += horisontal_width / 3;
		}

		window.display();
	}
}
