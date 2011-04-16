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
	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre 
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/
	Walking_monster(std::string name, int posx, int posy);

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	Walking_monster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Walking_monster();
};



#endif


