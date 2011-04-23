/**
 * 	@file babar.cpp
 *	@brief Implémentation de la classe Babar
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <stdint.h>

#include "babar.h"
#include "../util/debug.h"
#include "../game/game.h"
#include "../physic/collisions_manager.h"
#include "../physic/moving_platform.h"
#include "../control/keyboard.h"
#include "../game/static_data.h"
#include "../actors/projectiles_manager.h"
#include "../video/surface.h"
#include "../util/globals.h"
#include "../sprites/sprites_manager.h"

class Sprites_manager;

/*********************************
**	Méthodes de Babar 	**
**********************************/
Babar::Babar(Analyser *analyser)
    : m_peanuts(0)
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
	#ifdef DEBUG_COLL
	age_c = '0';
	#endif
	std::string babar_pic_dir = PIC_BABAR_R;

    /* TODO ici fuite de mémoire si rechargement... */
	m_sprite = gGraphics->get_sprites_manager()->add_table(babar_pic_dir+age_c+"/"+"babar", MIDDLEGROUND);
	m_sprite->set_pos(position());
	set_h(m_sprite->h());
	set_w(m_sprite->w());

	m_last_pos.x = 0;
	m_last_pos.y = 0;
}

void Babar::init_babar(Analyser * a)
{
	m_bind = NULL;
    /* Initialisation de la position de Babar */
    a->find_string("#Babar#");
    m_pos.x = a->read_int();
    m_pos.y = a->read_int();
    /* Chargement des images en fonction de l'age */
    load_anim(a->read_int());
	m_rel_pos = m_pos;

    /* A gerer en fonction des évènements précédents : vies en sortant du niveau... */
    m_hp = 5;

    /* Initisalisation de la phase de tir */
    m_fire_phase = 0;

    /* Paramètres par défaut */
    m_invincible = 0;
	m_dir = RIGHT;
	m_crouch_time = 0;
	interrupt_jump();
	m_bind = NULL;
}

Rect Babar::position() const
{
	if (binded()) {
		Rect res = m_bind->position();
		res.x += m_rel_pos.x;
		res.y += m_rel_pos.y;
		res.h = m_pos.h;
		res.w = m_pos.w;
		return res;
	} else {
		return m_pos;
	}
}

void Babar::move(int x, int y)
{
	if (binded()) {
		m_rel_pos.x += x;
		m_rel_pos.y += y;
	} else {
		m_pos.x += x;
		m_pos.y += y;
	}
}

bool Babar::is_on_something()
{
	if (binded()) {
		return Collisions_manager::is_down_coll(m_bind->down_collision_type(m_rel_pos));
	} else {
		return Collisions_manager::is_down_coll(gCollision->get_matrix()->down_collision_type(position()));
	}

}



void Babar::update_pos()
{
	m_phase++;
	unsigned int coll;
	/* cas où le sprite descend */
	for (int speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE){
		check_unbind();
		gCollision->update_babar_platforms();
		coll = gCollision->get_matrix()->down_collision_type(position());
		if (binded()) {
			coll |= m_bind->down_collision_type(m_rel_pos);
		}
		if (Collisions_manager::is_down_coll(coll)){
			speed_y = 0;
			m_speed.y = 0;
			if ( !binded() ) {
                m_last_pos = m_pos;
			}
		} else {
			move(0, BOX_SIZE);
//~ 			if (position().y + position().h > (int)gStatic->static_data_height())
//~ 				m_rel_pos.y = gStatic->static_data_height() - m_pos.h;
		}
	}
	/* cas où le sprite monte */
	for (int speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE){
		check_unbind();
		gCollision->update_babar_platforms();
		coll = gCollision->get_matrix()->up_collision_type(position());
		if (binded()) {
			coll |= m_bind->up_collision_type(m_rel_pos);
		}
		if (Collisions_manager::is_up_coll(coll)){
			speed_y = 0;
			m_speed.y = 0;
		}
		else {
//~ 			if (m_pos.y < 0)
//~ 				m_pos.y = 0;
			move(0, -BOX_SIZE);
		}
	}
	/* cas où le sprite va à droite */
	for (int speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE){
		check_unbind();
		gCollision->update_babar_platforms();
		move(0, -BOX_SIZE);
		coll = gCollision->get_matrix()->right_collision_type(position());
//~ 		if (binded()) {
//~ 			coll |= m_bind->right_collision_type(m_rel_pos);
//~ 		}
		if (Collisions_manager::is_right_coll(coll)){
			PRINT_DEBUG(1, "ouch");

			speed_x = 0;
			m_speed.x = 0;
		} else {
			move(BOX_SIZE, 0); // On avance!
		}
		if(!is_on_something()) // s'il n'y avait pas de pente montante, on revient
			move(0, BOX_SIZE);
		if(!is_on_something()) // gestion de la pente descendante
			move(0, BOX_SIZE);
		if(!is_on_something())
			move(0, -BOX_SIZE); // ce n'était pas une pente descendante, on revient


//~ 		if (m_pos.x + m_pos.w > (int)gStatic->static_data_weight())
//~ 			m_pos.x = gStatic->static_data_weight() - m_pos.w;
	}
	/* cas où le sprite va à gauche */
	for (int speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE){
		check_unbind();
		gCollision->update_babar_platforms();
		move(0, -BOX_SIZE);
		coll = gCollision->get_matrix()->left_collision_type(position());
		if (binded()) {
			coll |= m_bind->left_collision_type(m_rel_pos);
		}
		if (Collisions_manager::is_left_coll(coll)){
			speed_x = 0;
			m_speed.x = 0;
		} else {
			move(-BOX_SIZE, 0); // On avance!
		}
		if(!is_on_something()) // s'il n'y avait pas de pente montante, on revient
			move(0, BOX_SIZE);
		if(!is_on_something()) // gestion de la pente descendante
			move(0, BOX_SIZE);
		if(!is_on_something())
			move(0, -BOX_SIZE); // ce n'était pas une pente descendante, on revient

	}
}

void Babar::update_speed()
{
    m_speed.y += GRAVITE;
    m_speed.x = 0;

	if (m_jump) {
		m_speed.y = -2*BABAR_SPEED; /* Vitesse de saut */
	}

	/* Pour pouvoir se diriger (ttlt) */
    if (gKeyboard->key_down(k_left)) {
        if ( m_crouch_time ) {
            m_speed.x -= BABAR_SPEED/3;
        } else {
            m_speed.x -= BABAR_SPEED;
        }
    }
    if (gKeyboard->key_down(k_right)) {
        if ( m_crouch_time ) {
            m_speed.x += BABAR_SPEED/3;
        } else {
            m_speed.x += BABAR_SPEED;
        }
    }
}

void Babar::update_state()
{
	if (!gKeyboard->time_pressed(k_jump))
		m_jump = false;
	if (m_jump) {
		if ( gKeyboard->time_pressed(k_jump) > 1 ) {
			m_ready_double_jump = true;
			if ( gKeyboard->time_pressed(k_jump) > JUMP_TIME) {
				m_jump = false;
				gKeyboard->disable_key(k_jump);
			}
		}
	}

	update_direction();

    if ( Collisions_manager::is_down_coll(gCollision->get_matrix()->down_collision_type(position())) ) {
        interrupt_jump();
    }

    if (can_fire()) {
        m_fire = true;
		gProj->add_friend_proj(fire());
        m_fire_phase = 0;
    } else {
        m_fire = false;
        m_fire_phase++;
    }

    if (can_crouch()) {
        crouch();
    } else {
        /* si on se releve */
        if ( m_crouch_time ) {
           interrupt_crouch();
        }
    }

    if (can_jump())
		jump();

	if (can_double_jump())
		double_jump();

	if (can_go_down())
		go_down();

	if (m_invincible > 0) {
		m_invincible --;

		if ( m_invincible%2 ) {
            m_sprite->no_pic();
        } else {
            m_sprite->set_pic();
        }
	}



	m_weapons_armory.update();

	if (gKeyboard->time_pressed(k_prev_weapon) == 1)
		m_weapons_armory.previous_weapon();

	if (gKeyboard->time_pressed(k_next_weapon) == 1)
		m_weapons_armory.next_weapon();

    m_sprite->change_anim(get_state(), m_dir);
    m_sprite->set_pos(position());
	set_h(m_sprite->h());
	set_w(m_sprite->w());
}

void Babar::update_direction()
{
	if (gKeyboard->key_down(k_left)) {
		m_dir = LEFT;
	}
	if (gKeyboard->key_down(k_right)) {
		m_dir = RIGHT;
	}
}

bool Babar::can_fire()
{
	return gKeyboard->key_down(k_fire)&&(m_fire_phase>m_weapons_armory.get_current_weapon()->reload_time());
}

std::list<Projectile*> *Babar::fire()
{
	PRINT_TRACE(2, "Tir de Babar")
	/* Calcul de la position de la source du tir */
	Rect fire_pos = position();
	fire_pos.y += SOURCE_Y;
	if ( m_dir == RIGHT ) {
	    fire_pos.x += position().w;
	}
    return m_weapons_armory.get_current_weapon()->fire(fire_pos,m_dir);
}

bool Babar::can_walk() const
{
    return (gKeyboard->key_down(k_right)||gKeyboard->key_down(k_left))&& !m_jump && !m_double_jump && !m_crouch_time;
}

bool Babar::can_crouch() const
{
    return gKeyboard->key_down(k_down);
}

void Babar::crouch()
{
    m_crouch_time = 1;
    int h_last = m_sprite->curr_pic()->h();
    m_sprite->change_anim(CROUCH, m_dir);
    int h = m_sprite->curr_pic()->h();
	move(0, h_last - h);
}

bool Babar::can_jump() const
{
    return !can_go_down() && gKeyboard->key_down(k_jump) && m_ready_jump && !gKeyboard->key_down(k_down);
}

void Babar::jump()
{
	PRINT_DEBUG(1, "jump");
	m_jump = true;
	m_ready_jump = false;
	m_ready_double_jump = true;
	m_speed.y = -2*BABAR_SPEED; /* Vitesse de saut */
	prepare_sound(BABAR_SOUNDS_R + "jump" + SOUNDS_EXT);
	unbind();
}

bool Babar::can_double_jump() const
{
	return !m_jump && (gKeyboard->time_pressed(k_jump)==1) && !m_double_jump && m_ready_double_jump;
}

void Babar::double_jump()
{
	m_double_jump = true;
	m_ready_double_jump = false;
	PRINT_TRACE(1, "Double-saut de Babar")
	m_speed.y = -4*BABAR_SPEED;
	gKeyboard->disable_key(k_jump);

}

bool Babar::can_go_down() const
{
	Collisions_matrix *plop;
	Rect pos;
	if (binded()) {
		plop = m_bind;
		pos = m_rel_pos;
	} else {
		plop = gCollision->get_matrix();
		pos = m_pos;
	}
	return (gKeyboard->key_down(k_jump) && gKeyboard->key_down(k_down)
				&& Collisions_manager::is_down_coll(plop->down_collision_type(pos)))
				&& !plop->double_collision(pos);
}

void Babar::go_down()
{
	m_pos.y += 2*BOX_SIZE;
	m_speed.y += BOX_SIZE;
	if (binded()) {
		while (Collisions_manager::is_down_coll(m_bind->down_collision_type(m_rel_pos))){
			if (m_bind->double_collision(m_rel_pos)) {
				m_rel_pos.y -= BOX_SIZE;
				break;
			}
			else {
				m_rel_pos.y += BOX_SIZE;
			}
		}
	} else {
		while (Collisions_manager::is_down_coll(gCollision->get_matrix()->down_collision_type(m_pos))){
			if (gCollision->get_matrix()->double_collision(m_pos)) {
				m_pos.y -= BOX_SIZE;
				break;
			}
			else {
				m_pos.y += BOX_SIZE;
			}
		}
	}
	unbind();
	PRINT_TRACE(1, "Descente d'une plateforme")
}

void Babar::damage(int damages)
{
	if (!is_invincible()) {
		m_hp -= damages;
		m_invincible = 20;
	}
}

void Babar::HPup(int HP)
{
	m_hp += HP;
}

void Babar::add_weapon(weapon_type weapon)
{
	m_weapons_armory.add_weapon(weapon);
}

bool Babar::is_invincible() const
{
	return m_invincible > 0;
}

int Babar::HP() const
{
	return m_hp;
}

int Babar::munitions()
{
	return m_weapons_armory.get_current_weapon()->munitions();
}

weapon_type Babar::type_of_weapon()
{
	return m_weapons_armory.get_current_weapon()->type_of_weapon();
}

Rect Babar::speed() const
{
	return m_speed;
}

bool Babar::binded() const
{
	return m_bind;
}

void Babar::bind(Moving_platform *platform)
{
	if (platform->can_bind()) {
		unbind();
		m_bind = platform;
		Rect plat_speed = platform->speed();
		Rect plat_pos = platform->position();
		m_speed.x = plat_speed.x;
		m_speed.y = plat_speed.y;
		interrupt_jump();
		m_ready_jump = true;
		gKeyboard->disable_key(k_jump);
		m_rel_pos.x = m_pos.x - plat_pos.x;
		m_rel_pos.y = m_pos.y - plat_pos.y;
	}
}

void Babar::unbind()
{
	if (binded()) {
		std::cout << "unbind" << std::endl;
		m_pos.x = m_rel_pos.x + m_bind->position().x;
		m_pos.y = m_rel_pos.y + m_bind->position().y;
		m_bind->unbind();
		m_bind = NULL;
	}
}

int Babar::peanuts()
{
	return m_peanuts;
}

void Babar::incr_peanuts(int peanuts)
{
	m_peanuts += peanuts;
}

state_player Babar::get_state() const
{
	if (m_crouch_time && can_walk())
		return CROUCH_WALKING;
	if (m_crouch_time)
		return CROUCH;
	if (m_jump || m_double_jump || m_ready_double_jump) // m_ready_double_jump indique qu'on est entre saut et doublesaut
		return JUMP;
	if (can_walk())
		return WALK;
	return STATIC;
}

void Babar::interrupt_jump()
{
	m_jump = false;
	m_double_jump = false;
	m_ready_jump = true;
	m_ready_double_jump = false;
}

void Babar::interrupt_crouch()
{
    int h_last = m_sprite->curr_pic()->h();
    m_sprite->change_anim(STATIC, m_dir);
    int h = m_sprite->curr_pic()->h();
	move(0, h_last - h);
	m_crouch_time = 0;
}

bool Babar::check_unbind()
{
	Rect rectdown = m_rel_pos;
	rectdown.y += 1;

	if (binded()) {
		if (!Collisions_manager::is_down_coll(m_bind->down_collision_type(m_rel_pos))
			&& !Collisions_manager::is_down_coll(m_bind->down_collision_type(rectdown))) {
			PRINT_DEBUG(1, "AIUYGFSGDF");
			unbind();
			return true;
		}
		// si on descend et qu'on rencontre un static, on s'y arrete
		if (m_bind->is_going_down() && Collisions_manager::is_down_coll(gCollision->get_matrix()->down_collision_type(position()))) {
			unbind();
			PRINT_DEBUG(1, "oIURHGELIUHFGELIUGHLEISHRGHSDLIUH")
			PRINT_DEBUG(1, "oIURHGELIUHFGELIUGHLEISHRGHSDLIUH")
			PRINT_DEBUG(1, "oIURHGELIUHFGELIUGHLEISHRGHSDLIUH")
			PRINT_DEBUG(1, "oIURHGELIUHFGELIUGHLEISHRGHSDLIUH")
			return true;
		}
	}
	return false;
}

void Babar::set_last_pos()
{
    m_pos = m_last_pos;
    m_speed.x = 0;
    m_speed.y = 0;
}
