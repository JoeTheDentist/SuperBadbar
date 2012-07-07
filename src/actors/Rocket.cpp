/**
 * 	@file rocket.cpp
 * 	@brief Implementation de la classe Rocket
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date avril 2011
 *
 */

#include "Rocket.h"

#include "util/debug.h"
#include "sprites/SpritesManager.h"
#include "util/globals.h"
#include "game/GameEngine.h"
#include "actors/MonstersManager.h"
#include "actors/Explosion.h"

Rocket::Rocket(Rect pos, Direction h, unsigned int speedx, unsigned int speedy, unsigned int damage)
{
    PRINT_CONSTR(2, "Construction de Rocket");
    m_pos = pos;
    m_dir = h;
    m_damage = damage;
	m_life_span = ROCKET_LIFE_SPAN;
    std::string rep = PIC_PROJ_R;

    m_sprite = gGraphics->get_sprites_manager()->add_table(rep+"rocket/rocket", MIDDLEGROUND);
    m_sprite->set_pos(m_pos);
	m_pos.h = m_sprite->h();
	m_pos.w = m_sprite->w();

    m_speed.x = speedx;
    m_speed.y = speedy;

	m_dead = false;
	m_phase = 0;

	m_invincible = false;
}

Rocket::~Rocket()
{
	PRINT_CONSTR(2, "Destruction de Projectile");
	Projectile * boom = new Explosion(m_pos,m_dir,m_damage);
	gProj->add_proj(boom, m_chan);
}

void Rocket::update_speed()
{
    Rect monsterPos = gGameEngine->get_monsters_manager()->closer_monster_pos(position(), 1000);
	if (monsterPos.x == 0 && monsterPos.y == 0) {
		Projectile::update_speed();
	} else {
		PRINT_DEBUG(1, "YOP")
		if ((monsterPos - position()).det(m_speed) > 0)
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
