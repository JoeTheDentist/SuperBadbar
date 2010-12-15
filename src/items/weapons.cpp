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
#include "../util/lists.h"
#include "../util/debug.h"
#include "../sprites/projectiles.h"



Weapon::Weapon(List<Projectile*> *projectiles_list, SDL_Surface **proj_pics)
{
	m_projectiles_list = projectiles_list;
	m_proj_pics = proj_pics;
	PRINT_CONSTR(2, "Construction d'une Weapon")
    m_weapon_type = GUN;
    m_reload_time = 2;
}

Weapon::Weapon(weapon_type type, List<Projectile*> *projectiles_list, SDL_Surface **proj_pics, Sound_manager *sound_manager)
{

	PRINT_CONSTR(2, "Construction d'une Weapon")
	m_last_dir_h = 3;
	m_proj_pics = proj_pics;
	m_sound_manager = sound_manager;
    m_weapon_type = type;
	m_projectiles_list = projectiles_list;
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

void Weapon::fire(Rect pos, horizontal h)
{
    Projectile * proj;
	m_sound_manager->play_fire(m_weapon_type);
	int dir_h =0;
    switch (m_weapon_type) {
        case GUN :
            proj = new Projectile(pos, h, (2*h-1)*PROJ_SPEED, 0,1, m_proj_pics);
            m_projectiles_list->add(proj);
			m_munitions++;
			break;
        case MACHINEGUN:
            dir_h = (2*h-1)*PROJ_SPEED;
			proj = new Projectile(pos, h, dir_h, 0,1, m_proj_pics);
            m_projectiles_list->add(proj);
            break;
        case SHOTGUN:
            int x[5];
            int y[5];
            Rect pos2;
            Rect pos3;

            Projectile * proj[5];
            for(int i = 0;i<5;i++) {
                x[i] = PROJ_SPEED;
            }
            y[0] = 4;
            y[1] = 2;
            y[2] = 0;
            y[3] = 2;
            y[4] = 4;

            pos2.x = pos.x + 5*h;
            pos2.y = pos.y + 5;

            pos3.x = pos.x + 10*h;
            pos3.y = pos.y + 10;


            for(int i = 0;i<5;i++) {
                proj[i] = new Projectile(pos, h, (2*h-1)*x[i] + rand()%3-1, rand()%3-1,1, m_proj_pics);
				m_projectiles_list->add(proj[i]);
            }
            for(int i = 0;i<5;i++) {
                proj[i] = new Projectile(pos2, h, (2*h-1)*x[i] + rand()%3-1, rand()%3-1,1, m_proj_pics);
                m_projectiles_list->add(proj[i]);
            }
            for(int i = 0;i<5;i++) {
                proj[i] = new Projectile(pos3, h, (2*h-1)*x[i] + rand()%3-1, rand()%3-1,1, m_proj_pics);
                m_projectiles_list->add(proj[i]);
            }

            break;
    }
	m_munitions --;
	if (m_munitions <= 0)
		change_weapon(GUN);

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
