/**
 * 	@file WalkingMonster.h
 * 	@brief Header de la classe WalkingMonster
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _WALKINGMONSTERS_
#define _WALKINGMONSTERS_

#include <actors/Monster.h>

class Analyser;

/*!
 * 	@class WalkingMonster
 * 	@brief Monstre qui marche
 */
class WalkingMonster : public Monster {
private:


public:
	/**
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


