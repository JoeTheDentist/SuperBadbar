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
#include "Sound.h"

Sound::Sound(std::string str) 
{
	m_sound = str;
}

Sound::~Sound()
{
	
}

std::string Sound::get_string()
{
	return m_sound;
}
