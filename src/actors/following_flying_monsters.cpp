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


Following_flying_monster::Following_flying_monster(Analyser *analyserLevel)
{
    PRINT_CONSTR(1, "                               Construction d'un following_flying_monster")
	m_nom = analyserLevel->read_string();

	// donnees contenues dans le level
	m_pos.x = analyserLevel->read_int();
	m_pos.y = analyserLevel->read_int();

	initFromMonsterFile(m_nom);

}

Following_flying_monster::~Following_flying_monster()
{

}


void Following_flying_monster::update_speed_simple()
{
	if ( (m_pos.x<gBabar->position().x)&&(m_dir != RIGHT) ) {
	    m_dir = RIGHT;
		m_speed.x = m_speed_def;
	}
	if ( (m_pos.x>gBabar->position().x)&&(m_dir != LEFT) ) {
	    m_dir = LEFT;
	    m_speed.x = -m_speed_def;
	}

	if ( (m_pos.y<gBabar->position().y) ) {
		m_speed.y = m_speed_def;
	}
	if ( (m_pos.y>gBabar->position().y) ) {
	    m_speed.y = -m_speed_def;
	}
}

