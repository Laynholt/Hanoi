#include "Hanoi.h"

Hanoi::Hanoi()
{
	pin = 0;

	back_to_menu = false;

	number_of_disks = 3;
	FOR_3D = (disable_3d == false) ? 10 : 1;
	horisontal_width = vertical_height = 0.0f;
}

void Hanoi::Loop()
{

	// Выводим меню
	menu();

	stacks.resize(3);
	vertical.resize(3);
	full_heights.resize(3);

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

	// Запускаем функцию рестарта
	restart();


	// Луп Игры
	int16_t a = 0;
	bool first = true;			// Для отрисовки в первый раз

	while (window.isOpen())
	{
		vertical_x = SCREEN_WIDTH * 0.1f + horisontal_width / 6;

		// Возврат в меню
		if (back_to_menu)
		{
			menu();
			restart();
			first = true;
			triangle.setPosition((pin * horisontal_width / 3) + vertical_x - _radius + vertical[0].getSize().x / 2, SCREEN_HEIGHT * 0.85f);
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Действия
			if (event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::KeyPressed)
			{
				a = actions();
				if (a == 4) { back_to_menu = true; }
			}
		}


		if (a != 0 || first)
		{
			window.clear();

			first = false;

			if (a == 1 || a == 5) { triangle.setPosition((pin * horisontal_width / 3) + vertical_x - _radius + vertical[0].getSize().x / 2, SCREEN_HEIGHT * 0.85f); }


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

			// Башенка
			draw_tower();

			window.display();
		}
	}
}

int16_t Hanoi::actions()
{
	if (window.hasFocus())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { pin = 0; return 1; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { pin = 1; return 1; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { pin = 2; return 1; }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (pin == 2) { move_disk(2, 1, 1); return 2; }
			else if (pin == 1) { move_disk(1, 0, 0); return 2; }

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (pin == 0) { move_disk(0, 1, 1); return 2; }
			else if (pin == 1) { move_disk(1, 2, 2); return 2; }
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			if (pin == 0) { move_disk(0, 2, 2); return 2; }
			else if (pin == 2) { move_disk(2, 0, 0); return 2; }
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { return 4; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			restart();
			return 5;
		}
	}

	return 0;
}

void Hanoi::restart()
{
	disks.resize(number_of_disks);

	FOR_3D = (disable_3d == false) ? 10 : 1;

	back_to_menu = false;

	// Диски
	float scale = SCALE;
	float disk_width = horisontal_width * 0.27f;
	float disk_height = vertical_height * DISK_HEIGHT_DEP_OF_HEIGHT;

	for (uint16_t i = 0; i < 3; i++)
	{
		while (!stacks[i].empty()) { stacks[i].pop(); }

		full_heights[i] = SCREEN_HEIGHT * 0.8f - disk_height;
	}


	int16_t r, g, b;
	r = g = b = 0;

	srand(time(NULL));

	for (uint16_t i = 0; i < number_of_disks; i++, scale -= SCALE_STEP)
	{
		r = 40 + rand() % 200;
		g = 40 + rand() % 200;
		b = 40 + rand() % 200;

		disks[i].setSize(sf::Vector2f(disk_width, disk_height));
		disks[i].setScale(sf::Vector2f(scale, 1.0f));
		disks[i].setPosition((SCREEN_WIDTH * 0.1f) + (pin * horisontal_width / 3) + (horisontal_width * 0.034f) + (disk_width * (1 - scale) / 2), full_heights[pin]);
		disks[i].setFillColor(sf::Color(r, g, b, 240));
		disks[i].setOutlineThickness(5);
		disks[i].setOutlineColor(sf::Color(r + 15, g + 15, b + 15, 240));

		sf::RectangleShape temp = disks[i];
		for (uint16_t j = 0; j < FOR_3D; j++)
		{
			stacks[pin].push(temp);
			temp.setPosition((SCREEN_WIDTH * 0.1f) + (pin * horisontal_width / 3) + (horisontal_width * 0.034f) + (disk_width * (1 - scale) / 2) + j, full_heights[pin] - j);
		}

		full_heights[pin] -= disk_height;
	}
}

void Hanoi::draw_tower()
{
	std::stack<sf::RectangleShape> s;

	if (window.isOpen())
	{
		for (int16_t i = 0; i < 3; i++)
		{
			s = stacks[i];
			while (!s.empty()) { window.draw(s.top()); s.pop(); }
		}
	}
}

bool Hanoi::move_disk(int8_t from_pin, int8_t to_pin, int16_t new_pin)
{
	if (!stacks[from_pin].empty())
	{
		if (stacks[to_pin].empty() || stacks[from_pin].top().getScale().x < stacks[to_pin].top().getScale().x)
		{
			sf::RectangleShape temp = stacks[from_pin].top();

			float disk_width, scale;
			for (uint16_t j = 0; j < FOR_3D; j++)
			{
				stacks[to_pin].push(temp);

				disk_width = stacks[to_pin].top().getSize().x;
				scale = stacks[to_pin].top().getScale().x;

				stacks[to_pin].top().setPosition((SCREEN_WIDTH * 0.1f) + (new_pin * horisontal_width / 3) + (horisontal_width * 0.034f) + (disk_width * (1 - scale) / 2) + j, full_heights[to_pin] - j);
			}

			full_heights[to_pin] -= stacks[to_pin].top().getSize().y;                           // Считаем полную высоту стека

			full_heights[from_pin] += stacks[to_pin].top().getSize().y;

			for (uint16_t j = 0; j < FOR_3D; j++)
			{
				stacks[from_pin].pop();
			}

			return 0;
		}
	}

	return 1;
}
