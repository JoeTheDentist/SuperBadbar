/**
 * 	@file RocketLauncher.h
 * 	@brief Header de la classe RocketLauncher
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _BABAR_ROCKET_LAUNCHER_H_
#define _BABAR_ROCKET_LAUNCHER_H_

#include <list>

#include <items/Weapon.h>
#include "util/globals.h"



class Sprites;
class Projectile;


/**
 * 	@class RocketLauncher
 * 	@brief Instance d'un gun
 */
class RocketLauncher: public Weapon
{
public:
    /**
     * 	@brief Constructeur
    */
    RocketLauncher();

    /**
     * 	@brief Destructeur
     */
    ~RocketLauncher();

    /**
     * 	@brief Tire une balle de gun
     *	@param pos La position du propriétaire de l'arme
     *	@param h la direction de tir
     *	@return La liste de projectiles tirés
     */
    std::list<Projectile*> *fire (Rect pos, Direction h, dmg_chan type);

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
