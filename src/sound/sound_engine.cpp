/**
 * 	@file sound_engine.cpp
 * 	@brief Implementation de la classe Sound_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include "sound_engine.h"
#include "../sound/sound_engine.h"
#include "../sound/sound.h"
#include "../sound/sonorisable.h"
#include "../util/debug.h"
#include "../util/globals.h"


Sound_engine::Sound_engine():
	m_sounds_volume(99),
	m_music_volume(99)
{

	PRINT_CONSTR(1, "Construction du Sound_engine")
	FMOD_System_Create(&m_system);
	FMOD_System_Init(m_system, 2, FMOD_INIT_NORMAL, NULL);
	FMOD_System_CreateSound(m_system, (RACINE_R+"/sound/music/level1.mp3").c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &m_music);
//~ 	m_music = FSOUND_Stream_Open((RACINE_R+"/sound/music/level1.mp3").c_str(), 0, 0, 0);
	play_music();

//~ 	FSOUND_SetPan(BABAR_FIRE_CANAL, 5);
//~ 	FSOUND_SetVolume(BABAR_FIRE_CANAL, 5);
	
}



Sound_engine::~Sound_engine()
{
	PRINT_CONSTR(1, "Destruction du Sound_engine")
	FMOD_System_Close(m_system);
	FMOD_System_Release(m_system);
}


void Sound_engine::play_music()
{
//~ 	FSOUND_Stream_Play(MUSIC_CANAL, m_music);
	FMOD_System_PlaySound(m_system, FMOD_CHANNEL_FREE, m_music, 0, NULL);
}

void Sound_engine::play_sound(std::string key)
{	
	PRINT_TRACE(1, "jeu du son %s", key.c_str())
	std::map<std::string, FMOD_SOUND*>::iterator it = m_sound_samples.find(key);
	FMOD_SOUND *to_play = NULL;
	if (it == m_sound_samples.end()) {
		FMOD_RESULT test = FMOD_System_CreateSound(m_system, key.c_str(), FMOD_CREATESAMPLE, 0, &to_play);
		if (test != FMOD_OK) {
			PRINT_DEBUG(1, "impossible de charger le son %s", key.c_str());
			return;
		}
		m_sound_samples.insert(std::pair<std::string, FMOD_SOUND*>(key, to_play));
	} else {
		to_play = (*it).second;
	}
	PRINT_TRACE(3, "JEU DU SON %s",key.c_str());
	FMOD_System_PlaySound(m_system, FMOD_CHANNEL_FREE, to_play, 0, NULL);

//~ 	FSOUND_SetVolume(channel, m_sounds_volume);

}


void Sound_engine::play_sound(Sonorisable *sonorisable)
{	
	while (!sonorisable->no_more_sounds()) {
		play_sound(sonorisable->get_next_sound());
		sonorisable->pop_sound();
	}
}

void Sound_engine::set_sounds_volume(int v)
{	
	m_sounds_volume = v;
//~ 	FSOUND_SetVolume(FSOUND_ALL, (255.0 * (double)m_sounds_volume / 100.0));	
//~ 	FSOUND_SetVolume(MUSIC_CANAL, (255.0 * (double)m_music_volume / 100.0));

}

void Sound_engine::set_music_volume(int v)
{
	m_music_volume = v;
//~ 	FSOUND_SetVolume(MUSIC_CANAL, (255.0 * (double)m_music_volume / 100.0));	
}

int Sound_engine::get_sounds_volume() const
{
	return m_sounds_volume;
}

int Sound_engine::get_music_volume() const
{
	return m_music_volume;
}

