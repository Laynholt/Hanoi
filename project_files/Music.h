#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "Library.h"

#define MUSIC_VOLUME 50.0f

class Music
{
public:
	Music();

public:
	sf::Music music;
	bool music_error;

	bool disable_music;

	bool mute;
	float music_volume;
	float _buf_music_volume;

};
#endif // !_MUSIC_H_
