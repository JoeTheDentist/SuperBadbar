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
#include "../sound/sound_engine.h"
#include "../control/keyboard.h"
#include "../util/debug.h"
#include "../actors/actor.h"
#include "../actors/babar.h"
#include "../actors/monsters.h"
#include "../sound/sound_engine.h"
#include "../actors/monsters_manager.h"
#include "../actors/walking_monsters.h"
#include "../actors/projectiles.h"
#include "../actors/projectiles_manager.h"
#include "../util/analyser.h"
#include "../video/camera.h"
#include "../control/keyboard.h"
#include "../video/pictures_container.h"
#include "../events/events_manager.h"
#include "../util/globals.h"
#include "../sets/animated_set_manager.h"
#include "../sprites/sprites_manager.h"
#include "../events/stats.h"
#include "../players/players_manager.h"

Game_engine::Game_engine() :
	m_monsters_manager(new Monsters_manager()),
	m_sets(new Animated_set_manager()),
	m_victory(false)
{
}



Game_engine::~Game_engine()
{
	delete m_monsters_manager;
	delete m_sets;
}


void Game_engine::init_game_engine(std::string level_name, Camera *camera,
	Pictures_container *pictures_container)
{
	PRINT_CONSTR(1, "Construction de la classe Game_engine")
	m_matrix_weight = gStatic->static_data_weight();
	m_matrix_height = gStatic->static_data_height();

	gCollision->init_collisions_manager(LEVELS_R + level_name);
	Analyser analyser;
	analyser.open(LEVELS_R + level_name);

    gPlayers = new Players_manager();
    gPlayers->init_players_manager(&analyser);
	m_monsters_manager->init_monsters_manager(&analyser);
	gEvent->init_events_manager(gStatic, this, pictures_container);
	gEvent->load_events(&analyser);

	m_sets->load_sets(&analyser);
	gEvent->load_triggers(&analyser);

	analyser.close();

	m_spawn = SPAWN_TIME;
}

void Game_engine::update()
{
	update_pos();
	update_speed();
	gPlayers->update();
	gStats->update();
	m_sets->update();
	m_monsters_manager->babar_monsters_collision();
	m_monsters_manager->make_monsters_fire();
	gCollision->update_waiting_list();
	gEvent->update();
	update_monsters_projectiles();
	update_babar_projectiles();
	update_babar_damage();
	delete_dead_things();
}

void Game_engine::update_pos()
{
//	gBabar->update_pos();
	gCollision->update_platforms_pos();
	gProj->update_pos();
	gProj->update_state();
	m_monsters_manager->monsters_update_pos();
}

void Game_engine::update_speed()
{
//	gBabar->update_speed();
	m_monsters_manager->monsters_update_speed();
	gCollision->update_platforms_speed();
	gProj->update_speed();
}

void Game_engine::delete_dead_things()
{
	gProj->delete_old_projectiles();
	m_monsters_manager->delete_dead_monsters();
	gCollision->update_dead_platforms();
}

void Game_engine::update_monsters_projectiles()
{
    m_monsters_manager->init();
    while (!m_monsters_manager->end()) {
		Monster *monster = m_monsters_manager->element();
        for (std::list<Projectile *>::iterator it = gProj->proj_begin(PLAYER1);
				it != gProj->proj_end(PLAYER1); it++){
			if (monster->dead()) {
			    gStats->kill();
				break;
			}
            if ( Collisions_manager::check_collision(monster->position(),(*it)->position()) && !(*it)->dead()) {
                monster->damage((*it)->damage());
                /* animation du sang */
                Rect pos = monster->position();
                pos.y = (*it)->position().y;
                char img = '0';
                if ( (*it)->dir() == RIGHT ) {
                    pos.x += pos.w;
                    img++;
                }
                if ( !(*it)->invincible() ) {
                    (*it)->kill();
                }
			}
        }
		m_monsters_manager->next();
    }
}

void Game_engine::update_babar_projectiles()
{
	for (std::list<Projectile *>::iterator it = gProj->proj_begin(MONSTERS);
				it != gProj->proj_end(MONSTERS); it++) {
            if ( Collisions_manager::check_collision(gPlayers->local_player()->damage_box(),(*it)->position()) && !(*it)->dead()) {
                gStats->hit();
				gPlayers->local_player()->damage(1);
				(*it)->kill();
			}
	}
}

void Game_engine::update_babar_damage()
{
    /* Si Babar sort de l'écran => on lui fait perdre des vie et on le remet à la bonne place */
    if ( !gPlayers->local_player()->locked() && gPlayers->local_player()->position().y + gPlayers->local_player()->position().h >= (int)gStatic->static_data_height() ) {
//~         if ( m_spawn == SPAWN_TIME ) {
            m_sets->add_set("splash/splash",gPlayers->local_player()->position().x, (int)gStatic->static_data_height()-100, false, true, true);
			gPlayers->local_player()->die();
//~             m_spawn--;
//~         } else {
//~             if ( m_spawn == 0) {
//~                 m_spawn = SPAWN_TIME;
//~             } else {
//~                 m_spawn--;
//~             }
//~         }
    }
}

void Game_engine::display_events(Camera *camera)
{
	gEvent->display_events(camera);
}

void Game_engine::play_sounds()
{
	m_monsters_manager->play_sounds();
	gSound->play_sound(gPlayers->local_player());
}

void Game_engine::set_victory()
{
	m_victory = true;
}

bool Game_engine::has_won()
{
	return m_victory;
}

bool Game_engine::has_lost()
{
	return gPlayers->local_player()->lifes() <= 0;
}
