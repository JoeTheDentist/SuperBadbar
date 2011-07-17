/**
 * 	@file monster_basic_weapon.hpp
 * 	@brief Header de la classe Monster_basic_weapon
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */
#ifndef _MONSTER_BASIC_WEAPON_
#define _MONSTER_BASIC_WEAPON_

#include "../items/Weapon.h"
#include <list>
#include "../util/globals.h"



class Sprites;
class Projectile;


/**
 * 	@class Monster_basic_weapon
 * 	@brief Instance d'une arme basique de monstres (tire aléatoirement comme un gun)
 */
class Monster_basic_weapon: public Weapon {
private:
	int m_fire_frequency; /* this weapon fires randomly with a probability m_fire_frenquency */
public:
	/**
	 * 	@brief Constructeur
	*/
	Monster_basic_weapon();

	/**
	 * 	@brief Destructeur
	 */
	~Monster_basic_weapon();

	/**
	 * 	@brief Tire une balle de gun
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
	 *
	 *	(ne fait rien pour cette instance d'arme)
	 */
	virtual void add_munitions();
};

#endif
