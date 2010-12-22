/**
 * 	@file gun.cpp
 * 	@brief Implémentation de la classe Gun
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
 #include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "gun.h"
#include "../util/debug.h"
#include "../sprites/projectiles.h"



Gun::Gun(SDL_Surface **proj_pics)
{
	m_proj_pics = proj_pics;
	PRINT_CONSTR(2, "Construction d'un Gun")
    m_weapon_type = GUN;
    m_reload_time = RELOAD_GUN;
}

Gun::Gun(weapon_type type, SDL_Surface **proj_pics, Sound_manager *sound_manager)
{

	PRINT_CONSTR(2, "Construction d'une Gun")
	m_last_dir_h = 3;
	m_proj_pics = proj_pics;
	m_sound_manager = sound_manager;
    m_weapon_type = type;
	m_reload_time = RELOAD_GUN;
	m_munitions = MUN_GUN;

}
Gun::Gun(Pictures_container *pictures_container, Sound_manager *sound_manager) : Weapon(pictures_container, sound_manager)
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

std::list<Projectile*> *Gun::fire(Rect pos, horizontal h)
{
	std::list<Projectile*> *proj_list = new std::list<Projectile*>();
	proj_list->push_back(new Projectile(pos, h, (2*h-1)*PROJ_SPEED, 0,1, m_pictures_container));
	return proj_list;
}


weapon_type Gun::type_of_weapon() const
{
	return GUN;
}


void Gun::add_munitions() 
{
	m_munitions += MUN_GUN;
}
