/**
 * 	@file WalkingMonsters.cpp
 * 	@brief Source de la classe WalkingMonster
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>
#include <stdint.h>

#include "WalkingMonster.h"
#include "../util/debug.h"
#include "../util/Analyser.h"
#include "../sound/SoundEngine.h"
#include "../video/PicturesContainer.h"
#include "Babar.h"


WalkingMonster::WalkingMonster(std::string name, int posx, int posy):
	Monster(name, posx, posy)
{
    PRINT_CONSTR(2, "Construction de WalkingMonster");
}

WalkingMonster::WalkingMonster(Analyser *analyserLevel):
	Monster(analyserLevel)
{
    PRINT_CONSTR(2, "Construction de WalkingMonster");
}

WalkingMonster::~WalkingMonster()
{
    PRINT_CONSTR(2, "Destruction de WalkingMonster");
}

