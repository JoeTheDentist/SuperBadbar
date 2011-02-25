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
#include "../game/moving_platform.h"
#include "../control/keyboard.h"
#include "../game/static_data.h"
#include "../sprites/projectiles_manager.h"
#include "../video/surface.h"
#include "../util/globals.h"

/*********************************
**	Méthodes de Babar 	**
**********************************/
Babar::Babar(Keyboard *keyboard, Static_data *static_data, Analyser *analyser)
    : m_keyboard(keyboard)
{
	PRINT_CONSTR(1, "Construction de Babar")
	init_babar(analyser);
	m_bind = NULL;
	m_fire = false;
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

void Babar::update_pos(Static_data *static_data, Collisions_manager *collisions_manager)
{
	m_phase++;
	/* Si Babar est lié à une plateforme, on gère autrement sa position */
	if (binded()) {
		binded_update_pos(static_data, m_bind);
		return;
	}
	uint32_t coll;
	/* cas où le sprite descend */
	for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		coll = collisions_manager->down_collision_type(m_pos);
		if(binded())
			break;
		collisions_manager->update_babar_platforms(this);
		if (Collisions_manager::is_down_coll(coll)){
			speed_y = 0;
			m_speed.y = 0;
			/*if (m_state == JUMP)
				m_state = STATIC;*/
		}
		else {
			m_pos.y += BOX_SIZE;
			if (m_pos.y + m_pos.h > (int32_t)static_data->static_data_height())
				m_pos.y = static_data->static_data_height() - m_pos.h;
		}
	}
	/* cas où le sprite monte */
	for (int32_t speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		collisions_manager->update_babar_platforms(this);
		if(binded())
			break;
		if (Collisions_manager::is_up_coll(collisions_manager->up_collision_type(m_pos))){
			speed_y = 0;
			m_speed.y = 0;
		}
		else {
			if (m_pos.y < 0)
				m_pos.y = 0;
			m_pos.y -= BOX_SIZE;
		}
	}
	/* cas où le sprite va à droite */
	for (int32_t speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
		collisions_manager->update_babar_platforms(this);
		if(binded())
			break;
		m_pos.y -= 	BOX_SIZE;
		if(!Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos)))
			m_pos.y += BOX_SIZE;
		m_pos.x += BOX_SIZE;
		if (m_pos.x + m_pos.w > (int32_t)static_data->static_data_weight())
			m_pos.x = static_data->static_data_weight() - m_pos.w;
	}
	/* cas où le sprite va à gauche */
	for (int32_t speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
		collisions_manager->update_babar_platforms(this);
		if(binded())
			break;
		m_pos.y -= 	BOX_SIZE;
		if(!Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos)))
			m_pos.y += BOX_SIZE;
		m_pos.x -= BOX_SIZE;
		if (m_pos.x < 0)
			m_pos.x = 0;
	}


}

void Babar::binded_update_pos(Static_data *static_data, Moving_platform *platform)
{
	Rect plat_pos = platform->position();
	m_pos.x = plat_pos.x;
	m_pos.y = plat_pos.y;
	/* update de  m_binded_pos */
	uint32_t coll;
	/* cas où le sprite descend */
	for (int32_t speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		coll = platform->down_collision_type(m_binded_pos);
		if (Collisions_manager::is_down_coll(coll)){
			speed_y = 0;
			m_speed.y = 0;
		}
		else {
			m_binded_pos.y += BOX_SIZE;
			if (m_pos.y + m_pos.h > (int32_t)static_data->static_data_height())
				m_pos.y = static_data->static_data_height() - m_pos.h;
		}
	}
	/* cas où le sprite monte */
	for (int32_t speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		if (Collisions_manager::is_up_coll(platform->up_collision_type(m_binded_pos))){
			speed_y = 0;
			m_speed.y = 0;
		}
		else {
			if (m_pos.y < 0)
				m_pos.y = 0;
			m_binded_pos.y -= BOX_SIZE;
		}
	}
	/* cas où le sprite va à droite */
	for (int32_t speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
		m_binded_pos.y -= 	BOX_SIZE;
		if(!Collisions_manager::is_down_coll(platform->down_collision_type(m_binded_pos)))
			m_binded_pos.y += BOX_SIZE;
		m_binded_pos.x += BOX_SIZE;
		if (m_pos.x + m_pos.w > (int32_t)static_data->static_data_weight())
			m_pos.x = static_data->static_data_weight() - m_pos.w;
	}
	/* cas où le sprite va à gauche */
	for (int32_t speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
		m_binded_pos.y -= 	BOX_SIZE;
		if(!Collisions_manager::is_down_coll(platform->down_collision_type(m_binded_pos)))
			m_binded_pos.y += BOX_SIZE;
		m_binded_pos.x -= BOX_SIZE;
		if (m_pos.x < 0)
			m_pos.x = 0;
	}




	m_pos.x += m_binded_pos.x;
	m_pos.y += m_binded_pos.y;
}

void Babar::update_speed()
{
    m_speed.y += GRAVITE;

    m_speed.x = 0;                          /* Pour pouvoir se diriger (ttlt) */
    if (m_keyboard->key_down(k_left)) {
        if ( m_state == CROUCH_WALKING ) {
            m_speed.x -= BABAR_SPEED/3;
        } else {
            m_speed.x -= BABAR_SPEED;
        }
    }
    if (m_keyboard->key_down(k_right)) {
        if ( m_state == CROUCH_WALKING ) {
            m_speed.x += BABAR_SPEED/3;
        } else {
            m_speed.x += BABAR_SPEED;
        }
    }
}

void Babar::update_state(Static_data *static_data, Collisions_manager *collisions_manager, Projectiles_manager *projectiles_manager)
{
	// ATTENTION: "arnaque" pour la sortie de plateforme mobile:
	// les pentes introduisent des sorties non voulues, donc
	// on considère qu'on sort de la plateforme après 3 cycles de chute
	static int unbind_phase = 0;
	if (m_bind) {
		if (!Collisions_manager::is_down_coll(m_bind->down_collision_type(m_binded_pos))) {
			unbind_phase++;
			if (unbind_phase == 3) {
				unbind();
				unbind_phase = 0;
			}
		} else {
			unbind_phase = 0;
		}
	}

	m_weapons_armory.update();
    if(m_state != JUMP) {
        m_state = STATIC;
		m_double_jump = false;
    }

	update_direction();

    if ( Collisions_manager::is_down_coll(collisions_manager->down_collision_type(m_pos)) ) {
        m_ready_jump = true;
        m_ready_double_jump = false;
        m_state = STATIC;
    }

    if (can_fire()) {
        m_fire = true;
		projectiles_manager->add_friend_proj(fire());
        m_fire_phase = 0;
    }
    else {
        m_fire = false;
        m_fire_phase++;
    }

    if (can_crouch()) {
        crouch();
    } else {
        /* si on se releve */
        if ( m_crouch_time ) {
            m_pos.y -= m_pos.h/2;
            m_crouch_time = 0;
        }
    }

    if ( can_walk() ) {
        walk();
    }

/* A REFAIRE */
	if (binded() && m_keyboard->key_down(k_jump)) {
		unbind();
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
	/* Calcul de la position de la source du tir */
	Rect fire_pos = m_pos;
	fire_pos.y += SOURCE_Y;
	if ( m_dir == RIGHT ) {
	    fire_pos.x += m_pos.w;
	}
    return m_weapons_armory.get_current_weapon()->fire(fire_pos,m_dir);
}

bool Babar::can_walk() const
{
    return (m_keyboard->key_down(k_right)||m_keyboard->key_down(k_left))&&(m_state!=JUMP && m_state!=CROUCH && m_state!=CROUCH_WALKING );
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
    if ( m_keyboard->key_down(k_right) || m_keyboard->key_down(k_left) )
        m_state = CROUCH_WALKING;
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
	PRINT_TRACE(1, "Saut de Babar")
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
	return (m_keyboard->key_down(k_jump) && m_keyboard->key_down(k_down)
                && (m_state == STATIC || m_state == WALK || m_state == CROUCH)
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
//~ 	m_keyboard->disable_key(k_jump);
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

Rect Babar::speed() const
{
	return m_speed;
}

bool Babar::binded() const
{
	return m_bind != NULL;
}

void Babar::bind(Moving_platform *platform)
{
	m_bind = platform;
	Rect plat_speed = platform->speed();
	Rect plat_pos = platform->position();
	m_speed.x = plat_speed.x;
	m_speed.y = plat_speed.y;
	m_binded_pos.x = m_pos.x - plat_pos.x;
	m_binded_pos.y = m_pos.y - plat_pos.y;
	m_binded_pos.w = m_pos.w;
	m_binded_pos.h = m_pos.h;
	m_state = STATIC;
	m_ready_jump = true;
}

void Babar::unbind()
{
	m_bind->unbind();
	m_bind = NULL;

}
