/**
 * 	@file monsters.cpp
 * 	@brief Implémentation de la classe Monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "monsters.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../video/surface.h"




/*********************************
**	Méthodes de Monster	**
**********************************/

Monster::Monster()
{
    m_state = WALKING;
    m_fire = false;
}

Monster::~Monster()
{
	PRINT_CONSTR(3, "destruction d'un monstre")
}

Surface *Monster::current_picture() const
{
    m_animt->change_anim(m_state, m_dir, m_fire, true);
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

void Monster::damage(uint32_t damage)
{
    m_life -= damage;
	prepare_sound(MONSTERS_SOUNDS_R + "kickass" + SOUNDS_EXT);

}

bool Monster::dead() const
{
    return (m_life <= 0);
}
