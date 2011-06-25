/**
 * 	@file ChargingMonster.h
 * 	@brief Header de la classe ChargingMonster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mai 2011
 *
 */

#ifndef _ChargingMonster_
#define _ChargingMonster_

#include "../actors/monsters.h"
#include "../actors/WalkingMonsters.h"
#include "../AI/AI.h"

class Analyser;
class AI;


/**
 * 	@class ChargingMonster
 * 	@brief Monstre qui suit babar en marchant
 *
 */

class ChargingMonster : public WalkingMonster {
private:
	const int m_speed_max;
	int m_time_end_charge;
public:

	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/

	ChargingMonster(std::string name, int posx, int posy);
	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	*/
	ChargingMonster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~ChargingMonster();

	/**
	 * 	@brief Mise à jour de la vitesse du monstre (non ai)
	 */
	void virtual update_speed_simple();

	/**
	 * 	@brief Met à jour la vitesse du monstre
	 *
	 *	Le monstre avance par défaut en direction de Babar
	 */
	void update_speed_ai();


};



#endif


