/**
 * 	@file game_engine.cpp
 * 	@brief implémentation de la classe Game_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>
#include <string>

#include "game_engine.h"
#include "../game/static_data.h"
#include "../game/collisions_manager.h"
#include "../sound/sound_manager.h"
#include "../control/keyboard.h"
#include "../util/debug.h"
#include "../sprites/sprites.h"
#include "../sprites/babar.h"
#include "../sprites/monsters.h"
#include "../sprites/monsters_manager.h"
#include "../sprites/walking_monsters.h"
#include "../sprites/projectiles.h"
#include "../sprites/projectiles_manager.h"
#include "../util/analyser.h"
#include "../video/camera.h"
#include "../util/globals.h"
#include "../control/keyboard.h"
#include "../video/pictures_container.h"
#include "../events/events_manager.h"


Game_engine::Game_engine() : m_monsters_manager(new Monsters_manager()),  m_events_manager(new Events_manager), m_collisions_manager(new Collisions_manager()), m_projectiles_manager(new Projectiles_manager())
{
	m_sound_manager = NULL;
	m_babar = NULL;
}



Game_engine::~Game_engine()
{
    delete m_babar;
	delete m_monsters_manager;
	delete m_events_manager;
	delete m_collisions_manager;
	delete m_projectiles_manager;

}

void Game_engine::init_game_engine(int level, Camera *camera, Static_data *static_data, Sound_manager *sound_manager, Keyboard *keyboard)
{
    std::string rac = RAC;
	std::string rep;
	PRINT_CONSTR(1, "Construction de la classe Game_engine")
	m_sound_manager = sound_manager;
	m_matrix_weight = static_data->static_data_weight();
	m_matrix_height = static_data->static_data_height();
	m_collisions_manager->init_collisions_manager(level);
	std::string str_lvl = "1";
	rep = LEVELS_R;
	Analyser analyser;
	analyser.open(rep + "level" + str_lvl + ".lvl");
	m_monsters_manager->init_monsters_manager(&analyser, sound_manager, static_data->get_pictures_container());
	m_events_manager->init_events_manager(static_data, this);
	m_babar = new Babar(keyboard, static_data, sound_manager);
	m_events_manager->load_events();
	analyser.close();


}

void Game_engine::projectiles_update_pos()
{
	m_projectiles_manager->update_pos(m_collisions_manager);
}

void Game_engine::babar_update_pos(Static_data *static_data)
{
	m_babar->update_pos(static_data, m_collisions_manager);
}


void Game_engine::monsters_update_pos(Static_data*static_data)
{
	m_monsters_manager->monsters_update_pos(static_data, m_collisions_manager);
}

void Game_engine::babar_update_speed()
{
	m_babar->update_speed();
}

void Game_engine::babar_update_state(Static_data *static_data)
{
	m_babar->update_state(static_data, m_collisions_manager, m_projectiles_manager);
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
	m_monsters_manager->display_monsters(*camera);
}


void Game_engine::display_projectiles_friend(Camera *camera)
{
	m_projectiles_manager->display(camera);
}

void Game_engine::delete_old_projectiles_friend(Static_data *static_data)
{
	m_projectiles_manager->delete_old_projectiles(static_data);
}

void Game_engine::update_monsters_projectiles()
{
    m_monsters_manager->init();
    while (!m_monsters_manager->end()) {
		Monster *monster = m_monsters_manager->element();
        for (std::list<Projectile *>::iterator it = m_projectiles_manager->proj_friend_begin();
				it != m_projectiles_manager->proj_friend_end(); it++){
            if ( Collisions_manager::check_collision(monster->position(),(*it)->position()) && !(*it)->dead()) {
                monster->damage((*it)->damage());
                (*it)->kill();
			}
        }                 
        if ( monster->dead() ) {
            m_monsters_manager->delete_element();
        } else {
            m_monsters_manager->next();
        }
    }	
}



Babar *Game_engine::babar()
{
	return m_babar;
}


void Game_engine::update_events_manager() {
	m_events_manager->update();
}

void Game_engine::display_events(Camera *camera) {
	m_events_manager->display_events(camera);
}
