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

#include "WalkingMonster.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../sound/SoundEngine.h"
#include "../video/PicturesContainer.h"
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

