/**
 * 	@file monsters.h
 * 	@brief Header de la classe Monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _MONSTERS_
#define _MONSTERS_

/* distance à partir de laquelle le monstre se déplace suivant l'ai */
#define SWITCH_DIST 400

#include "sprites.h"
#include "../video/animation.h"
#include "../sound/sonorisable.h"

class Animation;
class Babar;
class Surface;


enum state_m {
    WALKING, WAIT, DEATH
};


/**
 * 	@class Monster
 * 	@brief Entité hostile à Babar
 *
 */

class Monster: public Sprite, public Sonorisable {
protected:
    state_m m_state;
	std::string m_nom;				/* sa nature (peut-etre à enlever) */
	int m_speed_def;               	/* vitesse en norme */
	int m_life;                    	/* vies */
	bool m_can_fire;                /* si le monstre à le droit de tirer ou non */
	bool m_fire;
public:
	/**
	 * 	@brief Constructeur
	 */
	Monster();

	/**
	 * 	@brief Destructeur
	 */
	~Monster();

	/**
	 * 	@brief Mise à jour de la vitesse du monstre
	 */
	void update_speed();

	/**
	 * 	@brief Mise à jour de la vitesse du monstre (non ai)
	 */
	void virtual update_speed_simple();

	/**
	 * 	@brief Mise à jour de la vitesse du monstre (ai)
	 *  Si non redéfinie = à simple
	 */
	void virtual update_speed_ai();

	/**
	 * 	@brief Acesseur
	 */
	Surface *current_picture() const;

	/**
	 * 	@brief Fait perdre des vies au monstre
	 *	@param damage Le nombre de viesà faire perdre
	 */
	void damage(uint32_t damage);

	/**
	 * 	@brief Accesseur: Indique si le monstre est mort
	 *	@return Vrai si les points de vies sont <= 0
	 */
	bool dead() const;


};

#endif
