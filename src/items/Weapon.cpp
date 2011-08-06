/**
 * 	@file weapons.cpp
 * 	@brief Implémentation de la classe Weapon
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "Weapon.h"
#include "util/debug.h"
#include "actors/Projectile.h"


Weapon::Weapon()
{
	PRINT_CONSTR(2, "construction d'une weapon");
}

Weapon::~Weapon()
{
	PRINT_CONSTR(2, "Destruction d'une Weapon")
}

uint32_t Weapon::reload_time() const
{
    return m_reload_time;
}

int Weapon::munitions() const
{
	return m_munitions;
}

weapon_type Weapon::type_of_weapon() const
{
	return m_weapon_type;
}
