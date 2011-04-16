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

#include "actor.h"
#include "../video/anim_pic.h"
#include "../sound/sonorisable.h"
#include <list>

class Anim;
class Babar;
class Surface;
class Weapon;
class Analyser;
class Projectile;


/**
 * 	@class Monster
 * 	@brief Entité hostile à Babar
 *
 */

class Monster: public Actor, public Sonorisable {
protected:
    state_m m_state;
	std::string m_nom;				/* sa nature (peut-etre à enlever) */
	int m_speed_def;               	/* vitesse en norme */
	int m_life;                    	/* vies */
	bool m_fire;
	unsigned int m_fire_phase;
	Weapon *m_weapon;

public:
	
	/*!
	 *	@brief Constructeur
	 *	@param name Le nom du monstre 
	 *	@param posx Position initiale
	 *	@param posy Position initiale
	*/
	Monster(std::string name, int posx, int posy);

	/**
	 * 	@brief Constructeur
	 *	@param analyserLevel Analyseur du level avec curseur devant le monstre a ajouter
	 */
	Monster(Analyser *analyserLevel);

	/**
	 * 	@brief Destructeur
	 */
	~Monster();


	/*!
	 *	@brief init monster's datas from a .mstr file
	*	@param file Le chemin du fichier monstre depuis le fichier des monstres (MONSTERS_STATS_R)
	*/
	void initFromMonsterFile(std::string file);

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
	 * 	@brief Fait perdre des vies au monstre
	 *	@param damage Le nombre de viesà faire perdre
	 */
	void damage(unsigned int damage);

	/**
	 *	@brief Methode reservee pour les actions speciales telles que le tir
	 */
	virtual void update();

	/**
	 * 	@brief Accesseur: Indique si le monstre est mort
	 *	@return Vrai si les points de vies sont <= 0
	 */
	bool dead() const;

	void kill();

	/*!
	 *	@brief Accesseur: indique si on peut tirer
	 *	@return Vrai si on peut tirer
	 */
	bool can_fire();

	/**
	 * 	@brief Fait tirer le monstre
	 *	@return La liste de projectiles tirés
	 *
	 *	Doit etre precede de can_fire()
	 */
	std::list<Projectile*> *fire();
};

#endif
