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


/*********************************
**	Méthodes de Babar 	**
**********************************/
Babar::Babar(Keyboard *keyboard, Static_data *static_data, Sound_manager *sound_manager)
    : m_keyboard(keyboard), m_weapon(MACHINEGUN, static_data->proj_pics(), sound_manager)
{
	PRINT_CONSTR(1, "Construction de Babar")
	m_pos.x = 0;
	m_pos.y = 1600;
	m_invincible = 0;
	m_lifes = 5;
	m_last_dir = LEFT;
	m_fire_phase = 0;
	m_double_jump = false;
	m_sound_manager = sound_manager;
	m_plane = false;
	m_allowed_to_plane = true;

    /*** Stockage et chargement dans le tableau des images ***/
    load(1);
}

Babar::~Babar()
{
	PRINT_CONSTR(1, "Destruction de Babar")
    delete m_animm;
}

void Babar::load(char age)
{
    char age_c = '0';
    age_c += age;
	std::string babar_pic_dir = PIC_BABAR_R;

	m_animm = new Anim_manager(babar_pic_dir+"babar");

    m_animm->setRect(m_pos);
}

void Babar::init_babar(Analyser a)
{

}

void Babar::update_speed()
{
	if (m_plane)
		m_speed.y = GRAVITE/5;
	else
		m_speed.y += GRAVITE;
    m_speed.x = 0;                          /* Pour pouvoir se diriger (ttlt) */
    if (m_keyboard->key_down(k_left))
        m_speed.x -= BABAR_SPEED;
    if (m_keyboard->key_down(k_right))
        m_speed.x += BABAR_SPEED;
}

void Babar::update_state(Static_data *static_data, Collisions_manager *collisions_manager, Projectiles_manager *projectiles_manager)
{
    if(m_state != JUMP) {
        m_state = STATIC;
		m_double_jump = false;
    }

   	//~ if (m_keyboard->key_down(k_action)) {
		//~ talks.load_and_display_text("test.dial");
	//~ }

	update_direction();

	if(can_fly()) {
		fly();
	}
	if (can_stop_fly()) {
		stop_fly();
	}
    if (can_fire()) {
		projectiles_manager->add_friend_proj(fire());
        m_fire_phase = 0;
    }
    else {
        m_fire_phase++;
    }

    if (can_jump())
		jump();

	if (can_double_jump())
		double_jump();

	if (can_go_down(collisions_manager))
		go_down(collisions_manager);

    if ((uint32_t)(m_pos.y + m_pos.h) > static_data->static_data_height()) {                           /* On remet le bon état à la fin du saut */
        m_state = STATIC;
    }
    if ((m_keyboard->key_down(k_right)||m_keyboard->key_down(k_left))&&(m_state!=JUMP)) {
        m_state = WALK;
    }
	if (m_invincible > 0)
		m_invincible --;
}

void Babar::update_direction()
{
	if (m_keyboard->key_down(k_left)) {
		m_horizontal = LEFT;
		m_last_dir = LEFT;
	}
	if (m_keyboard->key_down(k_right)) {
		m_horizontal = RIGHT;
		m_last_dir = RIGHT;
	}
}

bool Babar::can_fire() const
{
	return m_keyboard->key_down(k_fire)&&(m_fire_phase>m_weapon.reload_time());
}

std::list<Projectile*> *Babar::fire()
{
	PRINT_TRACE(2, "Tir de Babar")
	if(m_keyboard->key_down(k_up)||m_keyboard->key_down(k_down)) {
		return m_weapon.fire(m_pos,m_horizontal);
	}
	else {
		return m_weapon.fire(m_pos,m_last_dir);
	}
}

bool Babar::can_double_jump() const
{
	return m_state == JUMP && m_keyboard->key_down(k_jump) && (!m_double_jump);
}

void Babar::double_jump()
{
	m_double_jump = true;
	PRINT_TRACE(2, "Double-saut de Babar")
	m_speed.y = -5*BABAR_SPEED;
	m_sound_manager->play_babar_jump();
	m_keyboard->disable_key(k_jump);

}


bool Babar::can_jump() const
{
	return m_keyboard->key_down(k_jump) && (m_state!=JUMP) && !m_keyboard->key_down(k_down);
}

void Babar::jump()
{
	m_state = JUMP;
	m_speed.y = -5*BABAR_SPEED; /* Vitesse de saut */
	PRINT_TRACE(2, "Saut de Babar")
	m_keyboard->disable_key(k_jump);
	m_sound_manager->play_babar_jump();
}

bool Babar::can_go_down(Collisions_manager *collisions_manager) const
{
	return (m_keyboard->key_down(k_jump) && m_keyboard->key_down(k_down) && (m_state == STATIC || m_state == WALK)
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

void Babar::fly()
{
	m_keyboard->disable_key(k_jump);
	m_plane = true;
}

bool Babar::can_fly() const
{
	if (m_plane || !m_allowed_to_plane)
		return false;
	return m_double_jump && m_keyboard->key_down(k_jump);
}

bool Babar::can_stop_fly() const
{
	if (!m_plane)
		return false;
	return (m_plane && m_keyboard->key_down(k_jump)) || m_state == STATIC;

}

void Babar::stop_fly()
{
	m_keyboard->disable_key(k_jump);
	m_plane = false;
}


void Babar::damage(int damages)
{
	PRINT_TRACE(3, "Babar bobo")
	if (!is_invincible()) {
		m_sound_manager->play_babar_rugissement();
		m_lifes -= damages;
		m_invincible = 20;

	}
}

void Babar::change_weapon(weapon_type weapon)
{
	m_weapon.change_weapon(weapon);
}

bool Babar::is_invincible() const
{
	return m_invincible > 0;
}

int Babar::lifes() const
{
	return m_lifes;
}

int Babar::munitions()  const
{
	return m_weapon.munitions();
}

weapon_type Babar::type_of_weapon()  const
{
	return m_weapon.type_of_weapon();
}

SDL_Surface *Babar::current_picture() const
{
	if ((m_invincible <= 0 || m_invincible%2 == 0)) {
		m_animm->change_anim(m_state, m_last_dir);
        return m_animm->curr_pic();
	} else
		return NULL;
}

