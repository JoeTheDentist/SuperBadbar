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

#include "sprites.h"
#include "../video/animation.h"
class Animation;
class Babar;
class Surface;


enum state_m {
    WALKING, FIRE
};


/**
 * 	@class Monster
 * 	@brief Entité hostile à Babar
 *
 */

class Monster: public Sprite {
protected:
    state_m m_state;
	std::string m_nom;				/* sa nature (peut-etre à enlever) */
	int m_area_begin; 			 	/* début de la zone d'allez-retour */
	int m_area_end;                	/* fin de la zone d'aller-retrou */
	int m_speed_def;               	/* vitesse en norme */
	int m_life;                    	/* vies */
	bool m_can_fire;                /* si le monstre tire ou non */
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
	void virtual update_speed();

	/**
	 * 	@brief Mise à jour de la vitesse en fonction de Babar
	 * 	@todo réorganiser cette paramétrisation
	 */
	void virtual update_speed(Babar * babar);

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
