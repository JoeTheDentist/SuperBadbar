/**
 * 	@file babar.cpp
 *	@brief Implémentation de la classe Babar
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "babar.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../game/collisions_manager.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../game/static_data.h"
#include "../sprites/projectiles_manager.h"
#include "../video/surface.h"

/*********************************
**	Méthodes de Babar 	**
**********************************/
Babar::Babar(Keyboard *keyboard, Static_data *static_data, Analyser *analyser)
    : m_keyboard(keyboard)
{
	PRINT_CONSTR(1, "Construction de Babar")
	init_babar(analyser);
}

Babar::~Babar()
{
	PRINT_CONSTR(1, "Destruction de Babar")
}

void Babar::load_anim(char age)
{
    char age_c = '0';
    age_c += age;
	std::string babar_pic_dir = PIC_BABAR_R;

	m_animt = new Anim_table(babar_pic_dir+age_c+"/"+"babar");
	m_animt->set_rect(m_pos);
}

void Babar::init_babar(Analyser * a)
{
    /* Initialisation de la position de Babar */
    a->find_string("#Babar#");
    m_pos.x = a->read_int();
    m_pos.y = a->read_int();
    /* Chargement des images en fonction de l'age */
    load_anim(a->read_int());

    /* A gerer en fonction des évènements précédents : vies en sortant du niveau... */
    m_lifes = 5;

    /* Initisalisation de la phase de tir */
    m_fire_phase = 0;

    /* Paramètres par défaut */
    m_invincible = 0;
	m_double_jump = false;
	m_dir = RIGHT;
	m_crouch_time = 0;
	m_ready_double_jump = false;
	m_ready_jump = true;
	m_state = STATIC;
}

void Babar::update_speed()
{
    m_speed.y += GRAVITE;

    m_speed.x = 0;                          /* Pour pouvoir se diriger (ttlt) */
    if (m_keyboard->key_down(k_left))
        m_speed.x -= BABAR_SPEED;
    if (m_keyboard->key_down(k_right))
        m_speed.x += BABAR_SPEED;
}

void Babar::update_state(Static_data *static_data, Collisions_manager *collisions_manager, Projectiles_manager *projectiles_manager)
{
	m_weapons_armory.update();
    if(m_state != JUMP) {
        m_state = STATIC;
		m_double_jump = false;
    }

   	//~ if (m_keyboard->key_down(k_action)) {
		//~ talks.load_and_display_text("test.dial");
	//~ }

	update_direction();

    if ( Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos)) ) {
        m_ready_jump = true;
        m_ready_double_jump = false;
        m_state = STATIC;
    }

    if (can_fire()) {
		projectiles_manager->add_friend_proj(fire());
        m_fire_phase = 0;
    }
    else {
        m_fire_phase++;
    }

    if (can_crouch()) {
        crouch();
    } else {
        /* si on se releve */
        if ( m_crouch_time ) {
            m_pos.y -= m_pos.h;
            m_crouch_time = 0;
        }
    }

    if ( can_walk() ) {
        walk();
    }

    if (can_jump())
		jump();

	if (can_double_jump())
		double_jump();

	if (can_go_down(collisions_manager))
		go_down(collisions_manager);

	if (m_invincible > 0)
		m_invincible --;

	if (m_keyboard->time_pressed(k_prev_weapon) == 1)
		m_weapons_armory.previous_weapon();
	if (m_keyboard->time_pressed(k_next_weapon) == 1)
		m_weapons_armory.next_weapon();

    /* remarque : cette methode a un tour de retard, du fait de la ou elle est placee */
    m_animt->set_rect(m_pos);
}



void Babar::update_direction()
{
	if (m_keyboard->key_down(k_left)) {
		m_dir = LEFT;
	}
	if (m_keyboard->key_down(k_right)) {
		m_dir = RIGHT;
	}
}

bool Babar::can_fire()
{
	return m_keyboard->key_down(k_fire)&&(m_fire_phase>m_weapons_armory.get_current_weapon()->reload_time());
}

std::list<Projectile*> *Babar::fire()
{
	PRINT_TRACE(2, "Tir de Babar")
    return m_weapons_armory.get_current_weapon()->fire(m_pos,m_dir);
}

bool Babar::can_walk() const
{
    return (m_keyboard->key_down(k_right)||m_keyboard->key_down(k_left))&&(m_state!=JUMP && m_state!=CROUCH);
}

void Babar::walk()
{
    m_state = WALK;
}

bool Babar::can_crouch() const
{
    return m_keyboard->key_down(k_down)&&(m_state!=JUMP && m_state!=CROUCH);
}

void Babar::crouch()
{
    m_crouch_time++;
    m_state = CROUCH;
    /* ralentissement depuis debut de crouch */
}

bool Babar::can_jump() const
{
    return m_keyboard->key_down(k_jump) && m_ready_jump && ( !m_double_jump )
     && !m_keyboard->key_down(k_down);
}

void Babar::jump()
{
	m_state = JUMP;
	m_speed.y = -2*BABAR_SPEED; /* Vitesse de saut */
	PRINT_TRACE(3, "Saut de Babar")
	if ( m_keyboard->time_pressed(k_jump) > 1 ) {
        m_ready_double_jump = true;
        if ( m_keyboard->time_pressed(k_jump) > JUMP_TIME) {
            m_ready_jump = false;
            m_keyboard->disable_key(k_jump);
        }
	}
	if (m_keyboard->time_pressed(k_jump) == 1)
		prepare_sound(BABAR_SOUNDS_R + "jump" + SOUNDS_EXT);
}

bool Babar::can_double_jump() const
{
	return (m_state == JUMP) && (m_keyboard->time_pressed(k_jump)==1) && (!m_double_jump) && m_ready_double_jump;
}

void Babar::double_jump()
{
	m_double_jump = true;
	m_ready_double_jump = false;
	PRINT_TRACE(2, "Double-saut de Babar")
	m_speed.y = -4*BABAR_SPEED;
	m_keyboard->disable_key(k_jump);

}

bool Babar::can_go_down(Collisions_manager *collisions_manager) const
{
	return (m_keyboard->key_down(k_jump) && m_keyboard->key_down(k_down) && (m_state == STATIC || m_state == WALK || m_state == CROUCH)
				&& Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos)))
				&& !collisions_manager->double_collision(m_pos);
}

void Babar::go_down(Collisions_manager *collisions_manager)
{
	m_pos.y += BOX_SIZE;
	while (Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos))){
		if (collisions_manager->double_collision(m_pos)) {
			m_pos.y -= BOX_SIZE;
			break;
		}
		else {
			m_pos.y += BOX_SIZE;
		}
	}
	m_keyboard->disable_key(k_jump);
	PRINT_TRACE(2, "Descente d'une plateforme")
}

void Babar::damage(int damages)
{
	PRINT_TRACE(3, "Babar bobo")
	if (!is_invincible()) {
		m_lifes -= damages;
		m_invincible = 20;

	}
}

void Babar::add_weapon(weapon_type weapon)
{
	m_weapons_armory.add_weapon(weapon);
}

bool Babar::is_invincible() const
{
	return m_invincible > 0;
}

int Babar::lifes() const
{
	return m_lifes;
}

int Babar::munitions()
{
	return m_weapons_armory.get_current_weapon()->munitions();
}

weapon_type Babar::type_of_weapon()
{
	return m_weapons_armory.get_current_weapon()->type_of_weapon();
}

Surface *Babar::current_picture() const
{
	if ((m_invincible <= 0 || m_invincible%2 == 0)) {
		m_animt->change_anim(m_state, m_dir);
        return m_animt->curr_pic();
	} else
		return NULL;
}

