/**
 * 	@file WalkingMonsters.cpp
 * 	@brief Source de la classe WalkingMonster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>
#include <stdint.h>

#include "WalkingMonsters.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../sound/sound_engine.h"
#include "../video/pictures_container.h"
#include "babar.h"


WalkingMonster::WalkingMonster(std::string name, int posx, int posy):
	Monster(name, posx, posy)
{
}

WalkingMonster::WalkingMonster(Analyser *analyserLevel):
	Monster(analyserLevel)
{
}

WalkingMonster::~WalkingMonster()
{

}

