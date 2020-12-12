#include "Window.h"

Window::Window()
{
	// Подключение изображения для фона
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
		sprite.setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	}

	// Подключение шрифта
	font_error = false;
	if (!font.loadFromFile("recources/fonts/comic.ttf"))
	{
		std::wcout << L"\nFont error!" << std::endl;
		font_error = true;
	}

	if (!font_error)
	{
		text.setFont(font);
	}
}
