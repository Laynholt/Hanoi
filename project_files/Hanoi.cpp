#include "Hanoi.h"

Hanoi::Hanoi()
{
	back_to_menu = false;
}

void Hanoi::Loop()
{

	// Выводим меню
	menu();

	while (window.isOpen())
	{

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

		if (!texture_error) window.draw(sprite);

		window.display();
	}
}
