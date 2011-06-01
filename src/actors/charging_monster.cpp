/**
 * 	@file charging_monster.cpp
 * 	@brief Implementation de la classe Charging_monster
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mai 2011
 *
 */
#include <iostream>
#include <stdint.h>
#include <cmath>

#include "charging_monster.h"
#include "../util/debug.h"
#include "../util/globals.h"
#include "../video/camera.h"
#include "../video/graphic_engine.h"
#include "../util/analyser.h"
#include "../items/gun.h"
#include "../items/monster_basic_weapon.h"
#include "../actors/babar.h"
#include "../players/players_manager.h"
#include "../AI/AI.h"


Charging_monster::Charging_monster(std::string name, int posx, int posy):
	Walking_monster(name, posx, posy),
	m_speed_max(BABAR_SPEED * 2)
{
	m_state = WALKING;
	Rect babarpos = gPlayers->closer_babar(position())->position();
	if (babarpos.x > position().x) {
		m_dir = RIGHT;
		m_speed.x = m_speed_max; 
	} else {
		m_dir = LEFT;
		m_speed.x = -m_speed_max;
	}
}

Charging_monster::Charging_monster(Analyser *analyserLevel):
	Walking_monster(analyserLevel),
	m_speed_max(BABAR_SPEED * 2)
{
	m_state = WALKING;
}

Charging_monster::~Charging_monster()
{
}

void Charging_monster::update_speed_simple()
{
	Rect babarpos = gPlayers->closer_babar(position())->position();
	if (m_time_end_charge == 0) {
		if (babarpos.x > position().x) {
			m_dir = RIGHT;
			m_speed.x = m_speed_max; 
		} else {
			m_dir = LEFT;
			m_speed.x = -m_speed_max;
		}	
	}
	m_speed.y += GRAVITE;
	m_time_end_charge--;
}

void Charging_monster::update_speed_ai()
{
	m_speed.y += GRAVITE;
	Rect babarpos = gPlayers->closer_babar(position())->position();
	if (m_time_end_charge == 0) {
		if (babarpos.x > position().x) {
			m_dir = RIGHT;
			m_speed.x = m_speed_max; 
		} else {
			m_dir = LEFT;
			m_speed.x = -m_speed_max;
		}
	}
	if (abs(babarpos.x - m_pos.x) < 20 && m_time_end_charge <= 0) {
		m_time_end_charge = 20;
	}
	m_time_end_charge--;
}




