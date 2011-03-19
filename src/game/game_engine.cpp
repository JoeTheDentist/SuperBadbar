/**
 * 	@file game_engine.cpp
 * 	@brief implémentation de la classe Game_engine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>

#include <stdint.h>
#include <string>

#include "game_engine.h"
#include "../game/static_data.h"
#include "../physic/collisions_manager.h"
#include "../sound/sound_manager.h"
#include "../control/keyboard.h"
#include "../util/debug.h"
#include "../sprites/sprites.h"
#include "../sprites/babar.h"
#include "../sprites/monsters.h"
#include "../sound/sound_engine.h"
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
#include "../video/animation_engine.h"


Game_engine::Game_engine() : 
	m_monsters_manager(new Monsters_manager()),
	m_victory(false)
{
}



Game_engine::~Game_engine()
{
	delete m_monsters_manager;
}


void Game_engine::init_game_engine(std::string level_name, Camera *camera, Keyboard *keyboard,
	Pictures_container *pictures_container)
{
	PRINT_CONSTR(1, "Construction de la classe Game_engine")
	m_matrix_weight = gStatic->static_data_weight();
	m_matrix_height = gStatic->static_data_height();
	gCollision->init_collisions_manager(level_name);
	Analyser analyser;
	analyser.open(level_name);
    gBabar = new Babar(keyboard, &analyser);
	m_monsters_manager->init_monsters_manager(&analyser);
	gEvent->init_events_manager(gStatic, this, pictures_container);
	gEvent->load_events(&analyser);
	analyser.close();	
}

void Game_engine::update()
{
	update_pos();
	update_speed();
	gBabar->update_state();
	m_monsters_manager->babar_monsters_collision();
	gEvent->update();

}

void Game_engine::update_pos()
{
	gCollision->update_platforms_pos();
	gProj->update_pos();
	gBabar->update_pos();
	m_monsters_manager->monsters_update_pos();
	update_monsters_projectiles();
	delete_dead_things();
}


void Game_engine::update_speed()
{
	gBabar->update_speed();
	m_monsters_manager->monsters_update_speed();
	gCollision->update_platforms_speed();
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
                /* animation du sang */
                Rect speed = {0};
                Rect pos = monster->position();
                pos.y = (*it)->position().y;
                char img = '0';
                if ( (*it)->dir() == RIGHT ) {
                    pos.x += pos.w;
                    img++;
                }
                gAnims->add(PIC_R+"animations/blood_"+img+"_", pos, ENDED, speed, false);
                (*it)->kill();
			}
        }
		m_monsters_manager->next();
    }
}


void Game_engine::display_events(Camera *camera) 
{
	gEvent->display_events(camera);
}

void Game_engine::play_sounds()
{
	m_monsters_manager->play_sounds();
	gSound->play_sound(gBabar);
}

void Game_engine::set_victory()
{
	m_victory = true;
}

bool Game_engine::has_won()
{
	return m_victory;
}
