/**
 * 	@file weapons.cpp
 * 	@brief Implémentation de la classe Weapon
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
 #include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>
#include <time.h>

#include "weapons.h"
#include "../util/debug.h"
#include "../sprites/projectiles.h"



Weapon::Weapon()
{
}

Weapon::Weapon(Pictures_container *pictures_container, Sound_manager *sound_manager) : 
m_sound_manager(sound_manager), m_pictures_container(pictures_container)
{
	PRINT_CONSTR(1, "construction d'une vraie weapon");
}

Weapon::Weapon(SDL_Surface **proj_pics)
{
	m_proj_pics = proj_pics;
	PRINT_CONSTR(2, "Construction d'une Weapon")
    m_weapon_type = GUN;
    m_reload_time = 2;
}

Weapon::Weapon(weapon_type type, SDL_Surface **proj_pics, Sound_manager *sound_manager)
{

	PRINT_CONSTR(2, "Construction d'une Weapon")
	m_last_dir_h = 3;
	m_proj_pics = proj_pics;
	m_sound_manager = sound_manager;
    m_weapon_type = type;
    switch (m_weapon_type) {
        case GUN :
            m_reload_time = RELOAD_GUN;
			m_munitions = MUN_GUN;
            break;
        case MACHINEGUN:
            m_reload_time = RELOAD_MACHINEGUN;
			m_munitions = MUN_MACHINEGUN;
            break;
        case SHOTGUN:
            m_reload_time = RELOAD_SHOTGUN;
			m_munitions = MUN_SHOTGUN;
            break;
    }
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

void Weapon::change_weapon(weapon_type type)
{
	m_weapon_type = type;
    switch (type) {
        case GUN :
            m_reload_time = RELOAD_GUN;
			m_munitions = MUN_GUN;
            break;
        case MACHINEGUN:
            m_reload_time = RELOAD_MACHINEGUN;
			m_munitions = MUN_MACHINEGUN;
            break;
        case SHOTGUN:
            m_reload_time = RELOAD_SHOTGUN;
			m_munitions = MUN_SHOTGUN;
            break;
    }
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
