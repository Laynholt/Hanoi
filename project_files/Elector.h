#ifndef _ELECTOR_H_
#define _ELECTOR_H_

#include "Window.h"

class Elector
{
private:
	bool _new;
	Window* _win;

public:
	Elector(Window* win = nullptr) : _new(true), _win(win) {}

	void set_window(Window* win);
	void show(sf::RenderWindow& window, Music& music, Flags_for_game& flags);

};
#endif // !_ELECTOR_H_