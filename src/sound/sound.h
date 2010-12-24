/**
 * 	@file sound.h
 * 	@brief Header de la classe Sound
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _SOUND_
#define _SOUND_

#include <string>

class Sound_manager;

class Sound {
protected:
	std::string m_sound;
public:
	Sound(std::string str);
	~Sound();
};


#endif
