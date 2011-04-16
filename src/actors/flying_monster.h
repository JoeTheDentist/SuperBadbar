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

#include "../actors/monsters.h"

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
	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre 
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/
	Flying_monster(std::string name, int posx, int posy);

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	Flying_monster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Flying_monster();
};



#endif


