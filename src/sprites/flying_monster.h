/**
 * 	@file walking_monsters.h
 * 	@brief Header de la classe Flying_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _FLYING_MONSTER_
#define _FLYING_MONSTER_

#include "../sprites/monsters.h"

class Analyser;


/**
 * 	@class Flying_monster
 * 	@brief Monstre qui vole
 *
 */
class Flying_monster : public Monster {
private:
	int m_high_min;

public:
    /**
	 * 	@brief Constructeur vide
	*/
	Flying_monster();

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur se fichier
	*/
	Flying_monster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Flying_monster();

	/**
	 * 	@brief Met à jour la vitesse du monstre
	 *	@param babar Parametre inutilisé dans cette sous classe
	 *
	**/
	void update_speed();
};



#endif


