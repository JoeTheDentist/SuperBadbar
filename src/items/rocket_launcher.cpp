/**
 * 	@file rocket_launcher.cpp
 * 	@brief Implementation de la classe Rocket_launcher
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include <iostream>
#include <stdint.h>

#include "rocket_launcher.h"
#include "../util/debug.h"
#include "../actors/rocket.h"
#include "../actors/projectiles.h"
#include "../util/globals.h"
#include "../util/repertories.h"


Rocket_launcher::Rocket_launcher()
{
	PRINT_CONSTR(2, "Construction d'une Rocket_launcher")
	m_last_dir_h = 3;
    m_weapon_type = ROCKET_LAUNCHER;
	m_reload_time = RELOAD_ROCKET_LAUNCHER;
	m_munitions = MUN_ROCKET_LAUNCHER;
}

Rocket_launcher::~Rocket_launcher()
{
	PRINT_CONSTR(2, "Destruction d'un Rocket_launcher")
}

std::list<Projectile*> *Rocket_launcher::fire(Rect pos, direction h, dmg_chan type)
{
	std::list<Projectile*> *proj_list = new std::list<Projectile*>();
	Projectile * r = new Rocket(pos, h, (2*h-1)*PROJ_SPEED, 0,ROCKET_DAMAGE);
	r->set_chan(type);
	proj_list->push_back(r);
	m_munitions--;
	gSound->play_sound(FIRE_SOUNDS_R + "rocket.wav");
	return proj_list;
}


weapon_type Rocket_launcher::type_of_weapon() const
{
	return m_weapon_type;
}


void Rocket_launcher::add_munitions()
{
	m_munitions += m_munitions;
	if (m_munitions > m_munitions)
		m_munitions = m_munitions;
}
