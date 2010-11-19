
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "monsters.h"
#include "../util/debug.h"
#include "../util/collisions.h"
#include "../game/game.h"




/*********************************
**	Méthodes de Monster	**
**********************************/

Monster::Monster(Sound_manager *sound_manager) 
{
	m_sound_manager = sound_manager;
}

Monster::Monster(uint32_t type, SDL_Rect pos)
{
	m_pos = pos;
	m_type = type;
}

Monster::~Monster()
{

}

SDL_Surface *Monster::current_picture()
{
    return m_pics[m_horizontal/2][(m_phase/ANIMATION_SPEED)%3]; /* Temp */
}


void Monster::update_speed()
{
	m_speed.y += GRAVITE;

	if (m_pos.x<m_area_begin) {
	    m_horizontal = RIGHT;
		m_speed.x = -m_speed.x;
	}
	if (m_pos.x>m_area_end) {
	    m_horizontal = LEFT;
	    m_speed.x = -m_speed.x;
	}
}

void Monster::update_speed(Babar * babar)
{
	m_speed.y += GRAVITE;

	if (m_pos.x<m_area_begin) {
	    m_horizontal = RIGHT;
		m_speed.x = -m_speed.x;
	}
	if (m_pos.x>m_area_end) {
	    m_horizontal = LEFT;
	    m_speed.x = -m_speed.x;
	}
}

void Monster::set_pos_x(uint32_t x)
{
	m_pos.x = x;
}

void Monster::set_pos_y(uint32_t y)
{
	m_pos.y = y;
}

void Monster::set_type(uint32_t type)
{
    m_type = type;
}

void Monster::set_life(uint32_t life)
{
    m_life = life;
}

void Monster::set_begin(uint32_t begin)
{
    m_area_begin = begin;
}

void Monster::set_end(uint32_t end)
{
    m_area_end = end;
}

void Monster::set_fire(bool can_fire)
{
    m_can_fire = can_fire;
}

void Monster::set_speed(uint32_t speed)
{
    m_speed_def = speed;
    m_speed.x = speed;
}

void Monster::set_pic(SDL_Surface * pic, uint32_t i, uint32_t j)
{
    m_pics[i][j] = pic;
    m_pos.h = pic->h;
    m_pos.w = pic->w;
}

void Monster::damage(uint32_t damage)
{
	m_sound_manager->play_monster_damage();
    m_life -= damage;
}



bool Monster::dead()
{
    return (m_life <= 0);
}

int32_t Monster::type()
{
    return m_type;
}

