/**
 * 	@file boss_elmer.h
 * 	@brief Header de la classe Boss_elmer
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */

#ifndef _BABAR_BOSS_ELMER_
#define _BABAR_BOSS_ELMER_

#include "../actors/boss.h"



/**
 * 	@class Boss_elmer
 * 	@brief Elmer (premier boss)
 *
 */

class Boss_elmer : public Boss {
private:

public:

	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/

	Boss_elmer(std::string name, int posx, int posy);
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	Boss_elmer(Analyser *analyserLevel);

	~Boss_elmer();

	void update_speed_simple();

	void update_speed_ia();

	void update();

};



#endif


