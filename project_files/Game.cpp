#include "Game.h"

Game::Game()
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Towers of Hanoi", sf::Style::Titlebar);
	window.setFramerateLimit(60);
}

void Game::loop()
{
	Music music;
	Flags_for_game flags;

	Menu *menu = new Menu(music);
	Hanoi *hanoi = new Hanoi(music, flags);
	Settings *settings = new Settings(music);

	Elector* elector = new Elector(menu);

	while (window.isOpen())
	{
		if (flags.go_to_menu)
		{
			elector->set_window(menu);
		}

		else if (flags.go_to_game)
		{
			elector->set_window(hanoi);
		}

		else if (flags.go_to_settings)
		{
			elector->set_window(settings);
		}		

		elector->show(window, music, flags);
		window.display();
	}

	delete elector;
	delete menu;
	delete hanoi;
	delete settings;
}
