/**
 * 	@file sound_manager.h
 * 	@brief Header de la classe Sound_manager
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _SOUND_MANAGER
#define _SOUND_MANAGER

#include "../../lib/fmodapi375win/api/inc/fmod.h"

#include "../items/weapons.h"

#define MUSIC_CANAL 1
#define BABAR_FIRE_CANAL 2



/**
 * 	@class Sound_manager
 * 	@brief Moteur de son
 *
 *	@todo tout refaire buu
 *
 */
class Sound_manager {
private:
	/*FSOUND_STREAM *m_music;
	FSOUND_SAMPLE *m_babar_jump;
	FSOUND_SAMPLE *m_babar_rugissement;
	FSOUND_SAMPLE **m_fire;
	FSOUND_SAMPLE *m_monster_damage;*/


public:

	/**
	 * @brief Constructeur
	*/
	Sound_manager();

	/**
	 * @brief Destructeur
	*/
	~Sound_manager();

	/**
	 * @brief Joue la musique
	*/
	void play_music();

	/**
	 * 	@brief Joue le son de tir d'une arme
	 *	@param weapon le type d'arme
	*/
	void play_fire(int weapon);

	/**
	 * @brief Joue le son de saut de babar
	*/
	void play_babar_jump();

	/**
	 * @brief Joue le barrissement (ça se dit?) de babar
	*/
	void play_babar_rugissement();

	/**
	 * @brief Joue le son d'un monstre qui prend un coup
	*/
	void play_monster_damage();
};


#endif
