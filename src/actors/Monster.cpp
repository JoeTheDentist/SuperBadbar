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

#include "Monster.h"
#include "../util/globals.h"
#include "../util/repertories.h"
#include "../util/debug.h"
#include "../util/Analyser.h"
#include "../game/Game.h"
#include "../video/Surface.h"
#include "../actors/Projectile.h"
#include "../items/Weapon.h"
#include "../items/MonsterBasicWeapon.h"
#include "Babar.h"
#include "../sprites/SpritesManager.h"
#include "../players/PlayersManager.h"

class AnimatedSetManager;


/*********************************
**	Méthodes de Monster	**
**********************************/



Monster::Monster(std::string name, int posx, int posy):
	m_nom(name),
	m_weapon(NULL)
{
    PRINT_CONSTR(2, "Construction de Monster");
	m_pos.x = posx;
	m_pos.y = posy;
	initFromMonsterFile(m_nom);
}

Monster::Monster(Analyser *analyserLevel):
	m_weapon(NULL)
{
    PRINT_CONSTR(2, "Construction de Monster");
    m_nom = analyserLevel->read_string();
	// donnees contenues dans le level
	m_pos.x = analyserLevel->read_int();
	m_pos.y = analyserLevel->read_int();
	initFromMonsterFile(m_nom);
}

Monster::~Monster()
{
	PRINT_CONSTR(2, "Destruction de Monster");
	if ( m_weapon ) {
        delete m_weapon;
	}
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
	m_speed.x = m_speed_def;
	m_dir = RIGHT;

	m_sprite = gGraphics->get_sprites_manager()->add_table(PIC_MONSTERS_R + m_nom + "/" + m_nom, MIDDLEGROUND);
    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();
	m_life_max = m_life;
}

void Monster::update_speed()
{
	if ( dist(m_pos, gPlayers->local_player()->position()) > SWITCH_DIST ) {
	    update_speed_simple();
	} else {
	    update_speed_ai();
	}
}

void Monster::update_speed_simple()
{
    if ( gCollision->get_matrix()->can_fall(m_pos) ) {
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

void Monster::damage(unsigned int damage)
{
	m_life -= damage;
}

void Monster::update()
{
	m_fire_phase++;
	m_sprite->change_anim(m_state, m_dir);
	m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();
}

bool Monster::dead() const
{
    if ( m_life <= 0 ) {
        return true;
    }
    return false;
}

void Monster::kill()
{
	if (m_speed.y < 0)
		m_speed.y = 0;
	gSound->play_sound(MONSTERS_SOUNDS_R + "hit.mp3");
	gGameEngine->get_sets()->add_set(PIC_MONSTERS_R+m_nom+"/death/"+m_nom+"_"+to_string(m_dir)+"_", m_pos, m_speed);
	m_sprite->set_to_delete();
	m_sprite = NULL;
}

bool Monster::can_fire()
{
	return m_weapon && (m_fire_phase > m_weapon->reload_time());
}

std::list<Projectile*> *Monster::fire()
{
	// Calcul de la position de la source du tir
	Rect fire_pos = m_pos;
	if ( m_dir == RIGHT ) {
		fire_pos.x += m_pos.w;
	}
	fire_pos.y += fire_pos.h/3;
	m_fire_phase = 0;
	return m_weapon->fire(fire_pos,m_dir, MONSTERS);
}

