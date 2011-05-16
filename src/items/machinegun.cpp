/**
 * 	@file shotgun.cpp
 * 	@brief Implémentation de la classe Machinegun
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "machinegun.h"
#include "../util/debug.h"
#include "../actors/projectiles.h"
#include "../util/globals.h"
#include "../util/repertories.h"


Machinegun::Machinegun()
{
	PRINT_CONSTR(2, "Construction d'un Machinegun")
	m_last_dir_h = 3;
    m_weapon_type = MACHINEGUN;
	m_reload_time = RELOAD_MACHINEGUN;
	m_munitions = MUN_MACHINEGUN;

}

Machinegun::~Machinegun()
{
	PRINT_CONSTR(2, "Destruction d'un Machinegun")
}

std::list<Projectile*> *Machinegun::fire(Rect pos, direction h, dmg_chan type)
{
	std::list<Projectile*> *proj_list = new std::list<Projectile*>();
	if (m_munitions >= 0) {
		int dir_h = (2*h-1)*PROJ_SPEED;
		proj_list->push_back(new Projectile(pos, h, dir_h, 0,1, type));
		m_munitions --;
	}
	gSound->play_sound(FIRE_SOUNDS_R + "gun.wav");
	return proj_list;
}


weapon_type Machinegun::type_of_weapon() const
{
	return MACHINEGUN;
}


void Machinegun::add_munitions()
{
	m_munitions += MUN_MACHINEGUN;
	if (m_munitions += MUN_MACHINEGUN * 2)
		m_munitions = MUN_MACHINEGUN * 2;

}
