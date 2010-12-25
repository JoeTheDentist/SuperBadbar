/**
 * 	@file weapons.cpp
 * 	@brief Implémentation de la classe Weapon
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
#include <iostream>
#include <stdint.h>

#include "weapons.h"
#include "../util/debug.h"
#include "../sprites/projectiles.h"

Weapon::Weapon()
{
	PRINT_CONSTR(2, "construction d'une weapon");
}

Weapon::~Weapon()
{
	PRINT_CONSTR(2, "Destruction d'une Weapon")
}

std::list<Projectile*> *Weapon::fire(Rect pos, horizontal h)
{
	std::list<Projectile*> *proj_list = new std::list<Projectile*>();
	return proj_list;
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

void Weapon::add_munitions() 
{
}
