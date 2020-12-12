#ifndef _GAME_H_
#define _GAME_H_

#include "Menu.h"
#include "Hanoi.h"
#include "Settings.h"

#include "Music.h"
#include "Elector.h"

class Game
{
public:
	Game();

	void loop();

private:
	sf::RenderWindow window;
};
#endif // !_GAME_H_
