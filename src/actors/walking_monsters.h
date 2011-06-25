/**
 * 	@file WalkingMonsters.h
 * 	@brief Header de la classe WalkingMonster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _WalkingMonsterS_
#define _WalkingMonsterS_

#include "../actors/monsters.h"

class Analyser;


/**
 * 	@class WalkingMonster
 * 	@brief Monstre qui marche
 *
 */
class WalkingMonster : public Monster {
private:


public:
	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/
	WalkingMonster(std::string name, int posx, int posy);

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	WalkingMonster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~WalkingMonster();
};



#endif


