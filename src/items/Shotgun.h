/**
 * 	@file shotgun.h
 * 	@brief Header de la classe Shotgun
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _SHOTGUN_
#define _SHOTGUN_


#include "../items/Weapon.h"
#include <list>
#include "../util/globals.h"



class Sprites;
class Projectile;


/**
 * 	@class Shotgun
 * 	@brief Instance d'un shotgun
 */
class Shotgun: public Weapon {
private:
public:
	/**
	 * 	@brief Constructeur
	*/
	Shotgun();

	/**
	 * 	@brief Destructeur
	 */
	~Shotgun();

	/**
	 * 	@brief Tire plusieurs balles de fusil à pompe
	 *	@param pos La position du propriétaire de l'arme
	 *	@param h la direction de tir
	 *	@return La liste de projectiles tirés
	 */
	std::list<Projectile*> *fire(Rect pos, direction h, dmg_chan type);

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
