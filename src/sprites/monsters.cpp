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
#include "../video/animation_engine.h"
#include "../sprites/projectiles.h"
#include "../items/weapons.h"
#include "babar.h"
#include <stdlib.h>




/*********************************
**	Méthodes de Monster	**
**********************************/

Monster::Monster():
	m_weapon(NULL)
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
	if ( dist(m_pos, gBabar->position()) > SWITCH_DIST ) {
	    update_speed_simple();
	} else {
	    update_speed_ai();
	}
}

void Monster::update_speed_simple()
{
    if ( gCollision->can_fall(m_pos) ) {
        m_speed.x *= -1;
        if ( m_dir == LEFT ) {
            m_dir = RIGHT;
        } else {
            m_dir = LEFT;
        }
        m_pos.y -= 3*BOX_SIZE;
    }
    m_speed.y += GRAVITE;
}

void Monster::update_speed_ai()
{
    update_speed_simple();
}

void Monster::damage(uint32_t damage)
{
    m_life -= damage;
	prepare_sound(MONSTERS_SOUNDS_R + "death.wav");

}

void Monster::update()
{
	
}

bool Monster::dead() const
{
    if ( m_life <= 0 ) {
        gAnims->add(PIC_MONSTERS_R+m_nom+"/death/"+m_nom+"_"+(char)(m_dir+'0')+"_", m_pos, NOEND, m_speed, true);
        return true;
    }
    return false;
}

std::list<Projectile*> *Monster::fire()
{
	if (m_weapon && (rand() % 10 == 0)) {
		/* Calcul de la position de la source du tir */
		Rect fire_pos = m_pos;
		if ( m_dir == RIGHT ) {
			fire_pos.x += m_pos.w;
		}
		return m_weapon->fire(fire_pos,m_dir);
	} else {
		return new std::list<Projectile*>();
	}
}

