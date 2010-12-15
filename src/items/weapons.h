/**
 * 	@file weapons.h
 * 	@brief header de la classe Weapon
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef WEAPONS_H_INCLUDED
#define WEAPONS_H_INCLUDED

#include "SDL/SDL.h"
#include "../util/lists.h"
#include "../sound/sound_manager.h"
#include "../util/globals.h"


#define PROJ_LIFE_SPAN 15   /* Durée de vie d'un projectile */
#define PROJ_SPEED 40       /* Vitesse des projectiles */

/* nombre maximal de munitions par armes */
#define MUN_GUN 999
#define MUN_MACHINEGUN 300
#define MUN_SHOTGUN 10

/* temps de recharge des armes */
#define RELOAD_GUN 2
#define RELOAD_MACHINEGUN 0
#define RELOAD_SHOTGUN 10


class Sprites;
class Babar;
class Sound_manager;

enum horizontal {
    LEFT, RIGHT
};

enum vertical {
    UP, DOWN
};



enum weapon_type {
    GUN, MACHINEGUN, SHOTGUN // ATTENTION: SHOTGUN doit rester la derniere arme de l'enum pour que l'ensemble du programme ne bug pas
};

class Projectile;
class Sound_manager;


/**
 * 	@class Weapon
 * 	@brief Instance d'une arme
 *	
 *	@todo changer le fonctionnement: l'arme doit contenir
 *	un pointeur vers son propriétaire pour savoir à quelle
 * 	"alliance" elle appartient, ainsi qu'un pointeur vers le gestionnaire
 *	de projectiles (éventuellement en static avec une méthode set)
 */
class Weapon
{
private:
	weapon_type m_weapon_type;              /* type de l'arme */
	uint32_t m_reload_time;                 /* temps entre deux tirs */
	List<Projectile*> *m_projectiles_list;				/* liste de projectiles dans laquelle "tire" l'arme */
	SDL_Surface **m_proj_pics;
	Sound_manager *m_sound_manager;
	int m_munitions;
	float m_last_dir_h;
public:
	/**
	 * 	@brief Constructeur
	 *	@param projectiles_list Liste de projectiles dans laquelle tire l'arme
	 *	@param proj_pics images des projectiles de l'armes
	 *	@todo changer le chargement des images des projectiles\n
	 *	(éventuellement le déléguer à projectiles)
	*/
	Weapon(List<Projectile*> *projectiles_list, SDL_Surface **proj_pics);

	/**
	 * 	@brief Constructeur
	 *	@param projectiles_list Liste de projectiles dans laquelle tire l'arme
	 *	@param proj_pics Images des projectiles de l'armes
	 *	@param sound_manager Le gestionnaire de son
	 *	@todo changer le chargement des images des projectiles\n
	 *	(éventuellement le déléguer à projectiles)
	*/
	Weapon(weapon_type type, List<Projectile*> *projectiles_list, SDL_Surface **proj_pics, Sound_manager *sound_manager);

	/**
	 * 	@brief Destructeur
	 */
	~Weapon();
	
	/**
	 * 	@brief Tire en fonction de l'arme
	 *	@param La position du propriétaire de l'arme
	 *	@param horizontal la direction de tir
	 */
	void fire(Rect pos, horizontal h);
	
	/**
	 * 	@brief Accesseur
	 *	@return Le temps de rechargement (en cycles de jeu)
	 */
	uint32_t reload_time() const;
	
	/**
	 * 	@brief Changement d'arme
	 *	@param type Le type de la nouvelle arme
	 */
	void change_weapon(weapon_type type);
	
	/**
	 * 	@brief Accesseur
	 *	@return Le nombre de munitions restantes
	 */
	int munitions() const;
	
	/**
	 * 	@brief Accesseur
	 *	@return Le type de l'arme
	 */
	weapon_type type_of_weapon() const;

};

#endif // WEAPONS_H_INCLUDED
