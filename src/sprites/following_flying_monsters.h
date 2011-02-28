/**
 * 	@file Following_flying_monsters.h
 * 	@brief Header de la classe Following_flying_monsters
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef FOLLOWING_FLYING_MONSTERS_H_INCLUDED
#define FOLLOWING_FLYING_MONSTERS_H_INCLUDED

#include "../sprites/monsters.h"
#include "flying_monster.h"

class Analyser;


/**
 * 	@class Following_flying_monster
 * 	@brief Monstre qui vole et qui suit
 *
 */
class Following_flying_monster : public Flying_monster {
private:
	int m_high_min;

public:
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur se fichier
	*/
	Following_flying_monster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Following_flying_monster();

	/**
	 * 	@brief Met à jour la vitesse du monstre
	 *	@param babar Parametre inutilisé dans cette sous classe
	 *
	**/
	void update_speed();
};


#endif // FOLLOWING_FLYING_MONSTERS_H_INCLUDED
