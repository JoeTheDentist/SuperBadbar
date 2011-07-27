/**
 * 	@file Following_FlyingMonsters.h
 * 	@brief Header de la classe Following_FlyingMonsters
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef FOLLOWING_FlyingMonsterS_H_INCLUDED
#define FOLLOWING_FlyingMonsterS_H_INCLUDED

#include <actors/Monster.h>
#include <actors/FlyingMonster.h>

class Analyser;


/**
 * 	@class FollowingFlyingMonster
 * 	@brief Monstre qui vole et qui suit
 *
 */
class FollowingFlyingMonster : public FlyingMonster {
private:
	int m_high_min;

public:

	/**
	 *	@brief Constructeur
	 *	@param name Le nom du monstre
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/
	FollowingFlyingMonster(std::string name, int posx, int posy);

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	FollowingFlyingMonster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~FollowingFlyingMonster();

	/**
	 * 	@brief Met a jour la vitesse du monstre
	**/
	void update_speed_simple();
};


#endif // FOLLOWING_FlyingMonsterS_H_INCLUDED
