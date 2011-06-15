/**
 * 	@file boss.cpp
 * 	@brief Implementation de la classe Boss_elmer
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mai 2011
 *
 */
#include <iostream>
#include <stdint.h>
#include <cmath>

#include "boss_elmer.h"
#include "../video/surface.h"
#include "../actors/babar.h"
#include "../items/elmar_machine_gun.h"

Boss_elmer::Boss_elmer(std::string name, int posx, int posy):
	Boss(name, posx, posy)
{
    m_weapon = new Elmar_machine_gun();
}

Boss_elmer::Boss_elmer(Analyser *analyserLevel):
	Boss(analyserLevel)
{
}

Boss_elmer::~Boss_elmer()
{
}

void Boss_elmer::update_speed_simple()
{
    if ( gCollision->get_matrix()->can_fall(m_pos) ) {
        m_speed.x *= -1;
        if ( m_dir == LEFT ) {
            m_dir = RIGHT;
        } else {
            m_dir = LEFT;
        }
        m_pos.y -= 3*BOX_SIZE;
    }
    m_speed.y += GRAVITE;
    m_sprite->set_pos(m_pos);
    m_sprite->change_anim(m_state,m_dir);
}

void Boss_elmer::update_speed_ia()
{
    if ( gCollision->get_matrix()->can_fall(m_pos) ) {
        m_speed.x *= -1;
        if ( m_dir == LEFT ) {
            m_dir = RIGHT;
        } else {
            m_dir = LEFT;
        }
        m_pos.y -= 3*BOX_SIZE;
    }
    m_speed.y += GRAVITE;
    m_sprite->set_pos(m_pos);
    m_sprite->change_anim(m_state,m_dir);
}


void Boss_elmer::update()
{
	Rect babarpos = gPlayers->closer_babar(position())->position();
}


