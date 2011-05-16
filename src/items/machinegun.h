/**
 * 	@file machinegun.h
 * 	@brief Header de la classe Machinegun
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _MACHINEGUN_
#define _MACHINEGUN_

#include "../items/weapons.h"
#include <list>
#include "../util/globals.h"



class Sprites;
class Projectile;


/**
 * 	@class Machinegun
 * 	@brief Instance d'un Machinegun
 *
 *	@todo changer le fonctionnement: l'arme doit contenir
 *	un pointeur vers son propriétaire pour savoir à quelle
 * 	"alliance" elle appartient, ainsi qu'un pointeur vers le gestionnaire
 *	de projectiles (éventuellement en static avec une méthode set)
 */
class Machinegun: public Weapon {
private:
public:
	/**
	 * 	@brief Constructeur
	*/
	Machinegun();


	/**
	 * 	@brief Destructeur
	 */
	~Machinegun();

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
