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
#ifdef ACTIVE_FMOD
:
	m_music(NULL),
	m_sounds_volume(99),
	m_music_volume(99)
#endif
{
#ifdef ACTIVE_FMOD
	PRINT_CONSTR(1, "Construction du SoundEngine")
	FSOUND_Init(44100, 32, 0);
//~ 	m_fire = new FSOUND_SAMPLE*[SHOTGUN + 1];
	FSOUND_SetPan(BABAR_FIRE_CANAL, 5);
	FSOUND_SetVolume(BABAR_FIRE_CANAL, 5);
#endif
}

SoundEngine::~SoundEngine()
{
#ifdef ACTIVE_FMOD
	PRINT_CONSTR(1, "Destruction du SoundEngine")
	FSOUND_Close();
#endif
}

void SoundEngine::init_level(std::string level)
{
	Analyser analyser;
	analyser.open(LEVELS_R + level);
	analyser.find_string("#Music#");
	load_music(analyser.read_string());
	analyser.close();
}

void SoundEngine::load_music(std::string str)
{
	#ifdef ACTIVE_FMOD
	if (m_music) {
		FSOUND_Stream_Stop (m_music);
		FSOUND_Stream_Close(m_music);
		FSOUND_StopSound(MUSIC_CANAL);
	}
	m_music = FSOUND_Stream_Open((MUSIC_R + str).c_str(), 0, 0, 0);
	#endif
}

void SoundEngine::play_music()
{
	#ifdef ACTIVE_FMOD
	FSOUND_Stream_Play(MUSIC_CANAL, m_music);
	FSOUND_SetVolume(MUSIC_CANAL, (255.0 * (double)m_music_volume / 100.0));
	#endif
}

void SoundEngine::play_sound(std::string key)
{
	#ifdef ACTIVE_FMOD
	PRINT_TRACE(1, "jeu du son %s", key.c_str())
	std::map<std::string, FSOUND_SAMPLE*>::iterator it = m_sound_samples.find(key);
	FSOUND_SAMPLE *to_play = NULL;
	if (it == m_sound_samples.end()) {
		to_play = FSOUND_Sample_Load(FSOUND_FREE, key.c_str(), 0, 0, 0);
		if (to_play == NULL) {
			PRINT_DEBUG(1, "impossible de charger le son %s", key.c_str());
			return;
		}
		m_sound_samples.insert(std::pair<std::string, FSOUND_SAMPLE*>(key, to_play));
	} else {
		to_play = (*it).second;
	}
	PRINT_TRACE(3, "JEU DU SON %s",key.c_str());
	int channel = FSOUND_PlaySound(FSOUND_FREE, to_play);
	FSOUND_SetVolume(channel, m_sounds_volume);
#endif
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
	#ifdef ACTIVE_FMOD
	m_sounds_volume = v;
	FSOUND_SetVolume(FSOUND_ALL, (255.0 * (double)m_sounds_volume / 100.0));
	FSOUND_SetVolume(MUSIC_CANAL, (255.0 * (double)m_music_volume / 100.0));
	#endif
}

void SoundEngine::set_music_volume(int v)
{
	#ifdef ACTIVE_FMOD
	m_music_volume = v;
	FSOUND_SetVolume(MUSIC_CANAL, (255.0 * (double)m_music_volume / 100.0));
	#endif
}

int SoundEngine::get_sounds_volume() const
{
	#ifdef ACTIVE_FMOD
	return m_sounds_volume;
	#else
	return 0;
	#endif
}

int SoundEngine::get_music_volume() const
{
	#ifdef ACTIVE_FMOD
	return m_music_volume;
	#else
	return 0;
	#endif
}


