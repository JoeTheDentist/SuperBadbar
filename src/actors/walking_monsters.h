/**
 * 	@file walking_monsters.h
 * 	@brief Header de la classe Walking_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _WALKING_MONSTERS_
#define _WALKING_MONSTERS_

#include "../actors/monsters.h"

class Analyser;


/**
 * 	@class Walking_monster
 * 	@brief Monstre qui marche
 *
 */
class Walking_monster : public Monster {
private:


public:
    /**
	 * 	@brief Constructeur vide
	*/
    Walking_monster();

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur se fichier
	*/
	Walking_monster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Walking_monster();
};



#endif


