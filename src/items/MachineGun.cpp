/**
 * 	@file shotgun.cpp
 * 	@brief Implémentation de la classe MachineGun
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "MachineGun.h"
#include "util/debug.h"
#include "actors/Projectile.h"
#include "util/globals.h"
#include "util/repertories.h"


MachineGun::MachineGun()
{
	PRINT_CONSTR(2, "Construction d'un MachineGun")
	m_last_dir_h = 3;
    m_weapon_type = MACHINE_GUN;
	m_reload_time = RELOAD_MACHINEGUN;
	m_munitions = MUN_MACHINEGUN;

}

MachineGun::~MachineGun()
{
	PRINT_CONSTR(2, "Destruction d'un MachineGun")
}

std::list<Projectile*> *MachineGun::fire(Rect pos, direction h, dmg_chan type)
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


weapon_type MachineGun::type_of_weapon() const
{
	return MACHINE_GUN;
}


void MachineGun::add_munitions()
{
	m_munitions += MUN_MACHINEGUN;
	if (m_munitions += MUN_MACHINEGUN * 2)
		m_munitions = MUN_MACHINEGUN * 2;

}
