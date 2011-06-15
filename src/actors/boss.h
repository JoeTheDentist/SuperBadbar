/**
 * 	@file boss.h
 * 	@brief Header de la classe Boss
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date juin 2011
 *
 */

#ifndef _BABAR_BOSS_
#define _BABAR_BOSS_


#include "../actors/monsters.h"
#include "../video/life_bar_possessor.h"

/**
 * 	@class Boss
 * 	@brief Boss classique
 *
 */

class Boss : public Monster, public Life_bar_possessor {
public:

	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/

	Boss(std::string name, int posx, int posy);
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	Boss(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Boss();

	/**
	 * 	@brief Met à jour la vitesse du monstre quand il est proche de babar
	*/
	virtual void update_speed_ai();

	virtual void update();

	virtual double life_bar_status() { return double(m_life) / double(m_life_max);}

	virtual void kill();

private:
	void initBoss();

};



#endif


