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
Babar::Babar(Keyboard *keyboard, Static_data *static_data, Sound_manager *sound_manager, Analyser *analyser)
    : m_keyboard(keyboard), m_weapon(MACHINEGUN, static_data->proj_pics(), sound_manager)
{
	PRINT_CONSTR(1, "Construction de Babar")

	m_sound_manager = sound_manager;

	init_babar(analyser);
}

Babar::~Babar()
{
	PRINT_CONSTR(1, "Destruction de Babar")
    delete m_animt;
}

void Babar::load_anim(char age)
{
    char age_c = '0';
    age_c += age;
	std::string babar_pic_dir = PIC_BABAR_R;

	m_animt = new Anim_table(babar_pic_dir+age_c+"/"+"babar");

    m_animt->setRect(m_pos);
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
    if(m_state != JUMP) {
        m_state = STATIC;
		m_double_jump = false;
    }

   	//~ if (m_keyboard->key_down(k_action)) {
		//~ talks.load_and_display_text("test.dial");
	//~ }

	update_direction();

    if (can_fire()) {
		projectiles_manager->add_friend_proj(fire());
        m_fire_phase = 0;
    }
    else {
        m_fire_phase++;
    }

    if (can_crouch())
        crouch();

    if (can_jump())
		jump();

	if (can_double_jump())
		double_jump();

	if (can_go_down(collisions_manager))
		go_down(collisions_manager);

    if (can_walk()) {
        walk();
    }
	if (m_invincible > 0)
		m_invincible --;
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

bool Babar::can_fire() const
{
	return m_keyboard->key_down(k_fire)&&(m_fire_phase>m_weapon.reload_time());
}

std::list<Projectile*> *Babar::fire()
{
	PRINT_TRACE(2, "Tir de Babar")
    return m_weapon.fire(m_pos,m_dir);
}

bool Babar::can_walk() const
{
    return (m_keyboard->key_down(k_right)||m_keyboard->key_down(k_left))&&(m_state!=JUMP && m_state!=CROUCH);
}

void Babar::walk()
{
    m_crouch_time = 0;
    m_state = WALK;
}

bool Babar::can_crouch() const
{
    return m_keyboard->key_down(k_jump) && !m_keyboard->key_down(k_down) && (m_state!=JUMP);
}

void Babar::crouch()
{
    m_crouch_time++;
    m_state = CROUCH;
    /* faire que la vitesse horizontale dépende si on marchait avant */
}

bool Babar::can_jump() const
{
    if ( m_crouch_time > 0 && m_crouch_time < CROUCH_TIME ) {
        if ( !m_keyboard->key_down(k_jump) && (m_state!=JUMP) ) {
            return true;
        }
    }
    return false;
	/*return m_keyboard->key_down(k_jump) && (m_state!=JUMP) && !m_keyboard->key_down(k_down);*/
}

void Babar::jump()
{
    m_crouch_time = 0;
	m_state = JUMP;
	m_speed.y = -5*BABAR_SPEED; /* Vitesse de saut */
	PRINT_TRACE(2, "Saut de Babar")
	m_keyboard->disable_key(k_jump);
	m_sound_manager->play_babar_jump();
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

bool Babar::can_go_down(Collisions_manager *collisions_manager) const
{
	return (m_keyboard->key_down(k_jump) && m_keyboard->key_down(k_down) && (m_state == STATIC || m_state == WALK)
				&& Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos)))
				&& !collisions_manager->double_collision(m_pos);
}

void Babar::go_down(Collisions_manager *collisions_manager)
{
    m_crouch_time = 0;
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
		m_animt->change_anim(m_state, m_dir);
        return m_animt->curr_pic();
	} else
		return NULL;
}

