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
#include "../util/globals.h"
#include "../game/static_data.h"
#include "../physic/collisions_manager.h"
#include "../video/surface.h"


/*********************************
**	Méthodes de Actor 	**
**********************************/
Actor::Actor()
{
	m_sprite = NULL;
	m_speed = m_pos;
	m_dir = LEFT;
	m_phase = 0;
}

Actor::~Actor()
{
	PRINT_CONSTR(3, "destruction de actor")
	if ( m_sprite ) {
        m_sprite->set_to_delete();
        m_sprite = NULL;
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

Rect Actor::center() const
{
	Rect res;
	res.x = position().x + position().w / 2;
	res.y = position().y + position().h / 2;
	return res;
}

void Actor::move(int x, int y)
{
	m_pos.x += x;
	m_pos.y += y;
}

void Actor::set_pos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void Actor::do_stay_in_level()
{
	if (position().x < 0)
		set_pos(0, position().y);
	if (position().x + position().w> (int)gStatic->static_data_width())
		set_pos(gStatic->static_data_width() - position().w, position().y);
	if (position().y < 0)
		set_pos(position().x, 0);
	if (position().y > (int)gStatic->static_data_height())
		set_pos(position().x, gStatic->static_data_height());
}
