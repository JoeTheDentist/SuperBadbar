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
#include <stdlib.h>

#include "boss_elmer.h"
#include "../video/surface.h"
#include "../actors/babar.h"
#include "../items/elmar_machine_gun.h"

Boss_elmer::Boss_elmer(std::string name, int posx, int posy):
	Boss(name, posx, posy)
{
    m_weapon = new Elmar_machine_gun();
    m_fire = 0;
    m_elmar_state = ELMAR_FIRE;
    m_dir = RIGHT;
    m_speed.x = 0;
}

Boss_elmer::Boss_elmer(Analyser *analyserLevel):
	Boss(analyserLevel)
{
    m_weapon = new Elmar_machine_gun();
    m_fire = 0;
    m_elmar_state = ELMAR_FIRE;
    m_dir = RIGHT;
    m_speed.x = 0;
}

Boss_elmer::~Boss_elmer()
{
}

void Boss_elmer::update_speed_simple()
{
    /*if ( gCollision->get_matrix()->can_fall(m_pos) ) {
        m_speed.x *= -1;
        if ( m_dir == LEFT ) {
            m_dir = RIGHT;
        } else {
            m_dir = LEFT;
        }
        m_pos.y -= 3*BOX_SIZE;
    }*/
    m_speed.y += GRAVITE;
}

void Boss_elmer::update_speed_ia()
{
    /*if ( gCollision->get_matrix()->can_fall(m_pos) ) {
        m_speed.x *= -1;
        if ( m_dir == LEFT ) {
            m_dir = RIGHT;
        } else {
            m_dir = LEFT;
        }
        m_pos.y -= 3*BOX_SIZE;
    }*/
    m_speed.y += GRAVITE;
}


void Boss_elmer::update()
{
    update_state();

	// mise à jour des dimensions
	Rect pos_basse = m_pos;
	pos_basse.y += pos_basse.h;
	//pour toujours avoir la mm position malgré le changement d'état
	m_sprite->change_anim(m_elmar_state,m_dir);
    m_pos.w = m_sprite->w();
    m_pos.h = m_sprite->h();
    m_pos.y = pos_basse.y - m_pos.h;
    m_sprite->set_pos(m_pos);
}

bool Boss_elmer::bottom()
{
    return ( m_pos.y + 4*m_pos.h > 2*gStatic->background()->h() - 600 );
}

bool Boss_elmer::top()
{
    return ( m_pos.y + 4*m_pos.h < 2*gStatic->background()->h() - 600 );
}

bool Boss_elmer::in_bottom_left_corner()
{
    return  ( m_pos.x < m_pos.w/2 ) &&
            bottom();
}

bool Boss_elmer::in_bottom_right_corner()
{
    return  ( m_pos.x + (3*m_pos.w)/2 > 2*gStatic->background()->w() - 800 ) &&
            bottom();
}

bool Boss_elmer::in_top_left_corner()
{
    return  ( m_pos.x < m_pos.w/2 ) &&
            top();
}

bool Boss_elmer::in_top_right_corner()
{
    return  ( m_pos.x + (3*m_pos.w)/2 > 2*gStatic->background()->w() - 800 ) &&
            top();
}

bool Boss_elmer::in_bottom_middle()
{
    return ( m_pos.x + 30 > gStatic->background()->w() - 400 &&
             m_pos.x - 30 < gStatic->background()->w() - 400 );
}

void Boss_elmer::update_state()
{
	// comprotement d'Elmar
	// De façon générale Elmar se met dans les coins et en fonction
	// de la position de Babar saute ou non
	switch ( m_elmar_state ) {
	    case ELMAR_CHARGE :
            elmar_charge();
            break;
	    case ELMAR_FIRE :
            elmar_fire();
            break;
        case ELMAR_JUMP :
            elmar_jump();
            break;
        default:
            break;
	}
}

void Boss_elmer::elmar_charge()
{
    Rect babarpos = gPlayers->closer_babar(position())->position();

    // on regarde si Elmar est arrivé dans un coin
    if ( ( in_bottom_left_corner() || in_top_left_corner() ) && m_dir == LEFT ) {
        m_dir = RIGHT;
        m_speed.x = 0;
        m_elmar_state = ELMAR_FIRE;
        m_fire = rand()%10+5;
    } else if ( ( in_bottom_right_corner() || in_top_right_corner() ) && m_dir == RIGHT ) {
        m_dir = LEFT;
        m_speed.x = 0;
        m_fire = rand()%10+5;
        m_elmar_state = ELMAR_FIRE;
    } else if ( in_bottom_middle() ) {
        if ( (rand()%5 == 0) && babarpos.y > m_pos.y - m_pos.h ) {
            if ( babarpos.x > m_pos.x ) {
                m_dir = RIGHT;
            } else {
                m_dir = LEFT;
            }
            m_speed.x = 0;
            m_fire = rand()%10+5;
            m_elmar_state = ELMAR_FIRE;
        }
    }
}

void Boss_elmer::elmar_fire()
{
    Rect babarpos = gPlayers->closer_babar(position())->position();

    if ( m_phase%2 ) {
        // pour eviter de tirer trop vite
        if ( m_fire ) {
            // temps de tir
            if ( m_weapon->munitions() == 0) {
                m_weapon->add_munitions();
            }
            gProj->add_proj(fire(), MONSTERS);
            --m_fire;
        } else {
            // qd on a fini de tirer
            if ( babarpos.y < m_pos.y ) {
                // si le joueur est sur une plateforme au dessus
                // on saute si on est bien pas au millieu ni en haut
                if ( in_bottom_left_corner() ) {
                    m_elmar_state = ELMAR_JUMP;
                    m_dir = RIGHT;
                    m_speed.y = -80;
                } else if ( in_bottom_right_corner() ) {
                    m_elmar_state = ELMAR_JUMP;
                    m_dir = LEFT;
                    m_speed.y = -80;
                }
            } else {
                // sinon on le charge
                m_elmar_state = ELMAR_CHARGE;
                m_speed.x = 30;
                if ( m_dir == LEFT ) {
                    m_speed.x *= -1;
                }
            }
        }
    }
}

void Boss_elmer::elmar_jump()
{
    Rect babarpos = gPlayers->closer_babar(position())->position();
    if ( m_speed.y == 0 || !gCollision->get_matrix()->can_fall(m_pos) ) {
        m_elmar_state = ELMAR_CHARGE;
        m_speed.x = 30;
        if ( m_dir == LEFT ) {
            m_speed.x *= -1;
        }
    }
}
