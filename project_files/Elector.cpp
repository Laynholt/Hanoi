#include "Elector.h"

void Elector::set_window(Window* win)
{
	if (_win != win)
	{
		_new = true;
		_win = win;
	}
}

void Elector::show(sf::RenderWindow& window, Music& music, Flags_for_game& flags)
{
	if (_new)
	{
		_new = false;
		_win->create(window, music, flags);
	}

	_win->update(window, music, flags);
}
