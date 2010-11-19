#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>
#include <string>

#include "dynamic_data.h"
#include "../game/static_data.h"
#include "../sound/sound_manager.h"
#include "../control/keyboard.h"
#include "../util/debug.h"
#include "../sprites/sprites.h"
#include "../sprites/babar.h"
#include "../sprites/monsters.h"
#include "../sprites/walking_monsters.h"
#include "../sprites/projectiles.h"
#include "../util/analyser.h"
#include "../video/camera.h"
#include "../util/collisions.h"
#include "../util/globals.h"
#include "../control/keyboard.h"



Dynamic_data::Dynamic_data()
{
	m_sound_manager = NULL;
	m_babar = NULL;
}



Dynamic_data::~Dynamic_data()
{
    m_projectiles_ennemy.~List();
    m_projectiles_friend.~List();
    m_monsters.~List();

    delete m_babar;
}

void Dynamic_data::init_dynamic_data(Camera *camera, Static_data *static_data, Sound_manager *sound_manager, Keyboard *keyboard)
{
    m_projectiles_ennemy.void_list();
    m_projectiles_friend.void_list();
    m_monsters.void_list();

    std::string rac = RAC;
	std::string rep;
	PRINT_CONSTR(1, "Construction de la classe Dynamic_data")
	m_sound_manager = sound_manager;
	m_matrix_weight = static_data->static_data_weight();
	m_matrix_height = static_data->static_data_height();
	std::string str_lvl = "1";
	Analyser analyser, analyser2;
	rep = LEVELS_R;
	analyser.open(rep + "level" + str_lvl + ".lvl");

    /* Allocation de la matrice de monstres */
    analyser2.open(rep + "level" +str_lvl+".lvl");
    analyser.fill_monsters(&analyser2, static_data, this);
    analyser2.close();
	m_babar = new Babar(&m_projectiles_friend, keyboard, static_data, sound_manager);

    /*** Stockage des monstres dans la listes ***/
	SDL_Rect camera_frame, position_target = m_babar->position();
	camera_frame.h = WINDOW_HEIGHT;
	camera_frame.w = WINDOW_WEIGHT;
	camera_frame.x = position_target.x + (position_target.w / 2) - (camera_frame.w / 2);
	camera_frame.y = position_target.y + (position_target.h / 2) - (camera_frame.h / 2);
	if (camera_frame.x < 0)
		camera_frame.x = 0;
	if (camera_frame.y < 0)
		camera_frame.y = 0;
	if ((uint32_t) (camera_frame.x + camera_frame.w) > static_data->static_data_weight())
		camera_frame.x = static_data->static_data_weight() - camera_frame.w;
	if ((uint32_t) (camera_frame.y + camera_frame.h) > static_data->static_data_height())
		camera_frame.y = static_data->static_data_height() - camera_frame.h;

	analyser.close();	
}

bool Dynamic_data::projectiles_friend_end()
{
	return 	m_projectiles_friend.end();
}


void Dynamic_data::projectiles_friend_update_pos(Static_data *static_data)
{
    m_projectiles_friend.init();
	while(!m_projectiles_friend.end()) {
	    m_projectiles_friend.element()->update_pos(static_data);
	    m_projectiles_friend.next();
	}
}

void Dynamic_data::babar_update_pos(Static_data *static_data)
{
	m_babar->update_pos(static_data);
}


void Dynamic_data::monsters_update_pos(Static_data*static_data)
{
    m_monsters.init();
	while(!m_monsters.end()) {
		m_monsters.element()->update_pos(static_data);
		m_monsters.next();
	}
}

void Dynamic_data::babar_update_speed()
{
	m_babar->update_speed();
}

void Dynamic_data::babar_update_state(Static_data *static_data)
{
	m_babar->update_state(static_data);
}

void Dynamic_data::babar_monsters_collision()
{
	SDL_Rect babar_pos = m_babar->position();

	m_monsters.init();
	while(!m_monsters.end()) {
		if (check_collision(m_monsters.element()->position(), babar_pos)) {
			m_babar->damage(1);
		}
	    m_monsters.next();
	}
}

void Dynamic_data::monsters_update_speed()
{
    m_monsters.init();
	while ( !m_monsters.end() ) {
	    m_monsters.element()->update_speed(m_babar);
	    m_monsters.next();
	}
}

void Dynamic_data::display_monsters(Camera *camera)
{
    m_monsters.init();
	while(!m_monsters.end()) {
	    camera->display_sprite(m_monsters.element());
	    m_monsters.next();
	}
}


void Dynamic_data::display_projectiles_friend(Camera *camera)
{
    m_projectiles_friend.init();
	while(!projectiles_friend_end()) {
	    camera->display_sprite(m_projectiles_friend.element());
	    m_projectiles_friend.next();
	}
}

void Dynamic_data::delete_old_projectiles_friend(Static_data *static_data)
{
    m_projectiles_friend.init();
    while ( !m_projectiles_friend.end() ) {
        if ( too_old(m_projectiles_friend.element(),static_data) ) {
            m_projectiles_friend.delete_element(1);
        } else {
            m_projectiles_friend.next();
        }
    }
}

void Dynamic_data::update_monsters_projectiles()
{
    m_monsters.init();
    while ( !m_monsters.end() ) {
        m_projectiles_friend.init();
        while ( !m_projectiles_friend.end() ) {
            if ( check_collision(m_monsters.element()->position(),m_projectiles_friend.element()->position()) ) {
                m_monsters.element()->damage(m_projectiles_friend.element()->damage());
                m_projectiles_friend.delete_element(1);
            } else {
                m_projectiles_friend.next();
            }
        }

        if ( m_monsters.element()->dead() ) {
            m_monsters.delete_element(1);
        } else {
            m_monsters.next();
        }
    }
}

void Dynamic_data::fill_monster_stats(uint32_t i, uint32_t j, uint32_t monster_type, uint32_t begin, uint32_t end, uint32_t life, bool fire, uint32_t speed, Static_data *static_data)
{
    Monster * curr_monster = new Walking_monster(m_sound_manager);
    curr_monster->set_type(monster_type);
    curr_monster->set_pos_x(j*BOX_SIZE);
    curr_monster->set_pos_y(i*BOX_SIZE);
    curr_monster->set_begin(begin);
    curr_monster->set_end(end);
    curr_monster->set_life(life);
    curr_monster->set_fire(fire);
    speed += rand()%4;
    curr_monster->set_speed(speed);
    for (int k=0;k<2;k++) {
        for (int l=0;l<4;l++) {
			SDL_Surface **monster_pics = static_data->monster_pic(k, l);
            curr_monster->set_pic(monster_pics[monster_type],k,l);
//~ 			curr_monster->set_pic(monster_pics[k][l][monster_type],k,l);
        }
    }
    m_monsters.add(curr_monster);
}


void Dynamic_data::update(Camera *camera)
{

}

List<Projectile*> *Dynamic_data::projectiles_friend()
{
	return &m_projectiles_friend;
}


Babar *Dynamic_data::babar()
{
	return m_babar;
}

