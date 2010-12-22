/**
 * 	@file following_walking_monsters.h
 * 	@brief Header de la classe Following_walking_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "following_walking_monsters.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../sound/sound_manager.h"
#include "../video/pictures_container.h"
#include "babar.h"


Following_walking_monster::Following_walking_monster(Sound_manager *sound_manager, Analyser *analyserLevel, Pictures_container *pictures_container) : Monster(sound_manager)
{
	m_nom = analyserLevel->read_string();
	Analyser analyserMonster;

	// donnees contenues dans le level
	m_pos.x = analyserLevel->read_int();
	m_pos.y = analyserLevel->read_int();

	// donnees propres a la nature du monstre (a chercher dans le bestiaire)
	analyserMonster.open((MONSTERS_STATS_R + m_nom + MONSTERS_EXT).c_str());
	m_life = analyserMonster.read_int();
	m_speed_def = analyserMonster.read_int();
	analyserMonster.close();

	// images
    std::string pic_monsters_rep = PIC_MONSTERS_R;

    m_animt = new Anim_table(pic_monsters_rep+m_nom+"/"+m_nom);

	/*m_pics[0][0] = pictures_container->load_BMP((pic_monsters_rep+ m_nom + "_left_1" +PICS_EXT).c_str());
	m_pics[0][1] = pictures_container->load_BMP((pic_monsters_rep+ m_nom + "_left_2" +PICS_EXT).c_str());
	m_pics[0][2] = pictures_container->load_BMP((pic_monsters_rep+ m_nom + "_left_3" +PICS_EXT).c_str());
	m_pics[0][3] = pictures_container->load_BMP((pic_monsters_rep+ m_nom + "_left_2" +PICS_EXT).c_str());
	m_pics[1][0] = pictures_container->load_BMP((pic_monsters_rep+ m_nom + "_right_1" +PICS_EXT).c_str());
	m_pics[1][1] = pictures_container->load_BMP((pic_monsters_rep+ m_nom + "_right_2" +PICS_EXT).c_str());
	m_pics[1][2] = pictures_container->load_BMP((pic_monsters_rep+ m_nom + "_right_3" +PICS_EXT).c_str());
	m_pics[1][3] = pictures_container->load_BMP((pic_monsters_rep+ m_nom + "_right_2" +PICS_EXT).c_str());*/
	m_speed.x = m_speed_def;
	m_dir = RIGHT;

    m_animt->setRect(m_pos);

	/*m_pos.w = m_pics[0][0]->w;
	m_pos.h = m_pics[0][0]->h;*/
	m_can_fire = false;
}

Following_walking_monster::~Following_walking_monster()
{

}

void Following_walking_monster::update_speed(Babar *babar)
{

	m_speed.y += GRAVITE;
	if ( (m_pos.x<babar->position().x)&&(m_dir != RIGHT) ) {
	    m_dir = RIGHT;
		m_speed.x = m_speed_def;
	}
	if ( (m_pos.x>babar->position().x)&&(m_dir != LEFT) ) {
	    m_dir = LEFT;
	    m_speed.x = -m_speed_def;
	}
}




