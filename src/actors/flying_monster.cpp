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

#include "flying_monster.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "babar.h"


Flying_monster::Flying_monster() {}

Flying_monster::Flying_monster(Analyser *analyserLevel) : Monster()
{
	m_nom = analyserLevel->read_string();

	// donnees contenues dans le level
	m_pos.x = analyserLevel->read_int();
	m_pos.y = analyserLevel->read_int();
	m_high_min = 2800;

	initFromMonsterFile(m_nom);



}

Flying_monster::~Flying_monster()
{

}

