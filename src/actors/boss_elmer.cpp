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


Boss_elmer::Boss_elmer(std::string name, int posx, int posy):
	Boss(name, posx, posy)
{

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
	m_speed.y += GRAVITE;
}


void Boss_elmer::update()
{
	Rect babarpos = gPlayers->closer_babar(position())->position();
}


