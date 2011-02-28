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

#include "following_flying_monsters.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "babar.h"


Following_flying_monster::Following_flying_monster(Analyser *analyserLevel)
{
    PRINT_CONSTR(1, "                               Construction d'un following_flying_monster")
	m_nom = analyserLevel->read_string();
	Analyser analyserMonster;

	// donnees contenues dans le level
	m_pos.x = analyserLevel->read_int();
	m_pos.y = analyserLevel->read_int();

	// donnees propres a la nature du monstre (a chercher dans le bestiaire)
	analyserMonster.open((MONSTERS_STATS_R + m_nom + MONSTERS_EXT).c_str());
	std::cout << analyserMonster.read_string() << std::endl; // on saute la premiere ligne inutile ici
	m_life = analyserMonster.read_int();
	m_speed_def = analyserMonster.read_int();
	std::cout << m_life << " " << m_speed_def << std::endl;
	analyserMonster.close();

	// images
    std::string pic_monsters_rep = PIC_MONSTERS_R;

    m_animt = new Anim_table(pic_monsters_rep+m_nom+"/"+m_nom);

	m_speed.x = m_speed_def;
	m_dir = RIGHT;

    m_animt->set_rect(m_pos);

	m_can_fire = false;
}

Following_flying_monster::~Following_flying_monster()
{

}


void Following_flying_monster::update_speed()
{
	if ( (m_pos.x<gBabar->position().x)&&(m_dir != RIGHT) ) {
	    m_dir = RIGHT;
		m_speed.x = m_speed_def;
	}
	if ( (m_pos.x>gBabar->position().x)&&(m_dir != LEFT) ) {
	    m_dir = LEFT;
	    m_speed.x = -m_speed_def;
	}

	if ( (m_pos.y<gBabar->position().y) ) {
		m_speed.y = m_speed_def;
	}
	if ( (m_pos.y>gBabar->position().y) ) {
	    m_speed.y = -m_speed_def;
	}
}

