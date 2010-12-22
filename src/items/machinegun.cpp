/**
 * 	@file shotgun.cpp
 * 	@brief Implémentation de la classe Machinegun
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
 #include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "machinegun.h"
#include "../util/debug.h"
#include "../sprites/projectiles.h"



Machinegun::Machinegun(SDL_Surface **proj_pics)
{
	m_proj_pics = proj_pics;
	PRINT_CONSTR(2, "Construction d'une Machinegun")
    m_weapon_type = MACHINEGUN;
    m_reload_time = RELOAD_MACHINEGUN;
}

Machinegun::Machinegun(Pictures_container *pictures_container, Sound_manager *sound_manager) : Weapon(pictures_container, sound_manager)
{
	PRINT_CONSTR(2, "Construction d'un Machinegun")
	m_last_dir_h = 3;
    m_weapon_type = MACHINEGUN;
	m_reload_time = RELOAD_MACHINEGUN;
	m_munitions = MUN_MACHINEGUN;

}

Machinegun::Machinegun(weapon_type type, SDL_Surface **proj_pics, Sound_manager *sound_manager)
{

	PRINT_CONSTR(2, "Construction d'une Machinegun")
	m_last_dir_h = 3;
	m_proj_pics = proj_pics;
	m_sound_manager = sound_manager;
    m_weapon_type = type;
	m_reload_time = RELOAD_MACHINEGUN;
	m_munitions = MUN_MACHINEGUN;

}

Machinegun::~Machinegun()
{
	PRINT_CONSTR(2, "Destruction d'un Machinegun")
}

std::list<Projectile*> *Machinegun::fire(Rect pos, horizontal h)
{
	std::list<Projectile*> *proj_list = new std::list<Projectile*>();
	if (m_munitions >= 0) {
		m_sound_manager->play_fire(MACHINEGUN);
		int dir_h = (2*h-1)*PROJ_SPEED;
		proj_list->push_back(new Projectile(pos, h, dir_h, 0,1, m_pictures_container));
		m_munitions --;
	}
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
