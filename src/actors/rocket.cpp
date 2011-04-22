/**
 * 	@file rocket.cpp
 * 	@brief Implementation de la classe Rocket
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include "rocket.h"
#include "../util/debug.h"
#include "../sprites/sprites_manager.h"
#include "../util/globals.h"
#include "../game/game_engine.h"
#include "../actors/monsters_manager.h"

Rocket::Rocket(Rect pos, direction h, unsigned int speedx, unsigned int speedy, unsigned int damage):
	Projectile(pos, h, speedx, speedy, damage)
{
	m_life_span = ROCKET_LIFE_SPAN;
}

Rocket::~Rocket()
{
	PRINT_CONSTR(3, "Destruction d'une rocket")
}

void Rocket::update_speed()
{
    Rect monsterPos = gGame_engine->get_monsters_manager()->closer_monster_pos(position(), 1000);
	if (monsterPos.x == 0 && monsterPos.y == 0) {
		Projectile::update_speed();
	} else {
		PRINT_DEBUG(1, "YOP")
		if (det(monsterPos - position(), m_speed) > 0)
			changeDirDirect();
		else
			changeDirIndirect();
	}
}

void Rocket::changeDirDirect()
{
	if (m_speed.x >= 0) {
		m_speed.y-= ROCKET_TURN_SPEED;
	} else {
		m_speed.y+= ROCKET_TURN_SPEED;
	}
	if (m_speed.y >= 0) {
		m_speed.x+= ROCKET_TURN_SPEED;
	} else {
		m_speed.x-= ROCKET_TURN_SPEED;
	}
}

void Rocket::changeDirIndirect()
{
	if (m_speed.x >= 0) {
		m_speed.y+= ROCKET_TURN_SPEED;
	} else {
		m_speed.y-= ROCKET_TURN_SPEED;
	}
	if (m_speed.y >= 0) {
		m_speed.x-= ROCKET_TURN_SPEED;
	} else {
		m_speed.x+= ROCKET_TURN_SPEED;
	}	
}
