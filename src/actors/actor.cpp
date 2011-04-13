/**
 * 	@file sprites.cpp
 * 	@brief Implémentation de la classe Actor
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <stdint.h>

#include "actor.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../game/static_data.h"
#include "../physic/collisions_manager.h"
#include "../video/surface.h"


/*********************************
**	Méthodes de Actor 	**
**********************************/
Actor::Actor()
{
	m_sprite = NULL;
	m_pos = {0};
	m_speed = {0};
	m_dir = LEFT;
	m_phase = 0;
}

Actor::~Actor()
{
	PRINT_CONSTR(3, "destruction de actor")
	if ( m_sprite ) {
        m_sprite->set_to_delete();
    }
}

void Actor::update_pos()
{
	m_phase++;
	gCollision->get_matrix()->update_pos(m_pos, m_speed);
}

Rect Actor::position() const
{
	return m_pos;
}

Rect Actor::damage_box() const
{
	Rect box = this->position();
	box.x += box.w / DAMAGE_BOX_RATIO;
	box.y += box.h / DAMAGE_BOX_RATIO;
	box.w *= (DAMAGE_BOX_RATIO - 2); box.w /= DAMAGE_BOX_RATIO;
	box.h *= (DAMAGE_BOX_RATIO - 2); box.h /= DAMAGE_BOX_RATIO;
	return box;
}

int Actor::phase() const
{
    return m_phase;
}

int Actor::direction_h() const
{
	if (m_dir == RIGHT)
		return 1;
	else
		return -1;
}

direction Actor::dir() const
{
    return m_dir;
}
