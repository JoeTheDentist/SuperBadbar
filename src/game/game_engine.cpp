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
#include "../sound/sound_engine.h"
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
#include "../control/keyboard.h"
#include "../video/pictures_container.h"
#include "../events/events_manager.h"
#include "../util/globals.h"


Game_engine::Game_engine() : m_monsters_manager(new Monsters_manager()),  m_events_manager(new Events_manager)
{
    gCollision = new Collisions_manager();
    gProj = new Projectiles_manager;
	m_babar = NULL;
}



Game_engine::~Game_engine()
{
    delete m_babar;
	delete m_monsters_manager;
	delete m_events_manager;
	delete gCollision;
	delete gProj;

}

void Game_engine::init_game_engine(int level, Camera *camera, Keyboard *keyboard, Pictures_container *pictures_container)
{
    std::string rac = RAC;
	std::string rep;
	PRINT_CONSTR(1, "Construction de la classe Game_engine")
	m_matrix_weight = gStatic->static_data_weight();
	m_matrix_height = gStatic->static_data_height();
	gCollision->init_collisions_manager(level);
	std::string str_lvl = "1";
	rep = LEVELS_R;
	Analyser analyser;
	analyser.open(rep + "level" + str_lvl + ".lvl");
    m_babar = new Babar(keyboard, &analyser);
	m_monsters_manager->init_monsters_manager(&analyser, m_babar);
	m_events_manager->init_events_manager(gStatic, this, pictures_container);
	m_events_manager->load_events(&analyser);
	analyser.close();

}

void Game_engine::update_pos()
{
	gCollision->update_platforms_pos(m_babar);
	gProj->update_pos();
	m_babar->update_pos();
	m_monsters_manager->monsters_update_pos();
}


void Game_engine::update_speed()
{
	m_babar->update_speed();
	m_monsters_manager->monsters_update_speed(m_babar);
	gCollision->update_platforms_speed();
}

void Game_engine::babar_update_state()
{
	m_babar->update_state();
}

void Game_engine::babar_monsters_collision()
{
	m_monsters_manager->babar_monsters_collision(m_babar);
}

void Game_engine::display_monsters(Camera * const camera) const
{
	m_monsters_manager->display_monsters(*camera);
	gCollision->display_platforms(camera);
}


void Game_engine::display_projectiles_friend(Camera *camera)
{
	gProj->display(camera);
}

void Game_engine::delete_dead_things()
{
	gProj->delete_old_projectiles();
	m_monsters_manager->delete_dead_monsters();
}

void Game_engine::update_monsters_projectiles()
{
    m_monsters_manager->init();
    while (!m_monsters_manager->end()) {
		Monster *monster = m_monsters_manager->element();
        for (std::list<Projectile *>::iterator it = gProj->proj_friend_begin();
				it != gProj->proj_friend_end(); it++){
			if (monster->dead())
				break;
            if ( Collisions_manager::check_collision(monster->position(),(*it)->position()) && !(*it)->dead()) {
                monster->damage((*it)->damage());
                (*it)->kill();
			}
        }
		m_monsters_manager->next();
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


void Game_engine::play_sounds()
{
	m_monsters_manager->play_sounds();
	gSound->play_sound(m_babar);
}
