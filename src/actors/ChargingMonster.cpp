/**
 * 	@file ChargingMonster.cpp
 * 	@brief Implementation de la classe ChargingMonster
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mai 2011
 *
 */


#include "ChargingMonster.h"

#include <cmath>

#include <actors/Babar.h>
#include <items/Gun.h>
#include <items/MonsterBasicWeapon.h>
#include <players/PlayersManager.h>
#include <util/globals.h>
#include <util/utils.h>
#include <video/Camera.h>
#include <video/GraphicEngine.h>





ChargingMonster::ChargingMonster(std::string name, int posx, int posy):
	WalkingMonster(name, posx, posy),
	m_speed_max(BABAR_SPEED * 2),
	m_time_end_charge(0)
{
    PRINT_CONSTR(2, "Construction de ChargingMonster");
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

ChargingMonster::ChargingMonster(Analyser *analyserLevel):
	WalkingMonster(analyserLevel),
	m_speed_max(BABAR_SPEED * 2),
	m_time_end_charge(0)
{
    PRINT_CONSTR(2, "Construction de ChargingMonster");
	m_state = WALKING;
}

ChargingMonster::~ChargingMonster()
{
    PRINT_CONSTR(2, "Destruction de ChargingMonster");
}

void ChargingMonster::update_speed_simple()
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
	if (abs(babarpos.x - m_pos.x) < 20 && m_time_end_charge <= 0) {
		m_time_end_charge = 20;
	}
	m_speed.y += GRAVITE;
	m_time_end_charge--;
}

void ChargingMonster::update_speed_ai()
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




