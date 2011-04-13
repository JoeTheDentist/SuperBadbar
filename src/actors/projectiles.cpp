/**
 * 	@file projectiles.cpp
 * 	@brief Implémentation de la classe Projectile
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <stdint.h>

#include "projectiles.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../game/static_data.h"
#include "../physic/collisions_manager.h"
#include "../sprites/sprites_manager.h"


/**************************
**  Méthodes projectiles **
**************************/



Projectile::Projectile(Rect pos, direction h, unsigned int speedx, unsigned int speedy, unsigned int damage)
{
	PRINT_CONSTR(3, "Construction d'un projectile")
    m_pos = pos;
    m_dir = h;
    m_damage = damage;

    std::string rep = PIC_PROJ_R;

    /* Rajouter le nom... */
    m_sprite = gSprites->add_table(rep+"simple/simple", MIDDLEGROUND);
    m_sprite->synchro(&m_pos);

    m_speed.x = speedx;
    m_speed.y = speedy;

	m_dead = false;
	m_phase = 0;
}

void Projectile::update_pos(Collisions_manager *collisions_manager)
{
	m_phase++;
	unsigned int coll;
	/* cas où le sprite descend */
	for (int speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		coll = collisions_manager->get_matrix()->down_collision_type(m_pos);
		if (Collisions_manager::is_down_coll(coll)){
			m_dead = true;
		}
		else {
			m_pos.y += BOX_SIZE;
		}
	}

	/* cas où le sprite monte */
	for (int speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		if (Collisions_manager::is_up_coll(collisions_manager->get_matrix()->up_collision_type(m_pos))){
			m_dead = true;
		}
	}

	/* cas où le sprite va à droite */
	for (int speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
			if(Collisions_manager::is_down_coll(collisions_manager->get_matrix()->down_collision_type(m_pos)))
				m_dead = true;
			m_pos.x += BOX_SIZE;
	}

	/* cas où le sprite va à gauche */
	for (int speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
			if(Collisions_manager::is_down_coll(collisions_manager->get_matrix()->down_collision_type(m_pos))) {
				m_dead = true;
			}
			m_pos.x -= BOX_SIZE;
	}
	if (m_phase >= PROJ_LIFE_SPAN)
		m_dead = true;
}

Projectile::~Projectile()
{
	PRINT_CONSTR(3, "Destruction d'un projectile")
}

unsigned int Projectile::damage() const
{
    return m_damage;
}

Rect Projectile::speed() const
{
    return m_speed;
}

bool Projectile::dead() const
{
	return m_dead;
}

void Projectile::kill()
{
	m_dead = true;
}


/*** Fonctions ***/

bool too_old(Projectile * p, Collisions_manager *collisions_manager)
{
    bool to_return = (p->phase()>PROJ_LIFE_SPAN);
    Rect speed = p->speed();
    if (speed.x>0)
        to_return |= collisions_manager->get_matrix()->right_collision(p->position());
    else
        to_return |= collisions_manager->get_matrix()->left_collision(p->position());

    if (speed.y>0)
        to_return |= collisions_manager->get_matrix()->down_collision(p->position());
    else
        to_return |= collisions_manager->get_matrix()->up_collision(p->position());
    return to_return;
}

