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


Flying_monster::Flying_monster(std::string name, int posx, int posy):
	Monster(name, posx, posy)
{
}

Flying_monster::Flying_monster(Analyser *analyserLevel) : 
	Monster(analyserLevel)
{
	m_high_min = 2800;
}

Flying_monster::~Flying_monster()
{

}

