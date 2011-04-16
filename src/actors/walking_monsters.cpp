/**
 * 	@file walking_monsters.cpp
 * 	@brief Source de la classe Walking_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>
#include <stdint.h>

#include "walking_monsters.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../sound/sound_manager.h"
#include "../video/pictures_container.h"
#include "babar.h"


Walking_monster::Walking_monster(std::string name, int posx, int posy):
	Monster(name, posx, posy)
{
}

Walking_monster::Walking_monster(Analyser *analyserLevel):
	Monster(analyserLevel)
{
}

Walking_monster::~Walking_monster()
{

}

