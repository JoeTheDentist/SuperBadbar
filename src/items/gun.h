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

#include "SDL/SDL.h"
#include "../util/lists.h"
#include "../sound/sound_manager.h"
#include "../util/globals.h"
#include "../items/weapons.h"
#include <list>



class Sprites;
class Projectile;
class Sound_manager;
class Pictures_container;

/**
 * 	@class Gun
 * 	@brief Instance d'un gun
 */
class Gun: public Weapon {
private:
public:
	/**
	 * 	@brief Constructeur
	 *	@param proj_pics images des projectiles de l'armes
	*/
	Gun(SDL_Surface **proj_pics);

	/**
	 * 	@brief Constructeur
	 *	@param type Le type de l'arme
	 *	@param proj_pics Images des projectiles de l'armes
	 *	@param sound_manager Le gestionnaire de son
	 *	@todo changer le chargement des images des projectiles\n
	*/
	Gun(weapon_type type, SDL_Surface **proj_pics, Sound_manager *sound_manager);

	/**
	 * 	@brief Constructeur
	 *	@param pictures_container Le gestionnaire d'images
	 *	@param sound_manager Le gestionnaire de son
	*/
	Gun(Pictures_container *pictures_container, Sound_manager *sound_manager);

	/**
	 * 	@brief Destructeur
	 */
	~Gun();
	
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
