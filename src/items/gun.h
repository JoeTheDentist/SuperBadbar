/**
 * 	@file gun.h
 * 	@brief Header de la classe Gun
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _GUN_
#define _GUN_

#include "../items/weapons.h"
#include <list>
#include "../util/globals.h"



class Sprites;
class Projectile;


/**
 * 	@class Gun
 * 	@brief Instance d'un gun
 */
class Gun: public Weapon {
private:
public:
	/**
	 * 	@brief Constructeur
	*/
	Gun();

	/**
	 * 	@brief Destructeur
	 */
	~Gun();

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
