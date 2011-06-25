/**
 * 	@file FlyingMonster.cpp
 * 	@brief Source de la classe FlyingMonster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>
#include <stdint.h>

#include "following_FlyingMonsters.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "babar.h"
#include "../players/players_manager.h"

Following_FlyingMonster::Following_FlyingMonster(std::string name, int posx, int posy):
	FlyingMonster(name, posx, posy)
{
}

Following_FlyingMonster::Following_FlyingMonster(Analyser *analyserLevel):
	FlyingMonster(analyserLevel)
{

}

Following_FlyingMonster::~Following_FlyingMonster()
{

}


void Following_FlyingMonster::update_speed_simple()
{
	if ( (m_pos.x<gPlayers->local_player()->position().x)&&(m_dir != RIGHT) ) {
	    m_dir = RIGHT;
		m_speed.x = m_speed_def;
	}
	if ( (m_pos.x>gPlayers->local_player()->position().x)&&(m_dir != LEFT) ) {
	    m_dir = LEFT;
	    m_speed.x = -m_speed_def;
	}

	if ( (m_pos.y<gPlayers->local_player()->position().y) ) {
		m_speed.y = m_speed_def;
	}
	if ( (m_pos.y>gPlayers->local_player()->position().y) ) {
	    m_speed.y = -m_speed_def;
	}
}

