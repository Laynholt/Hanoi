#include "Hanoi.h"

Hanoi::Hanoi(Music& music, Flags_for_game& flags)
{
	pin = 0;
	count = 0;
	best_count = 0;
	count_built_tower = 0;
	started_tower = pin;

	vertical_x = _radius = 0.0f;

	flags.number_of_disks = 3;
	FOR_3D = (flags.disable_3d == false) ? 10 : 1;
	horisontal_width = vertical_height = 0.0f;

	sound_error = false;
	if (!sound_buffer1.loadFromFile("recources/sounds/wrong.ogg"))
	{
		std::wcout << L"\nSound wrong error!" << std::endl;
		sound_error = true;
	}

	else 
	{ 
		wrong_sound.setBuffer(sound_buffer1); 
		wrong_sound.setVolume(MUSIC_VOLUME + music.music_volume);
	}

	disk_sound_error = false;
	if (!sound_buffer2.loadFromFile("recources/sounds/disks.ogg"))
	{
		std::wcout << L"\nSound disks error!" << std::endl;
		disk_sound_error = true;
	}

	else 
	{
		disk_sound.setBuffer(sound_buffer2); 
		disk_sound.setVolume(MUSIC_VOLUME + music.music_volume);
	}

	congrats_error = false;
	if (!sound_buffer3.loadFromFile("recources/sounds/congrats.ogg"))
	{
		std::wcout << L"\nSound congrats error!" << std::endl;
		congrats_error = true;
	}

	else 
	{ 
		congrats_sound.setBuffer(sound_buffer3); 
		congrats_sound.setVolume(MUSIC_VOLUME + music.music_volume);
	}
}

void Hanoi::create(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	flags.go_to_menu = flags.go_to_settings = false;

	rect_for_text.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 12));
	rect_for_text.setFillColor(sf::Color(22, 22, 22, 255));
	rect_for_text.setOutlineThickness(3);
	rect_for_text.setOutlineColor(sf::Color::White);

	stacks.resize(3);
	vertical.resize(3);
	full_heights.resize(3);

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

	_radius = ((SCREEN_HEIGHT > SCREEN_WIDTH) ? SCREEN_WIDTH : SCREEN_HEIGHT) * 0.05f;
	vertical_x = SCREEN_WIDTH * 0.1f + horisontal_width / 6;

	triangle.setRadius(_radius);
	triangle.setPointCount(3);
	triangle.setFillColor(sf::Color(222, 16, 94, 200));
	triangle.setPosition((pin * horisontal_width / 3) + vertical_x - _radius + vertical[0].getSize().x / 2, SCREEN_HEIGHT * 0.85f); // 0.81f

	restart(window, music, flags);
}

void Hanoi::update(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	int16_t a = 0;
	vertical_x = SCREEN_WIDTH * 0.1f + horisontal_width / 6;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		// Громкость музыки и звуков
		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (!music.mute)
			{
				if (event.mouseWheelScroll.delta >= 1.0f)
					music.music_volume += (music.music_volume < (100.0f - MUSIC_VOLUME)) ? 5.0f : (-5.0f);
				else if (event.mouseWheelScroll.delta <= -1.0f)
					music.music_volume -= (music.music_volume > (0.0f - MUSIC_VOLUME)) ? 5.0f : (-5.0f);

				if (!music.music_error) { music.music.setVolume(MUSIC_VOLUME + music.music_volume); }
				if (!sound_error) { wrong_sound.setVolume(MUSIC_VOLUME + music.music_volume); }
				if (!disk_sound_error) { disk_sound.setVolume(MUSIC_VOLUME + music.music_volume); }
				if (!congrats_error) { congrats_sound.setVolume(MUSIC_VOLUME + music.music_volume); }
				a = -1;
			}
		}

		// Действия
		if (event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::KeyPressed)
		{
			a = actions(window, music, flags);
		}
	}

	// Подсчёт количества собранных башен
	counting_built_towers(music, flags);

	if (a == 0)
	{
		window.clear();


		// Фон
		if (!texture_error) window.draw(sprite);


		// Текст
		window.draw(rect_for_text);
		if (!font_error)
		{
			std::wstring wstr = L"Башенек собранно: " + std::to_wstring(count_built_tower) +
				L"\tКоличество ходов: " + std::to_wstring(count) + L"\tРекорд по сбору (ходы): " + std::to_wstring(best_count);
			text.setString(wstr);
			text.setCharacterSize(30);
			text.setPosition(sf::Vector2f(70, 0));
			window.draw(text);

			text.setString(L"Громкость: " + std::to_wstring((int16_t)MUSIC_VOLUME + (int16_t)music.music_volume));
			text.setCharacterSize(20);
			text.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 40));
			window.draw(text);
		}

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
		draw_tower(window);
	}
}

int16_t Hanoi::actions(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	if (window.hasFocus())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) 
		{ 
			pin = 0; 
			vertical_x = SCREEN_WIDTH * 0.1f + horisontal_width / 6;
			triangle.setPosition((pin * horisontal_width / 3) + vertical_x - _radius + vertical[0].getSize().x / 2, SCREEN_HEIGHT * 0.85f);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) 
		{
			pin = 1;
			vertical_x = SCREEN_WIDTH * 0.1f + horisontal_width / 6;
			triangle.setPosition((pin * horisontal_width / 3) + vertical_x - _radius + vertical[0].getSize().x / 2, SCREEN_HEIGHT * 0.85f);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) 
		{
			pin = 2;
			vertical_x = SCREEN_WIDTH * 0.1f + horisontal_width / 6;
			triangle.setPosition((pin * horisontal_width / 3) + vertical_x - _radius + vertical[0].getSize().x / 2, SCREEN_HEIGHT * 0.85f);
		}


		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (pin == 2) { if (!move_disk(2, 1, 1)) { count++; if (!disk_sound_error) { disk_sound.play(); } return 0; } }
			else if (pin == 1) { if (!move_disk(1, 0, 0)) { count++; if (!disk_sound_error) { disk_sound.play(); } return 0; } }

			if (!sound_error) { wrong_sound.play(); }
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (pin == 0) { if (!move_disk(0, 1, 1)) { count++; if (!disk_sound_error) { disk_sound.play(); } return 0; } }
			else if (pin == 1) { if (!move_disk(1, 2, 2)) { count++; if (!disk_sound_error) { disk_sound.play(); } return 0; } }

			if (!sound_error) { wrong_sound.play(); }
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			if (pin == 0) { if (!move_disk(0, 2, 2)) { count++; if (!disk_sound_error) { disk_sound.play(); } return 0; } }
			else if (pin == 2) { if (!move_disk(2, 0, 0)) { count++; if (!disk_sound_error) { disk_sound.play(); } return 0; } }

			if (!sound_error) { wrong_sound.play(); }
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
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
			if (!sound_error) { wrong_sound.setVolume(MUSIC_VOLUME + music.music_volume); }
			if (!disk_sound_error) { disk_sound.setVolume(MUSIC_VOLUME + music.music_volume); }
			if (!congrats_error) { congrats_sound.setVolume(MUSIC_VOLUME + music.music_volume); }
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { flags.go_to_menu = true; flags.go_to_game = false; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			restart(window, music, flags);
		}

		else
		{
			return 1;
		}
	}

	return 0;
}

void Hanoi::restart(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	disks.resize(flags.number_of_disks);

	FOR_3D = (flags.disable_3d == false) ? 10 : 1;

	pin = 0;
	count = 0;
	best_count = 0;
	started_tower = pin;
	count_built_tower = 0;

	// Музыка
	if (!music.music.openFromFile("recources/music/Space-Music-Pulsar.ogg"))
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

	// Текст
	if (!font_error)
	{
		std::wstring wstr = L"Башенек собранно: " + std::to_wstring(count_built_tower) +
			L"\tКоличество ходов: " + std::to_wstring(count) + L"\tРекорд по сбору (ходы): " + std::to_wstring(best_count);
		text.setString(wstr);
		text.setPosition(sf::Vector2f(70, 0));
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Bold);
		window.draw(text);

		text.setString(L"Громкость: " + std::to_wstring((int16_t)MUSIC_VOLUME + (int16_t)music.music_volume));
		text.setCharacterSize(20);
		text.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 40));
		window.draw(text);
	}

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

	for (uint16_t i = 0; i < flags.number_of_disks; i++, scale -= SCALE_STEP)
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

void Hanoi::draw_tower(sf::RenderWindow& window)
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

void Hanoi::counting_built_towers(Music& music, Flags_for_game& flags)
{
	for (int16_t i = 0; i < 3; i++)
	{
		if ((stacks[i].size() / FOR_3D) == flags.number_of_disks && i != started_tower)
		{
			started_tower = i;
			count_built_tower++;

			if (best_count == 0 || best_count > count)
				best_count = count;

			if (!congrats_error) { congrats_sound.setVolume(MUSIC_VOLUME + music.music_volume); congrats_sound.play(); }

			count = 0;

			break;
		}
	}
}
