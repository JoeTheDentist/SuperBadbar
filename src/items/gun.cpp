/**
 * 	@file gun.cpp
 * 	@brief Implémentation de la classe Gun
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "gun.h"
#include "../util/debug.h"
#include "../sprites/projectiles.h"
#include "../util/globals.h"
#include "../util/repertories.h"


Gun::Gun()
{
	PRINT_CONSTR(2, "Construction d'une Gun")
	m_last_dir_h = 3;
    m_weapon_type = GUN;
	m_reload_time = RELOAD_GUN;
	m_munitions = MUN_GUN;
}

Gun::~Gun()
{
	PRINT_CONSTR(2, "Destruction d'un Gun")
}

std::list<Projectile*> *Gun::fire(Rect pos, direction h)
{
	std::list<Projectile*> *proj_list = new std::list<Projectile*>();
	proj_list->push_back(new Projectile(pos, h, (2*h-1)*PROJ_SPEED, 0,1));
	gSound->play_sound(FIRE_SOUNDS_R + "gun.wav");
	return proj_list;
}


weapon_type Gun::type_of_weapon() const
{
	return GUN;
}


void Gun::add_munitions()
{
	m_munitions += MUN_GUN;
	if (m_munitions > MUN_GUN)
		m_munitions = MUN_GUN;
}
