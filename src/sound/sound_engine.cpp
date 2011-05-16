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

//~ 	m_music = FSOUND_Stream_Open((RACINE_R+"/sound/music/level1.mp3").c_str(), 0, 0, 0);
//~ 	play_music();

//~ 	FSOUND_SetPan(BABAR_FIRE_CANAL, 5);
//~ 	FSOUND_SetVolume(BABAR_FIRE_CANAL, 5);
	
}



Sound_engine::~Sound_engine()
{
	PRINT_CONSTR(1, "Destruction du Sound_engine")
}


void Sound_engine::play_music()
{
//~ 	FSOUND_Stream_Play(MUSIC_CANAL, m_music);
}

void Sound_engine::play_sound(std::string key)
{	
//~ 	PRINT_TRACE(1, "jeu du son %s", key.c_str())
//~ 	std::map<std::string, FSOUND_SAMPLE*>::iterator it = m_sound_samples.find(key);
//~ 	FSOUND_SAMPLE *to_play = NULL;
//~ 	if (it == m_sound_samples.end()) {
//~ 		to_play = FSOUND_Sample_Load(FSOUND_FREE, key.c_str(), 0, 0, 0);
//~ 		if (to_play == NULL) {
//~ 			PRINT_DEBUG(1, "impossible de charger le son %s", key.c_str());
//~ 			return;
//~ 		}
//~ 		m_sound_samples.insert(std::pair<std::string, FSOUND_SAMPLE*>(key, to_play));
//~ 	} else {
//~ 		to_play = (*it).second;
//~ 	}
//~ 	PRINT_TRACE(3, "JEU DU SON %s",key.c_str());
//~ 	int channel = FSOUND_PlaySound(FSOUND_FREE, to_play);
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

