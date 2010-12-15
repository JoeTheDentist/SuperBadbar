/**
 * 	@file projectiles.cpp
 * 	@brief Implémentation de la classe Projectile
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "projectiles.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../game/static_data.h"
#include "../game/collisions_manager.h"

#include "../util/collisions.h"

/**************************
**  Méthodes projectiles **
**************************/

Projectile::Projectile(Rect pos, horizontal h, uint32_t speedx, uint32_t speedy, uint32_t damage, SDL_Surface **pics)
{
	PRINT_CONSTR(3, "Construction d'un projectile")
    m_pos = pos;
    m_horizontal = h;
    m_damage = damage;

    /*** Remplissage des images des projectiles (voir static_data.ccp) ***/
    if((h == LEFT)||(h == RIGHT)) {
        m_pic = pics[0];
    } else {
        m_pic = pics[1];
    }

    m_pos.h = m_pic->h;
    m_pos.w = m_pic->w;

    m_speed.x = speedx;
    m_speed.y = speedy;
}

void Projectile::update_pos(Static_data *static_data,  Collisions_manager *collisions_manager)
{
	m_phase++;
	uint32_t coll;
	/* cas où le sprite descend */
	for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		coll = collisions_manager->down_collision_type(m_pos);
		if (is_down_coll(coll)){
			speed_y = 0;
			m_speed.y = 0;
			m_phase = PROJ_LIFE_SPAN;
		}
		else {
			m_pos.y += BOX_SIZE;
			if (m_pos.y + m_pos.h > (int32_t)static_data->static_data_height())
				m_pos.y = static_data->static_data_height() - m_pos.h;
		}
	}
	/* cas où le sprite monte */
	for (int32_t speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		if (is_up_coll(collisions_manager->up_collision_type(m_pos))){
			speed_y = 0;
			m_speed.y = 0;
			m_phase = PROJ_LIFE_SPAN;

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
			if(!is_down_coll(collisions_manager->down_collision_type(m_pos))) {
				m_pos.y += BOX_SIZE;
				m_phase = PROJ_LIFE_SPAN;
			}
			m_pos.x += BOX_SIZE;
			if (m_pos.x + m_pos.w > (int32_t)static_data->static_data_weight())
				m_pos.x = static_data->static_data_weight() - m_pos.w;
	}
	/* cas où le sprite va à gauche */
	for (int32_t speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
			m_pos.y -= 	BOX_SIZE;
			if(!is_down_coll(collisions_manager->down_collision_type(m_pos))) {
				m_pos.y += BOX_SIZE;
				m_phase = PROJ_LIFE_SPAN;
			}
			m_pos.x -= BOX_SIZE;
			if (m_pos.x < 0)
				m_pos.x = 0;
	}

}


Projectile::~Projectile()
{
	PRINT_CONSTR(3, "Destruction d'un projectile")
}

SDL_Surface *Projectile::current_picture() const
{
    return m_pic;
}





uint32_t Projectile::damage() const
{
    return m_damage;
}

Rect Projectile::speed() const
{
    return m_speed;
}


/*** Fonctions ***/

bool too_old(Projectile * p, Collisions_manager *collisions_manager)
{
    bool to_return = (p->phase()>PROJ_LIFE_SPAN);
    Rect speed = p->speed();
    if (speed.x>0)
        to_return |= collisions_manager->right_collision(p->position());
    else
        to_return |= collisions_manager->left_collision(p->position());

    if (speed.y>0)
        to_return |= collisions_manager->down_collision(p->position());
    else
        to_return |= collisions_manager->up_collision(p->position());
    return to_return;
}

