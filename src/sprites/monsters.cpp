/**
 * 	@file monsters.h
 * 	@brief Implémentation de la classe Monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "monsters.h"
#include "../util/debug.h"
#include "../game/game.h"




/*********************************
**	Méthodes de Monster	**
**********************************/

Monster::Monster(Sound_manager *sound_manager) {
	m_sound_manager = sound_manager;
}

Monster::~Monster()
{
	PRINT_CONSTR(3, "destruction d'un monstre")
}

SDL_Surface *Monster::current_picture() const
{
    /* pour le moment, un seul état... */
    m_animt->change_anim(STATIC, m_dir);
    return m_animt->curr_pic();
}

void Monster::update_speed()
{
	m_speed.y += GRAVITE;

	if (m_pos.x<m_area_begin) {
	    m_dir = RIGHT;
		m_speed.x = -m_speed.x;
	}
	if (m_pos.x>m_area_end) {
	    m_dir = LEFT;
	    m_speed.x = -m_speed.x;
	}
}

void Monster::update_speed(Babar * babar)
{
	m_speed.y += GRAVITE;

	if (m_pos.x<m_area_begin) {
	    m_dir = RIGHT;
		m_speed.x = -m_speed.x;
	}
	if (m_pos.x>m_area_end) {
	    m_dir = LEFT;
	    m_speed.x = -m_speed.x;
	}
}

void Monster::damage(uint32_t damage)
{
	m_sound_manager->play_monster_damage();
    m_life -= damage;
}

bool Monster::dead() const
{
    return (m_life <= 0);
}
