#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>
#include <string>

#include "game_engine.h"
#include "../game/static_data.h"
#include "../sound/sound_manager.h"
#include "../control/keyboard.h"
#include "../util/debug.h"
#include "../sprites/sprites.h"
#include "../sprites/babar.h"
#include "../sprites/monsters.h"
#include "../sprites/monsters_manager.h"
#include "../sprites/walking_monsters.h"
#include "../sprites/projectiles.h"
#include "../util/analyser.h"
#include "../video/camera.h"
#include "../util/collisions.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../video/pictures_container.h"



Game_engine::Game_engine() : m_monsters_manager(new Monsters_manager())
{
	m_sound_manager = NULL;
	m_babar = NULL;
}



Game_engine::~Game_engine()
{
    delete m_babar;
}

void Game_engine::init_game_engine(Camera *camera, Static_data *static_data, Sound_manager *sound_manager, Keyboard *keyboard)
{
    m_projectiles_ennemy.void_list();
    m_projectiles_friend.void_list();
    m_monsters_manager->void_list();

    std::string rac = RAC;
	std::string rep;
	PRINT_CONSTR(1, "Construction de la classe Game_engine")
	m_sound_manager = sound_manager;
	m_matrix_weight = static_data->static_data_weight();
	m_matrix_height = static_data->static_data_height();
	std::string str_lvl = "1";
	Analyser analyser, analyser2;
	rep = LEVELS_R;
	analyser.open(rep + "level" + str_lvl + ".lvl");

    /* Allocation de la matrice de monstres */
	analyser.find_string("#Monsters#");
	int nombre_monstres = analyser.read_int();
	for (int compteur = 0; compteur < nombre_monstres; compteur++) {
		if (analyser.read_string() == "walking_monster") {
			Monster * curr_monster = new Walking_monster(m_sound_manager, &analyser, static_data->get_pictures_container());
			m_monsters_manager->add(curr_monster);

			
		}
	}

//~     analyser2.open(rep + "level" +str_lvl+".lvl");
//~     analyser.fill_monsters(&analyser2, static_data, this);
//~     analyser2.close();
	
	
	/* Creation de babar */
	m_babar = new Babar(&m_projectiles_friend, keyboard, static_data, sound_manager);
	

    /*** Stockage des monstres dans la listes ***/
//~ 	Rect camera_frame, position_target = m_babar->position();
//~ 	camera_frame.h = WINDOW_HEIGHT;
//~ 	camera_frame.w = WINDOW_WEIGHT;
//~ 	camera_frame.x = position_target.x + (position_target.w / 2) - (camera_frame.w / 2);
//~ 	camera_frame.y = position_target.y + (position_target.h / 2) - (camera_frame.h / 2);
//~ 	if (camera_frame.x < 0)
//~ 		camera_frame.x = 0;
//~ 	if (camera_frame.y < 0)
//~ 		camera_frame.y = 0;
//~ 	if ((uint32_t) (camera_frame.x + camera_frame.w) > static_data->static_data_weight())
//~ 		camera_frame.x = static_data->static_data_weight() - camera_frame.w;
//~ 	if ((uint32_t) (camera_frame.y + camera_frame.h) > static_data->static_data_height())
//~ 		camera_frame.y = static_data->static_data_height() - camera_frame.h;

	analyser.close();
}

bool Game_engine::projectiles_friend_end()
{
	return 	m_projectiles_friend.end();
}


void Game_engine::projectiles_friend_update_pos(Static_data *static_data)
{
    m_projectiles_friend.init();
	while(!m_projectiles_friend.end()) {
	    m_projectiles_friend.element()->update_pos(static_data);
	    m_projectiles_friend.next();
	}
}

void Game_engine::babar_update_pos(Static_data *static_data)
{
	m_babar->update_pos(static_data);
}


void Game_engine::monsters_update_pos(Static_data*static_data)
{
	m_monsters_manager->monsters_update_pos(static_data);
}

void Game_engine::babar_update_speed()
{
	m_babar->update_speed();
}

void Game_engine::babar_update_state(Static_data *static_data)
{
	m_babar->update_state(static_data);
}

void Game_engine::babar_monsters_collision()
{
	m_monsters_manager->babar_monsters_collision(m_babar);
}

void Game_engine::monsters_update_speed()
{
	m_monsters_manager->monsters_update_speed(m_babar);
}

void Game_engine::display_monsters(Camera *camera)
{
	m_monsters_manager->display_monsters(camera);
}


void Game_engine::display_projectiles_friend(Camera *camera)
{
    m_projectiles_friend.init();
	while(!projectiles_friend_end()) {
	    camera->display_sprite(m_projectiles_friend.element());
	    m_projectiles_friend.next();
	}
}

void Game_engine::delete_old_projectiles_friend(Static_data *static_data)
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

void Game_engine::update_monsters_projectiles()
{
	List<Monster*>  *monsters = m_monsters_manager->monsters();	
    monsters->init();
    while ( !monsters->end() ) {
        m_projectiles_friend.init();
        while ( !m_projectiles_friend.end() ) {
            if ( check_collision(monsters->element()->position(),m_projectiles_friend.element()->position()) ) {
                monsters->element()->damage(m_projectiles_friend.element()->damage());
                m_projectiles_friend.delete_element(1);
            } else {
                m_projectiles_friend.next();
            }
        }

        if ( monsters->element()->dead() ) {
            monsters->delete_element(1);
        } else {
            monsters->next();
        }
    }
}


void Game_engine::update(Camera *camera)
{

}


List<Projectile*> *Game_engine::projectiles_friend()
{
	return &m_projectiles_friend;
}


Babar *Game_engine::babar()
{
	return m_babar;
}

