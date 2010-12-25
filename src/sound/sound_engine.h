/**
 * 	@file sound_engine.h
 * 	@brief Header de la classe Sound_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _SOUND_ENGINE_
#define _SOUND_ENGINE_

#include <fmod/fmod.h>
#include <string>
#include <map>
#include "../items/weapons.h"

#define MUSIC_CANAL 1
#define BABAR_FIRE_CANAL 2

class Sound;
class Sonorisable;
/**
 * 	@class Sound_engine
 * 	@brief Moteur de son
 *
 *
 */
class Sound_engine {
private:
	std::map<std::string, FSOUND_SAMPLE*> m_sound_samples;

	/*FSOUND_STREAM *m_music;
	FSOUND_SAMPLE *m_babar_jump;
	FSOUND_SAMPLE *m_babar_rugissement;
	FSOUND_SAMPLE **m_fire;
	FSOUND_SAMPLE *m_monster_damage;*/


public:
	
	/**
	 * @brief Constructeur
	*/
	Sound_engine();

	/**
	 * @brief Destructeur
	*/
	~Sound_engine();

	/**
	 * @brief Joue la musique 
	*/
	void play_music();

	/**
	 * @brief Joue la musique 
	*/
	void play_sound(std::string key);

	void play_sound(Sonorisable *sonorisable);

};


#endif
