/**
 * 	@file projectiles.h
 * 	@brief Header de la classe Projectile
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#ifndef _PROJECTILES_
#define _PROJECTILES_

#include "actor.h"
#include "projectiles_manager.h"

#define PROJ_DAMAGE 1
#define ROCKET_DAMAGE 10
#define ROCKET_LIFE_SPAN 40
#define PROJ_LIFE_SPAN 15   /* Durée de vie d'un projectile */

class Static_data;

enum state_p {
    NONE
};

/**
 * 	@class Projectile
 * 	@brief Projectiles du jeu
 */
class Projectile: public Actor {
protected:
    state_p m_state;
    unsigned int m_damage;      /* Nombre de pt des vies que le projectile va faire perdre */
	bool m_dead;				/* Indique si le projectile est à supprimer */
	int m_life_span;
	ouille_chan m_chan;
	bool m_invincible;

public:
    /*!
	 *	@brief Constructeur
	*/
    Projectile();

	/*!
	 *	@brief Constructeur
	*/
    Projectile(Rect pos, direction h, unsigned int speedx, unsigned int speedy, unsigned int damage);

	/*!
	 * 	@brief Destructeur
	*/
     ~Projectile();

	/*!
	 * 	@brief Met à jour la position du Projectile
	 *	@param collisions_manager Gestionnaire de collisions
	*/
	virtual void update_pos(Collisions_manager *collisions_manager);

	/*!
	 * 	@brief Met à jour de la direction du Projectile
	*/
	virtual void update_state();

 	/*!
	 * 	@brief Met à jour la position du Projectile
	*/
	virtual void update_speed();

	/*!
	 * 	@brief Mutateur
	*/
	void set_chan(ouille_chan chan);

	/*!
	 * 	@brief Accesseur
	 *	@return Le nombre de points de vies que fait perdre le projectile
	*/
    virtual unsigned int damage() const;

	/*!
	 * 	@brief Accesseur
	 *	@return La vitesse du projectile
	*/
    virtual Rect speed() const;   /* Accesseur */

	/*!
	 *	@brief Accesseur
	 *	@return Vrai si le Projectile doit etre supprimé
	*/
	virtual bool dead() const;

	/*!
	 *	@brief Mutateur: "tue" le projectile
	*/
	virtual void kill();

	/**
	 *  @brief Acceseur
	 */
    bool invincible();
};

#endif
