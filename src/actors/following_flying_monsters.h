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

#include "../actors/monsters.h"
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
	
	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre 
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/
	Following_flying_monster(std::string name, int posx, int posy);

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	Following_flying_monster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Following_flying_monster();

	/**
	 * 	@brief Met a jour la vitesse du monstre
	**/
	void update_speed_simple();
};


#endif // FOLLOWING_FLYING_MONSTERS_H_INCLUDED
