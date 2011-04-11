/**
 * 	@file shotgun.cpp
 * 	@brief Implémentation de la classe Shotgun
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>
#include <stdlib.h>


#include "shotgun.h"
#include "../util/debug.h"
#include "../actors/projectiles.h"
#include "../util/globals.h"
#include "../util/repertories.h"



Shotgun::Shotgun()
{
	PRINT_CONSTR(2, "Construction d'un Shotgun")
	m_last_dir_h = 3;
    m_weapon_type = SHOTGUN;
	m_reload_time = RELOAD_SHOTGUN;
	m_munitions = MUN_SHOTGUN;
}

Shotgun::~Shotgun()
{
	PRINT_CONSTR(2, "Destruction d'une Shotgun")
}

std::list<Projectile*> *Shotgun::fire(Rect pos, direction h)
{
	std::list<Projectile*> *proj_list = new std::list<Projectile*>();
	if (m_munitions >= 0) {
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
			proj[i] = new Projectile(pos, h, (2*h-1)*x[i] + rand()%3-1, rand()%3-1,1);
			proj_list->push_back(proj[i]);
		}
		for(int i = 0;i<5;i++) {
			proj[i] = new Projectile(pos2, h, (2*h-1)*x[i] + rand()%3-1, rand()%3-1,1);
			proj_list->push_back(proj[i]);
		}
		for(int i = 0;i<5;i++) {
			proj[i] = new Projectile(pos3, h, (2*h-1)*x[i] + rand()%3-1, rand()%3-1,1);
			proj_list->push_back(proj[i]);
		}
		m_munitions --;
	}
	gSound->play_sound(FIRE_SOUNDS_R + "shotgun.wav");
	return proj_list;
}


weapon_type Shotgun::type_of_weapon() const
{
	return SHOTGUN;
}


void Shotgun::add_munitions()
{
	m_munitions += MUN_SHOTGUN;
	if (m_munitions > MUN_SHOTGUN * 2)
		m_munitions = MUN_SHOTGUN * 2;
}

