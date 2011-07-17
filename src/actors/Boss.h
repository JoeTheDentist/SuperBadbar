/**
 * 	@file boss.h
 * 	@brief Header de la classe Boss
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

#ifndef _BABAR_BOSS_
#define _BABAR_BOSS_


#include "../actors/Monster.h"
#include "../video/LifeBarPossessor.h"

/**
 * 	@class Boss
 * 	@brief Boss classique
 *
 */

class Boss : public Monster, public LifeBarPossessor {
public:

	/**
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
	 * 	@brief Met Ã  jour la vitesse du monstre quand il est proche de babar
	*/
	virtual void update_speed_ai();

        /**
         *  @brief Mise à jour
         */
	virtual void update();

        /**
         *  @brief Niveau de la barre de vie
         *  @return etat de la barre de vie
         */
	virtual double life_bar_status() { return double(m_life) / double(m_life_max);}

        /**
         *  @brief Mort
         */
	virtual void kill();

private:
        /**
         *  @brief Initialisation du boss
         */
	void initBoss();

};



#endif


