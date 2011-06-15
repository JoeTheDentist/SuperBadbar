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
    m_fire = 0;
    m_elmar_state = ELMAR_CHARGE;
    m_speed.x = 10;
}

Boss_elmer::Boss_elmer(Analyser *analyserLevel):
	Boss(analyserLevel)
{
    m_weapon = new Elmar_machine_gun();
    m_fire = 0;
    m_elmar_state = ELMAR_CHARGE;
    m_speed.x = 10;
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
}


void Boss_elmer::update()
{
    // mise à jour des dimensions
    m_sprite->set_pos(m_pos);
    m_sprite->change_anim(m_state,m_dir);
    m_pos.w = m_sprite->w();
    m_pos.h = m_sprite->h();

    // mise à jour du joueur ciblé
	Rect babarpos = gPlayers->closer_babar(position())->position();

	// mise à jour de l'arme
	if ( m_weapon ) {
	    if ( m_weapon->munitions() > 0) {
            gProj->add_proj(fire(), MONSTERS);
	    } else {
	        m_weapon->add_munitions();
	    }
	}

	// comprotement d'Elmar
	// De façon générale Elmar se met dans les coins et en fonction
	// de la position de Babar saute ou non
	if ( m_elmar_state == ELMAR_CHARGE ) {
        // on regarde si Elmar est arrivé dans un coin
        if ( m_pos.x < m_pos.w/2 && m_dir == LEFT ) {
            m_dir = RIGHT;
            m_speed.x *= -1;
        } else if ( m_pos.x + (3*m_pos.w)/2 > 2*gStatic->background()->w() - 800 && m_dir == RIGHT ) {
            m_dir = LEFT;
            m_speed.x *= -1;
        }
	}
}


