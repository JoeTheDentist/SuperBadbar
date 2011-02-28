/**
 * 	@file following_walking_monsters.cpp
 * 	@brief Source de la classe Following_walking_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>
#include <stdint.h>

#include "following_walking_monsters.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "babar.h"
#include "../AI/AI.h"


Following_walking_monster::Following_walking_monster(Analyser *analyserLevel)
{
	m_nom = analyserLevel->read_string();
	Analyser analyserMonster;

	// donnees contenues dans le level
	m_pos.x = analyserLevel->read_int();
	m_pos.y = analyserLevel->read_int();

	// donnees propres a la nature du monstre (a chercher dans le bestiaire)
	analyserMonster.open((MONSTERS_STATS_R + m_nom + MONSTERS_EXT).c_str());
	analyserMonster.read_string(); // on saute la premiere ligne inutile ici

	m_life = analyserMonster.read_int();
	m_speed_def = analyserMonster.read_int();
	analyserMonster.close();

	// images
    std::string pic_monsters_rep = PIC_MONSTERS_R;

    m_animt = new Anim_table(pic_monsters_rep+m_nom+"/"+m_nom);

	m_speed.x = m_speed_def;
	m_dir = RIGHT;

    m_animt->set_rect(m_pos);

	m_can_fire = false;
}

Following_walking_monster::Following_walking_monster(Analyser *analyserLevel, Babar *babar)
{
    m_nom = analyserLevel->read_string();
	Analyser analyserMonster;

	// donnees contenues dans le level
	m_pos.x = analyserLevel->read_int();
	m_pos.y = analyserLevel->read_int();

	// donnees propres a la nature du monstre (a chercher dans le bestiaire)
	analyserMonster.open((MONSTERS_STATS_R + m_nom + MONSTERS_EXT).c_str());
	analyserMonster.read_string(); // on saute la premiere ligne inutile ici
	m_life = analyserMonster.read_int();
	m_speed_def = analyserMonster.read_int();
	analyserMonster.close();

	// images
    std::string pic_monsters_rep = PIC_MONSTERS_R;

    m_animt = new Anim_table(pic_monsters_rep+m_nom+"/"+m_nom);

	m_speed.x = m_speed_def;
	m_dir = RIGHT;

    m_animt->set_rect(m_pos);

	m_can_fire = false;

    m_ai = new AI(babar, &m_pos);
}

Following_walking_monster::~Following_walking_monster()
{
    delete m_ai;
}

void Following_walking_monster::update_speed(Babar *babar)
{
    direction d = m_ai->dir();

    switch ( d ) {
        case LEFT:
            m_dir = LEFT;
            m_speed.x = -m_speed_def;
            break;
        case RIGHT:
            m_dir = RIGHT;
            m_speed.x = m_speed_def;
            break;
        case UP:
            if ( m_speed.y >= 0 ) {
                m_speed.y -= 70;
            }
            break;
        case DOWN:
            m_pos.y += 10;
            break;
    }


	m_speed.y += GRAVITE;
}




