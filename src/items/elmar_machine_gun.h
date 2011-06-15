#ifndef ELMAR_MACHINE_GUN_H
#define ELMAR_MACHINE_GUN_H

#include <list>
#include "weapons.h"

class Projectile;

class Elmar_machine_gun : public Weapon
{
    public:
	/**
	 * 	@brief Constructeur
	*/
	Elmar_machine_gun();


	/**
	 * 	@brief Destructeur
	 */
	~Elmar_machine_gun();

	/**
	 * 	@brief Tire
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

#endif // ELMAR_MACHINE_GUN_H
