/**
 * 	@file sprites.cpp
 * 	@brief Implémentation de la classe Sprite
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "sprites.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../game/static_data.h"
#include "../game/collisions_manager.h"

/*********************************
**	Méthodes de Sprite 	**
**********************************/
Sprite::Sprite()
{
	m_speed.x = 0;
	m_speed.y = 0;
	m_dir = LEFT;
	m_state = WALK;
	m_phase = 0;
}

Sprite::~Sprite()
{
    m_animt->~Anim_table();
}

SDL_Surface *Sprite::current_picture()  const
{
	return NULL;
}

void Sprite::update_pos(Static_data *static_data, Collisions_manager *collisions_manager)
{
	m_phase++;
	uint32_t coll;
	/* cas où le sprite descend */
	for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		coll = collisions_manager->down_collision_type(m_pos);
		if (Collisions_manager::is_down_coll(coll)){
			speed_y = 0;
			m_speed.y = 0;
			if (m_state == JUMP)
				m_state = STATIC;
		}
		else {
			m_pos.y += BOX_SIZE;
			if (m_pos.y + m_pos.h > (int32_t)static_data->static_data_height())
				m_pos.y = static_data->static_data_height() - m_pos.h;
		}
	}
	/* cas où le sprite monte */
	for (int32_t speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		if (Collisions_manager::is_up_coll(collisions_manager->up_collision_type(m_pos))){
			speed_y = 0;
			m_speed.y = 0;
		}
		else {
			if (m_pos.y < 0)
				m_pos.y = 0;
			m_pos.y -= BOX_SIZE;
		}
	}
	/* cas où le sprite va à droite */
	for (int32_t speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
			m_pos.y -= 	BOX_SIZE;
			if(!Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos)))
				m_pos.y += BOX_SIZE;
			m_pos.x += BOX_SIZE;
			if (m_pos.x + m_pos.w > (int32_t)static_data->static_data_weight())
				m_pos.x = static_data->static_data_weight() - m_pos.w;
	}
	/* cas où le sprite va à gauche */
	for (int32_t speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
			m_pos.y -= 	BOX_SIZE;
			if(!Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos)))
				m_pos.y += BOX_SIZE;
			m_pos.x -= BOX_SIZE;
			if (m_pos.x < 0)
				m_pos.x = 0;
	}


}


Rect Sprite::position() const
{
	return m_pos;
}

uint32_t Sprite::position_x() const
{
	return m_pos.x;
}

uint32_t Sprite::position_y() const
{
	return m_pos.y;
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


