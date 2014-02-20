/*
* 	@file ElmarMachineGun.h
* 	@brief Header de la classe ElmarMachineGun
*
* 	@author Guillaume Berard & Benoit Morel
* 	@date decembre 2010
*
*/

#ifndef ElmarMachineGun_H
#define ElmarMachineGun_H


#include <list>

#include <items/Weapon.h>

class Projectile;

/**
 *  @class ElmarMachineGun
 *  @brief Le machine gun de Elmar
 */
class ElmarMachineGun : public Weapon
{
public:
    /**
     * 	@brief Constructeur
    */
    ElmarMachineGun();


    /**
     * 	@brief Destructeur
     */
    ~ElmarMachineGun();

    /**
     * 	@brief Tire
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

#endif // ElmarMachineGun_H
