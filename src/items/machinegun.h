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

#include "../sound/sound_manager.h"
#include "../util/globals.h"
#include "../items/weapons.h"
#include <list>



class Sprites;
class Projectile;
class Sound_manager;


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
	 *	@param proj_pics images des projectiles de l'armes
	 *	@todo changer le chargement des images des projectiles\n
	 *	(éventuellement le déléguer à projectiles)
	*/
	Machinegun(SDL_Surface **proj_pics);

	/**
	 * 	@brief Constructeur
	 *	@param pictures_container Le gestionnaire d'images
	 *	@param sound_manager Le gestionnaire de son
	*/
	Machinegun(Pictures_container *pictures_container, Sound_manager *sound_manager);

	/**
	 * 	@brief Constructeur
	 *	@param type Le type de l'arme
	 *	@param proj_pics Images des projectiles de l'armes
	 *	@param sound_manager Le gestionnaire de son
	 *	@todo changer le chargement des images des projectiles\n
	*/
	Machinegun(weapon_type type, SDL_Surface **proj_pics, Sound_manager *sound_manager);

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
	std::list<Projectile*> *fire(Rect pos, horizontal h);
	
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
