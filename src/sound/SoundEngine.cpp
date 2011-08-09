/**
 * 	@file SoundEngine.cpp
 * 	@brief Implementation de la classe SoundEngine
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include "util/Analyser.h"
#include "util/repertories.h"
#include "SoundEngine.h"
#include "sound/SoundEngine.h"
#include "sound/Sound.h"
#include "sound/Sonorisable.h"
#include "util/debug.h"
#include "util/globals.h"


SoundEngine::SoundEngine()
:
//~ 	m_music(NULL),
	m_sounds_volume(99),
	m_music_volume(99)

{
	PRINT_CONSTR(1, "Construction du SoundEngine")
}

SoundEngine::~SoundEngine()
{
	for (std::map<std::string, sf::SoundBuffer*>::iterator it = m_soundBuffers.begin(); 
			it != m_soundBuffers.end(); ++it) {
		delete (*it).second;
	}
	for (std::list<sf::Sound *>::iterator it = m_soundsPlaying.begin(); 
			it != m_soundsPlaying.end(); ++it) {
		delete *it;
	}
	PRINT_CONSTR(1, "Destruction du SoundEngine")
	
}

void SoundEngine::init_level(std::string level)
{
	Analyser analyser;
	analyser.open(LEVELS_R + level);
	analyser.find_string("#Music#");
	load_music(analyser.read_string());
	analyser.close();
}

void SoundEngine::update()
{
	for (std::list<sf::Sound *>::iterator it = m_soundsPlaying.begin(); 
			it != m_soundsPlaying.end(); ) {
		if ((*it)->GetStatus() == sf::Sound::Stopped) {
			delete (*it);
			it = m_soundsPlaying.erase(it);
			PRINT_DEBUG(1, "DESTRUUUUUUUUUCTION");
		} else {
			++it;
		}
	}	
}


void SoundEngine::load_music(std::string str)
{
//~ 	if (m_music) {
//~ 		FSOUND_Stream_Stop (m_music);
//~ 		FSOUND_Stream_Close(m_music);
//~ 		FSOUND_StopSound(MUSIC_CANAL);
//~ 	}
//~ 	m_music = FSOUND_Stream_Open((MUSIC_R + str).c_str(), 0, 0, 0);
}

void SoundEngine::play_music()
{
//~ 	FSOUND_Stream_Play(MUSIC_CANAL, m_music);
//~ 	FSOUND_SetVolume(MUSIC_CANAL, (255.0 * (double)m_music_volume / 100.0));
}

void SoundEngine::play_sound(std::string key)
{
	PRINT_TRACE(2, "jeu du son %s", key.c_str())
	std::map<std::string, sf::SoundBuffer*>::iterator it = m_soundBuffers.find(key);
	sf::SoundBuffer *to_play = NULL;
	if (it == m_soundBuffers.end()) {
		to_play = new sf::SoundBuffer;
		if (!to_play->LoadFromFile(key.c_str())) {
			PRINT_DEBUG(1, "impossible de charger le son %s", key.c_str());
			delete to_play;
			return;
		}
		m_soundBuffers.insert(std::pair<std::string, sf::SoundBuffer*>(key, to_play));
	} else {
		to_play = (*it).second;
	}
	sf::Sound *sound = new sf::Sound;
	sound->SetBuffer(*to_play);
	sound->Play();
	m_soundsPlaying.push_back(sound);
}

void SoundEngine::play_sound(Sonorisable *sonorisable)
{
	while (!sonorisable->no_more_sounds()) {
		play_sound(sonorisable->get_next_sound());
		sonorisable->pop_sound();
	}
}

void SoundEngine::set_sounds_volume(int v)
{
	m_sounds_volume = v;
}

void SoundEngine::set_music_volume(int v)
{
	m_music_volume = v;
}

int SoundEngine::get_sounds_volume() const
{
	return m_sounds_volume;
}

int SoundEngine::get_music_volume() const
{
	return m_music_volume;
}

