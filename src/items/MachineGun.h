/**
 * 	@file MachineGun.h
 * 	@brief Header de la classe MachineGun
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _MACHINEGUN_
#define _MACHINEGUN_


#include <list>

#include <items/Weapon.h>
#include "util/globals.h"



class Sprites;
class Projectile;


/**
 * 	@class MachineGun
 * 	@brief Instance d'un MachineGun
 *
 *	@todo changer le fonctionnement: l'arme doit contenir
 *	un pointeur vers son propriétaire pour savoir �  quelle
 * 	"alliance" elle appartient, ainsi qu'un pointeur vers le gestionnaire
 *	de projectiles (éventuellement en static avec une méthode set)
 */
class MachineGun: public Weapon
{
private:
public:
    /**
     * 	@brief Constructeur
    */
    MachineGun();


    /**
     * 	@brief Destructeur
     */
    ~MachineGun();

    /**
     * 	@brief Tire plusieurs balles de fusil �  pompe
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
