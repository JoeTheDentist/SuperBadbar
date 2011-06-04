/**
 * 	@file boss.cpp
 * 	@brief Implementation de la classe Boss
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mai 2011
 *
 */
#include <iostream>
#include <stdint.h>
#include <cmath>

#include "boss.h"


Boss::Boss(std::string name, int posx, int posy):
	Monster(name, posx, posy)
{
	m_state = WALKING;
}

Boss::Boss(Analyser *analyserLevel):
	Monster(analyserLevel)
{
	m_state = WALKING;
}

Boss::~Boss()
{
}

void Boss::update_speed_ai()
{
	update_speed_simple(); // meme comportement dans tous les cas
}

void Boss::update()
{
}


