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


#include "../sound/sound_manager.h"
#include "../util/globals.h"
#include "../items/weapons.h"
#include <list>



class Sprites;
class Projectile;
class Sound_manager;


/**
 * 	@class Shotgun
 * 	@brief Instance d'un shotgun
 */
class Shotgun: public Weapon {
private:
public:
	/**
	 * 	@brief Constructeur
	 *	@param proj_pics images des projectiles de l'armes
	 *	@todo changer le chargement des images des projectiles\n
	 *	(éventuellement le déléguer à projectiles)
	*/
	Shotgun(SDL_Surface **proj_pics);

	/**
	 * 	@brief Constructeur
	 *	@param pictures_container Le gestionnaire d'images
	 *	@param sound_manager Le gestionnaire de son
	*/
	Shotgun(Pictures_container *pictures_container, Sound_manager *sound_manager);

	/**
	 * 	@brief Constructeur
	 *	@param type Le type de l'arme
	 *	@param proj_pics Images des projectiles de l'armes
	 *	@param sound_manager Le gestionnaire de son
	*/
	Shotgun(weapon_type type, SDL_Surface **proj_pics, Sound_manager *sound_manager);

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
