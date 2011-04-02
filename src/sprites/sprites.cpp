/**
 * 	@file sprites.cpp
 * 	@brief Implémentation de la classe Sprite
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <stdint.h>

#include "sprites.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../game/static_data.h"
#include "../physic/collisions_manager.h"
#include "../video/surface.h"


/*********************************
**	Méthodes de Sprite 	**
**********************************/
Sprite::Sprite()
{
	m_animt = NULL;
	m_speed.x = 0;
	m_speed.y = 0;
	m_dir = LEFT;
	m_phase = 0;
}

Sprite::~Sprite()
{
	PRINT_CONSTR(3, "destruction de sprite")
	if (m_animt)
		delete m_animt;
}

Surface *Sprite::current_picture()  const
{
	return NULL;
}

void Sprite::update_pos()
{
	m_phase++;

	gCollision->update_pos(m_pos, m_speed);
}


Rect Sprite::position() const
{
	return m_pos;
}


Rect Sprite::damage_box() const
{
	Rect box = this->position();
	box.x += box.w / DAMAGE_BOX_RATIO;
	box.y += box.h / DAMAGE_BOX_RATIO;
	box.w *= (DAMAGE_BOX_RATIO - 2); box.w /= DAMAGE_BOX_RATIO;
	box.h *= (DAMAGE_BOX_RATIO - 2); box.h /= DAMAGE_BOX_RATIO;
	return box;
}


uint32_t Sprite::position_x() const
{
	return position().x;
}

uint32_t Sprite::position_y() const
{
	return position().y;
}

uint32_t Sprite::phase() const
{
    return m_phase;
}

int Sprite::direction_h() const
{
	if (m_dir == RIGHT)
		return 1;
	else
		return -1;
}

direction Sprite::dir() const
{
    return m_dir;
}
