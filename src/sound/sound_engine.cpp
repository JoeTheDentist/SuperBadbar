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


Sound_engine::Sound_engine()
{

	PRINT_CONSTR(1, "Construction du Sound_engine")
	//~ FSOUND_Init(44100, 32, 0);
//~ 	/*m_fire = new FSOUND_SAMPLE*[SHOTGUN + 1];
//~ 	m_music = FSOUND_Stream_Open((rac+"/sound/music/level1.mp3").c_str(), 0, 0, 0);
//~ 	if (m_music == NULL) {
//~ 		PRINT_DEBUG(1, "Impossible de charger la musique")
//~ 	}

//~ 	FSOUND_SetPan(BABAR_FIRE_CANAL, 5);
//~ 	FSOUND_SetVolume(BABAR_FIRE_CANAL, 5);
//~ 	*/
}



Sound_engine::~Sound_engine()
{
	PRINT_CONSTR(1, "Destruction du Sound_engine")
	//~ FSOUND_Close();
}


void Sound_engine::play_music()
{
	/*FSOUND_Stream_Play(MUSIC_CANAL, m_music);*/
}

void Sound_engine::play_sound(std::string key)
{
	PRINT_TRACE(1, "jeu du son %s", key.c_str())
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
//~ 	int channel = FSOUND_PlaySound(4, to_play);
//~ 	FSOUND_SetVolume(channel, 100);
//~ 	
}


void Sound_engine::play_sound(Sonorisable *sonorisable)
{
	while (!sonorisable->no_more_sounds()) {
		play_sound(sonorisable->get_next_sound());
		sonorisable->pop_sound();
	}
}
