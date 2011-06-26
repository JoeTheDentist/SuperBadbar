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

#include "FlyingMonster.h"
#include "../util/debug.h"
#include "../util/Analyser.h"
#include "Babar.h"


FlyingMonster::FlyingMonster(std::string name, int posx, int posy):
	Monster(name, posx, posy)
{
}

FlyingMonster::FlyingMonster(Analyser *analyserLevel) :
	Monster(analyserLevel)
{
	m_high_min = 2800;
}

FlyingMonster::~FlyingMonster()
{

}

