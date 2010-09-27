
#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "walking_monsters.h"
#include "../util/debug.h"
#include "../sound/sound_manager.h"

Walking_monster::Walking_monster(Sound_manager *sound_manager) : Monster(sound_manager)
{
	
}

Walking_monster::~Walking_monster()
{
	
}

void Walking_monster::update_speed()
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




