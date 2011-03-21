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

#include <stdint.h>
#include <list>
#include "../util/globals.h"

#define PROJ_LIFE_SPAN 15   /* Durée de vie d'un projectile */
#define PROJ_SPEED 40       /* Vitesse des projectiles */

/* nombre maximal de munitions par armes */
#define MUN_GUN 999
#define MUN_MACHINEGUN 100
#define MUN_SHOTGUN 20

/* temps de recharge des armes */
#define RELOAD_GUN 2
#define RELOAD_MACHINEGUN 0
#define RELOAD_SHOTGUN 18


enum direction {
    LEFT, RIGHT, UP, DOWN, NOPE
};


enum weapon_type {
    GUN, MACHINEGUN, SHOTGUN, MONSTER_BASIC_WEAPON, LASTWEAPON // ATTENTION: LASTWEAPON doit rester la derniere arme de l'enum pour que l'ensemble du programme ne bug pas
};


class Sprites;
class Projectile;
struct Rect;

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
protected:
	weapon_type m_weapon_type;              /* type de l'arme */
	uint32_t m_reload_time;                 /* temps entre deux tirs */
	int m_munitions;
	float m_last_dir_h;
public:

	/**
	 * 	@brief Constructeur
	*/
	Weapon();

	/**
	 * 	@brief Destructeur
	 */
	virtual ~Weapon();

	/**
	 * 	@brief Tire en fonction de l'arme
	 *	@param pos La position du propriétaire de l'arme
	 *	@param h la direction de tir
	 *	@return La liste de projectiles tirés
	 */
	virtual std::list<Projectile*> * fire(Rect pos, direction h) = 0;

	/**
	 * 	@brief Accesseur
	 *	@return Le temps de rechargement (en cycles de jeu)
	 */
	virtual uint32_t reload_time() const;


	/**
	 * 	@brief Accesseur
	 *	@return Le nombre de munitions restantes
	 */
	virtual int munitions() const;

	/**
	 * 	@brief Accesseur
	 *	@return Le type de l'arme
	 */
	virtual weapon_type type_of_weapon() const;


	/**
	 * 	@brief Mutateur: ajoute des munitions
	 */
	virtual void add_munitions() = 0;

};

#endif // WEAPONS_H_INCLUDED
