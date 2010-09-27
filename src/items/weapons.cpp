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
	m_last_dir_v = 3;
	m_last_dir_h = 3;
	m_phase_diago = 0;
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
			m_munitions = 50;
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

void Weapon::fire(SDL_Rect pos, horizontal h, vertical v)
{

    Projectile * proj;
	m_sound_manager->play_fire(m_weapon_type);
	int dir_h =0, dir_v = 0;
    switch (m_weapon_type) {
        case GUN :
            proj = new Projectile(pos, h, v, (h-1)*PROJ_SPEED, (v-1)*PROJ_SPEED,1, m_proj_pics);
            m_projectiles_list->add(proj);
			m_munitions++;
			break;
        case MACHINEGUN:
			if (m_last_dir_v != v && m_last_dir_h == h && m_last_dir_h != 1)  {
				m_phase_diago+= 1 + m_reload_time;
				if (m_phase_diago == 1) {
					dir_h = (h-1)*PROJ_SPEED;
					if (m_last_dir_v !=1)
						dir_v = (m_last_dir_v-1)*PROJ_SPEED*2/3 + (v-1)*PROJ_SPEED*2/3;
					else 
						dir_v = (m_last_dir_v-1)*PROJ_SPEED/3 + (v-1)*PROJ_SPEED/3;
				} else if (m_phase_diago > 1) {
					dir_h = (h-1)*PROJ_SPEED;
					if (m_last_dir_v !=1)
						dir_v = (m_last_dir_v-1)*PROJ_SPEED/3 + (v-1)*PROJ_SPEED/3;
					else 
						dir_v = (m_last_dir_v-1)*PROJ_SPEED*2/3 + (v-1)*PROJ_SPEED*2/3;
						
					m_phase_diago = 0;
					m_last_dir_v = 3;
					m_last_dir_h = 3;
				}
			} else if (m_last_dir_v == v && m_last_dir_h != h && m_last_dir_v != 1) {
				m_phase_diago+= 1 + m_reload_time;
				if (m_phase_diago == 1) {
					dir_v = (v-1)*PROJ_SPEED;
					if (m_last_dir_h !=1)
						dir_h = (m_last_dir_h-1)*PROJ_SPEED*2/3 + (h-1)*PROJ_SPEED*2/3;
					else 
						dir_h = (m_last_dir_h-1)*PROJ_SPEED/3 + (h-1)*PROJ_SPEED/3;
				} else if (m_phase_diago > 1) {
					dir_v = (v-1)*PROJ_SPEED;
					if (m_last_dir_h !=1)
						dir_h = (m_last_dir_h-1)*PROJ_SPEED/3 + (h-1)*PROJ_SPEED/3;
					else 
						dir_h = (m_last_dir_h-1)*PROJ_SPEED*2/3 + (h-1)*PROJ_SPEED*2/3;
						
					m_phase_diago = 0;
					m_last_dir_v = 3;
					m_last_dir_h = 3;
				}			
				
			} else {
				dir_h = (h-1)*PROJ_SPEED;
				dir_v = (v-1)*PROJ_SPEED;
				m_phase_diago = 0;
				m_last_dir_v = v;
				m_last_dir_h = h;
			}
			proj = new Projectile(pos, h, v, dir_h, dir_v,1, m_proj_pics);
            m_projectiles_list->add(proj);
            break;
        case SHOTGUN:
            int x[5];
            int y[5];
            SDL_Rect pos2;
            SDL_Rect pos3;

            Projectile * proj[5];
            if((h-1)&&(v-1)) { /* le tir se fait en diagonale */
                x[0] = 3*PROJ_SPEED/4;
                x[1] = 7*PROJ_SPEED/8;
                x[2] = PROJ_SPEED;
                x[3] = PROJ_SPEED;
                x[4] = PROJ_SPEED;

                y[0] = PROJ_SPEED;
                y[1] = PROJ_SPEED;
                y[2] = PROJ_SPEED;
                y[3] = 7*PROJ_SPEED/8;
                y[4] = 3*PROJ_SPEED/4;
            }
            else if(h-1) { /* tir uniquement dans la dimention horizontale */
                for(int i = 0;i<5;i++) {
                    x[i] = PROJ_SPEED;
                }
                y[0] = /*3*PROJ_SPEED/10*/4;
                y[1] = /*3*PROJ_SPEED/20*/2;
                y[2] = 0;
                y[3] = /*-3*PROJ_SPEED/20*/2;
                y[4] = /*-3*PROJ_SPEED/10*/4;
            }
            else {  /* tir uniquement dans la dimension verticale */
                for(int i = 0;i<5;i++) {
                    y[i] = PROJ_SPEED;
                }
                x[0] = PROJ_SPEED/7;
                x[1] = PROJ_SPEED/14;
                x[2] = 0;
                x[3] = -PROJ_SPEED/14;
                x[4] = -PROJ_SPEED/7;
            }

            pos2.x = pos.x + 5*h;
            pos2.y = pos.y + 5*v;

            pos3.x = pos.x + 10*h;
            pos3.y = pos.y + 10*v;


            for(int i = 0;i<5;i++) {
                proj[i] = new Projectile(pos, h, v, (h-1)*x[i] + rand()%3-1, (v-1)*y[i] + rand()%3-1,1, m_proj_pics);
				m_projectiles_list->add(proj[i]);
            }
            for(int i = 0;i<5;i++) {
                proj[i] = new Projectile(pos2, h, v, (h-1)*x[i] + rand()%3-1, (v-1)*y[i] + rand()%3-1,1, m_proj_pics);
                m_projectiles_list->add(proj[i]);
            }
            for(int i = 0;i<5;i++) {
                proj[i] = new Projectile(pos3, h, v, (h-1)*x[i] + rand()%3-1, (v-1)*y[i] + rand()%3-1,1, m_proj_pics);
                m_projectiles_list->add(proj[i]);
            }

            break;
    }
	m_munitions --;
	if (m_munitions <= 0)
		change_weapon(GUN);

}

uint32_t Weapon::reload_time()
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

int Weapon::munitions()
{
	return m_munitions;
}

weapon_type Weapon::type_of_weapon()
{
	return m_weapon_type;
}
