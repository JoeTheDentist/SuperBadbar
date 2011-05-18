/**
 * 	@file charging_monster.cpp
 * 	@brief Implementation de la classe Charging_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mai 2011
 *
 */
#include <iostream>
#include <stdint.h>

#include "charging_monster.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../items/gun.h"
#include "../items/monster_basic_weapon.h"
#include "babar.h"
#include "../AI/AI.h"


Charging_monster::Charging_monster(std::string name, int posx, int posy):
	Walking_monster(name, posx, posy)
{
    m_ai = new AI(&m_pos);
}

Charging_monster::Charging_monster(Analyser *analyserLevel):
	Walking_monster(analyserLevel)
{
    m_ai = new AI(&m_pos);
}

Charging_monster::~Charging_monster()
{
    delete m_ai;
}

void Charging_monster::update_speed_ai()
{
    direction d = m_ai->dir();
    m_state = WALKING;

    switch ( d ) {
        case LEFT:
            m_dir = LEFT;
            m_speed.x = -m_speed_def;
            break;
        case RIGHT:
            m_dir = RIGHT;
            m_speed.x = m_speed_def;
            break;
        case UP:
            /* pour ne pas avoir de vitesse trop rapides */
            if ( m_speed.y >= 0 ) {
                m_speed.y -= 70;
            }
            break;
        case DOWN:
            m_pos.y += 10;
            break;
        case NOPE:
            /* où le monstre ne doit rien faire => state = WAIT */
            m_state = WAIT;
            break;
    }
	m_speed.y += GRAVITE;


}




