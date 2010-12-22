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
#include "../video/pictures_container.h"

/**************************
**  Méthodes projectiles **
**************************/

Projectile::Projectile(Rect pos, horizontal h, uint32_t speedx, uint32_t speedy, uint32_t damage, Pictures_container *pictures_container)
{
	PRINT_CONSTR(3, "Construction d'un projectile")
    m_pos = pos;
    m_dir = h;
    m_damage = damage;
	std::string rep = PIC_PROJ_R;


    m_animt = new Anim_table(rep+"simple/simple");

    /*** Remplissage des images des projectiles (voir static_data.ccp) ***/
    /*if((h == LEFT)||(h == RIGHT)) {
        m_pic = pictures_container->load_BMP((rep + "left-right.bmp").c_str());
    } else {
        m_pic = pictures_container->load_BMP((rep + "up-down.bmp").c_str());;
    }
    m_pos.h = m_pic->h;
    m_pos.w = m_pic->w;*/

    m_animt->setRect(m_pos);

    m_speed.x = speedx;
    m_speed.y = speedy;

	m_dead = false;
	m_phase = 0;
}

Projectile::Projectile(Rect pos, horizontal h, uint32_t speedx, uint32_t speedy, uint32_t damage, SDL_Surface **pics)
{
	PRINT_CONSTR(3, "Construction d'un projectile")
    m_pos = pos;
    m_dir = h;
    m_damage = damage;

    std::string rep = PIC_PROJ_R;

    m_animt = new Anim_table(rep+"simple/simple");

    /*** Remplissage des images des projectiles (voir static_data.ccp) ***/
    /*if((h == LEFT)||(h == RIGHT)) {
        m_pic = pics[0];
    } else {
        m_pic = pics[1];
    }

    m_pos.h = m_pic->h;
    m_pos.w = m_pic->w;*/

    m_animt->setRect(m_pos);

    m_speed.x = speedx;
    m_speed.y = speedy;

	m_dead = false;
	m_phase = 0;
}

void Projectile::update_pos(Collisions_manager *collisions_manager)
{
	m_phase++;
	uint32_t coll;
	/* cas où le sprite descend */
	for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		coll = collisions_manager->down_collision_type(m_pos);
		if (Collisions_manager::is_down_coll(coll)){
			m_dead = true;
		}
		else {
			m_pos.y += BOX_SIZE;
		}
	}
	/* cas où le sprite monte */
	for (int32_t speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		if (Collisions_manager::is_up_coll(collisions_manager->up_collision_type(m_pos))){
			m_dead = true;
		}

	}
	/* cas où le sprite va à droite */
	for (int32_t speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
			m_pos.y -= 	BOX_SIZE;
			if(!Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos))) {
				m_pos.y += BOX_SIZE;
			} else {
				m_dead = true;
			}
			m_pos.x += BOX_SIZE;
	}
	/* cas où le sprite va à gauche */
	for (int32_t speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
			m_pos.y -= 	BOX_SIZE;
			if(!Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos))) {
				m_pos.y += BOX_SIZE;
			} else {
				m_dead = true;
			}
			m_pos.x -= BOX_SIZE;
	}
	if (m_phase >= PROJ_LIFE_SPAN)
		m_dead = true;
}


Projectile::~Projectile()
{
	PRINT_CONSTR(3, "Destruction d'un projectile")
}

SDL_Surface *Projectile::current_picture() const
{
    m_animt->change_anim(STATIC, m_dir);
    return m_animt->curr_pic();
}

uint32_t Projectile::damage() const
{
    return m_damage;
}

Rect Projectile::speed() const
{
    return m_speed;
}

bool Projectile::dead() const {
	return m_dead;
}

void Projectile::kill() {
	m_dead = true;
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

