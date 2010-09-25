#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "projectiles.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../game/static_data.h"

#include "../util/collisions.h"

/**************************
**  Méthodes projectiles **
**************************/

Projectile::Projectile()
{
	PRINT_CONSTR(3, "Construction d'un projectile")
}

Projectile::Projectile(SDL_Rect pos, horizontal h, vertical v, uint32_t speedx, uint32_t speedy, uint32_t damage, SDL_Surface **pics)
{
	PRINT_CONSTR(3, "Construction d'un projectile")
    m_pos = pos;
    m_horizontal = h;
    m_vertical = v;
    m_damage = damage;

    /*** Remplissage des images des projectiles (voir static_data.ccp) ***/
    if(((h == LEFT)&&(v == UP))||((h == RIGHT)&&(v == DOWN))) {
        m_pic = pics[2];
    }
    if(((h == LEFT)&&(v == MIDDLE_v))||((h == RIGHT)&&(v == MIDDLE_v))) {
        m_pic = pics[0];
    }
    if(((h == LEFT)&&(v == DOWN))||((h == RIGHT)&&(v == UP))) {
        m_pic = pics[3];
    }
    if(((h == MIDDLE_h)&&(v == UP))||((h == MIDDLE_h)&&(v == DOWN))) {
        m_pic = pics[1];
    }

    m_pos.h = m_pic->h;
    m_pos.w = m_pic->w;

    m_speed.x = speedx;
    m_speed.y = speedy;
}

void Projectile::update_pos(Static_data *static_data)
{
	m_phase++;
	uint32_t coll;
	/* cas où le sprite descend */
	for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		coll = static_data->down_collision_type(m_pos);
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
		if (is_up_coll(static_data->up_collision_type(m_pos))){
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
			if(!is_down_coll(static_data->down_collision_type(m_pos))) {
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
			if(!is_down_coll(static_data->down_collision_type(m_pos))) {
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

SDL_Surface *Projectile::current_picture()
{
    return m_pic;
}





uint32_t Projectile::damage()
{
    return m_damage;
}

SDL_Rect Projectile::speed()
{
    return m_speed;
}


/*** Fonctions ***/

bool too_old(Projectile * p, Static_data *static_data)
{
    bool to_return = (p->phase()>PROJ_LIFE_SPAN);
    SDL_Rect speed = p->speed();
    if (speed.x>0)
        to_return |= static_data->right_collision(p->position());
    else
        to_return |= static_data->left_collision(p->position());

    if (speed.y>0)
        to_return |= static_data->down_collision(p->position());
    else
        to_return |= static_data->up_collision(p->position());
    return to_return;
}

