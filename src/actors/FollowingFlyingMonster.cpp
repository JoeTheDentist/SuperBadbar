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

#include "FollowingFlyingMonster.h"
#include "../util/debug.h"
#include "../util/Analyser.h"
#include "Babar.h"
#include "../players/PlayersManager.h"

FollowingFlyingMonster::FollowingFlyingMonster(std::string name, int posx, int posy):
	FlyingMonster(name, posx, posy)
{
    PRINT_CONSTR(2, "Construction de FollowingFlyingMonster");
}

FollowingFlyingMonster::FollowingFlyingMonster(Analyser *analyserLevel):
	FlyingMonster(analyserLevel)
{
    PRINT_CONSTR(2, "Construction de FollowingFlyingMonster");
}

FollowingFlyingMonster::~FollowingFlyingMonster()
{
    PRINT_CONSTR(2, "Destruction de FollowingFlyingMonster");
}


void FollowingFlyingMonster::update_speed_simple()
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

