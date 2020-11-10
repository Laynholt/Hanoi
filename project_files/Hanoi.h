#ifndef _HANOI_H_
#define _HANOI_H_

#include "Menu.h"


class Hanoi : public Menu
{
private:
	bool back_to_menu;


public:
	Hanoi();

	void Loop();
};

#endif // !_HANOI_H_

