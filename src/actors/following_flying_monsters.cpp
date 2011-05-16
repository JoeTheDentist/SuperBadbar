/**
 * 	@file flying_monster.cpp
 * 	@brief Source de la classe Flying_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>
#include <stdint.h>

#include "following_flying_monsters.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "babar.h"
#include "../players/players_manager.h"

Following_flying_monster::Following_flying_monster(std::string name, int posx, int posy):
	Flying_monster(name, posx, posy)
{
}

Following_flying_monster::Following_flying_monster(Analyser *analyserLevel):
	Flying_monster(analyserLevel)
{

}

Following_flying_monster::~Following_flying_monster()
{

}


void Following_flying_monster::update_speed_simple()
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

