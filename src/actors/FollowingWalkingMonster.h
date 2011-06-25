/**
 * 	@file FollowingWalkingMonsters.h
 * 	@brief Header de la classe FollowingWalkingMonster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _FollowingWalkingMonsterS_
#define _FollowingWalkingMonsterS_

#include "../actors/Monster.h"
#include "../actors/WalkingMonster.h"
#include "../AI/AI.h"

class Analyser;
class AI;


/**
 * 	@class FollowingWalkingMonster
 * 	@brief Monstre qui suit babar en marchant
 *
 */
class FollowingWalkingMonster : public WalkingMonster {
private:
    AI * m_ai;

public:

	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/

	FollowingWalkingMonster(std::string name, int posx, int posy);
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	FollowingWalkingMonster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~FollowingWalkingMonster();

	/**
	 * 	@brief Met à jour la vitesse du monstre
	 *
	 *	Le monstre avance par défaut en direction de Babar
	 */
	void update_speed_ai();


};



#endif


