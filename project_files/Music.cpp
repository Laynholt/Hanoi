#include "Music.h"

Music::Music()
{
	// Подключаем музыку
	music_error = false;
	disable_music = false;
	music_volume = 0.0f;
	if (!music.openFromFile("recources/music/Space-Music-Astro.ogg"))
	{
		std::wcout << L"\nMusic error!" << std::endl;
		music_error = true;
	}

	disable_music = false;

	mute = false;
	music_volume = 0.0f;
	_buf_music_volume = 0.0f;
}
