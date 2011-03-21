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


Walking_monster::Walking_monster() {}

Walking_monster::Walking_monster(Analyser *analyserLevel)
{
	m_nom = analyserLevel->read_string();

	// donnees contenues dans le level
	m_pos.x = analyserLevel->read_int();
	m_pos.y = analyserLevel->read_int();

	// donnees propres a la nature du monstre (a chercher dans le bestiaire)
	initFromMonsterFile(m_nom);
}

Walking_monster::~Walking_monster()
{

}

