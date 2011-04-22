/**
 * 	@file rocket_launcher.h
 * 	@brief Header de la classe Rocket_launcher
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _BABAR_ROCKET_LAUNCHER_H_
#define _BABAR_ROCKET_LAUNCHER_H_

#include "../items/weapons.h"
#include <list>
#include "../util/globals.h"



class Sprites;
class Projectile;


/**
 * 	@class Rocket_launcher
 * 	@brief Instance d'un gun
 */
class Rocket_launcher: public Weapon {
public:
	/**
	 * 	@brief Constructeur
	*/
	Rocket_launcher();

	/**
	 * 	@brief Destructeur
	 */
	~Rocket_launcher();

	/**
	 * 	@brief Tire une balle de gun
	 *	@param pos La position du propriétaire de l'arme
	 *	@param h la direction de tir
	 *	@return La liste de projectiles tirés
	 */
	std::list<Projectile*> *fire(Rect pos, direction h);

	/**
	 * 	@brief Accesseur
	 *	@return Le type de l'arme
	 */
	weapon_type type_of_weapon() const;

	/**
	 * 	@brief Mutateur: ajoute des munitions
	 */
	virtual void add_munitions();

};

#endif
