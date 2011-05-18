/**
 * 	@file charging_monster.h
 * 	@brief Header de la classe Charging_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mai 2011
 *
 */

#ifndef _CHARGING_MONSTER_
#define _CHARGING_MONSTER_

#include "../actors/monsters.h"
#include "../actors/walking_monsters.h"
#include "../AI/AI.h"

class Analyser;
class AI;


/**
 * 	@class Charging_monster
 * 	@brief Monstre qui suit babar en marchant
 *
 */
class Charging_monster : public Walking_monster {
private:
    AI * m_ai;

public:
	
	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre 
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/

	Charging_monster(std::string name, int posx, int posy);
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	Charging_monster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Charging_monster();

	/**
	 * 	@brief Met à jour la vitesse du monstre
	 *
	 *	Le monstre avance par défaut en direction de Babar
	 */
	void update_speed_ai();


};



#endif


