/**
 * 	@file monsters.cpp
 * 	@brief Implémentation de la classe Monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "monsters.h"
#include "../util/repertories.h"
#include "../util/debug.h"
#include "../util/analyser.h"
#include "../game/game.h"
#include "../video/surface.h"
#include "../video/animation_engine.h"
#include "../sprites/projectiles.h"
#include "../items/weapons.h"
#include "../items/monster_basic_weapon.h"
#include "babar.h"




/*********************************
**	Méthodes de Monster	**
**********************************/

Monster::Monster():
	m_weapon(NULL)
{

}

Monster::~Monster()
{
	PRINT_CONSTR(3, "destruction d'un monstre")
}

void Monster::initFromMonsterFile(std::string file)
{
	m_weapon = NULL;
	m_state = WALKING;
    m_fire = false;
	m_fire_phase = 0;
	Analyser analyserMonster;
	analyserMonster.open((MONSTERS_STATS_R + file + MONSTERS_EXT).c_str());
	analyserMonster.find_string("#Lifes#");
	m_life = analyserMonster.read_int();
	analyserMonster.find_string("#Speed#");
	m_speed_def = analyserMonster.read_int();
	if (analyserMonster.find_string("#Weapon#")) {
		//TODO faire une fonction
		if (analyserMonster.read_string() == "monster_basic_weapon")
			m_weapon = new Monster_basic_weapon();
	}	
	analyserMonster.close();
    m_animt = new Anim_table(PIC_MONSTERS_R + m_nom + "/" + m_nom);
	m_speed.x = m_speed_def;
	m_dir = RIGHT;
    m_animt->set_rect(m_pos);	
}

Surface *Monster::current_picture() const
{
    m_animt->change_anim(m_state, m_dir, m_fire, true);
    return m_animt->curr_pic();
}

void Monster::update_speed()
{
	if ( dist(m_pos, gBabar->position()) > SWITCH_DIST ) {
	    update_speed_simple();
	} else {
	    update_speed_ai();
	}
}

void Monster::update_speed_simple()
{
    if ( gCollision->can_fall(m_pos) ) {
        m_speed.x *= -1;
        if ( m_dir == LEFT ) {
            m_dir = RIGHT;
        } else {
            m_dir = LEFT;
        }
        m_pos.y -= 3*BOX_SIZE;
    }
    m_speed.y += GRAVITE;
}

void Monster::update_speed_ai()
{
    update_speed_simple();
}

void Monster::damage(uint32_t damage)
{
	m_life -= damage;
	prepare_sound(MONSTERS_SOUNDS_R + "hit.mp3");
}

void Monster::update()
{
	m_fire_phase++;
}

bool Monster::dead() const
{
    if ( m_life <= 0 ) {
        gAnims->add(PIC_MONSTERS_R+m_nom+"/death/"+m_nom+"_"+(char)(m_dir+'0')+"_", m_pos, NOEND, m_speed, true);
        return true;
    }
    return false;
}

bool Monster::can_fire()
{
	return m_weapon && (m_fire_phase > m_weapon->reload_time());
}

std::list<Projectile*> *Monster::fire()
{
	/* Calcul de la position de la source du tir */
	Rect fire_pos = m_pos;
	if ( m_dir == RIGHT ) {
		fire_pos.x += m_pos.w;
	}
	fire_pos.y += fire_pos.h/2;
	m_fire_phase = 0;
	return m_weapon->fire(fire_pos,m_dir);
}

