/**
 * 	@file sound.h
 * 	@brief Implémentation de la classe Sound
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
//~  
#include <iostream>
#include "sound.h"
#include "../sound/sound_manager.h"

Sound::Sound(std::string str) 
{
	m_sound = str;
}

Sound::~Sound()
{
	
}
