/**
 * 	@file WalkingMonster.h
 * 	@brief Header de la classe FlyingMonster
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _FlyingMonster_
#define _FlyingMonster_

#include <actors/Monster.h>

class Analyser;


/**
 * 	@class FlyingMonster
 * 	@brief Monstre qui vole
 *
 */
class FlyingMonster : public Monster {
private:
	int m_high_min;

public:
	/**
	 *	@brief Constructeur
	 *	@param name Le nom du monstre
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/
	FlyingMonster(std::string name, int posx, int posy);

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	FlyingMonster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~FlyingMonster();
};



#endif


