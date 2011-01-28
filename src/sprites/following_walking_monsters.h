/**
 * 	@file following_walking_monsters.h
 * 	@brief Header de la classe Following_walking_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _FOLLOWING_WALKING_MONSTERS_
#define _FOLLOWING_WALKING_MONSTERS_

#include "../sprites/monsters.h"
#include "../sprites/walking_monsters.h"

class Analyser;


/**
 * 	@class Following_walking_monster
 * 	@brief Monstre qui suit babar en marchant
 *
 */
class Following_walking_monster : public Walking_monster {
private:


public:
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur se fichier
	*/
	Following_walking_monster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Following_walking_monster();

	/**
	 * 	@brief Met à jour la vitesse du monstre
	 *
	 *	Le monstre avance par défaut en direction de Babar
	 */
	void update_speed(Babar *babar);
};



#endif


