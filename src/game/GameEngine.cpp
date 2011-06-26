/**
 * 	@file GameEngine.cpp
 * 	@brief implémentation de la classe GameEngine
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include <iostream>

#include <stdint.h>
#include <string>

#include "GameEngine.h"
#include "../game/StaticData.h"
#include "../physic/CollisionsManager.h"
#include "../sound/SoundEngine.h"
#include "../control/Keyboard.h"
#include "../util/debug.h"
#include "../actors/Actor.h"
#include "../actors/Babar.h"
#include "../actors/Monster.h"
#include "../sound/SoundEngine.h"
#include "../actors/MonstersManager.h"
#include "../actors/WalkingMonster.h"
#include "../actors/Projectile.h"
#include "../actors/ProjectilesManager.h"
#include "../util/Analyser.h"
#include "../video/Camera.h"
#include "../control/Keyboard.h"
#include "../video/PicturesContainer.h"
#include "../events/EventsManager.h"
#include "../util/globals.h"
#include "../sets/AnimatedSetsManager.h"
#include "../sprites/SpritesManager.h"
#include "../events/Stats.h"
#include "../players/PlayersManager.h"

int PlayersManager::last_peanuts = 0;
int PlayersManager::last_lifes = 3;

GameEngine::GameEngine() :
	m_monsters_manager(new Monsters_manager()),
	m_sets(new AnimatedSetManager()),
	m_victory(false)
{
}

GameEngine::~GameEngine()
{
	delete m_monsters_manager;
	delete m_sets;
}


void GameEngine::init_GameEngine(std::string level_name, Camera *camera,
	PicturesContainer *PicturesContainer)
{

	PRINT_CONSTR(1, "Construction de la classe GameEngine")
	m_matrix_weight = gStatic->StaticData_width();
	m_matrix_height = gStatic->StaticData_height();

	gCollision->init_collisions_manager(LEVELS_R + level_name);
	Analyser analyser;
	analyser.open(LEVELS_R + level_name);

    gPlayers = new PlayersManager();
    gPlayers->init_players_manager(&analyser);
    gPlayers->local_player()->set_peanuts(PlayersManager::last_peanuts);
    gPlayers->local_player()->set_lifes(PlayersManager::last_lifes);
	m_monsters_manager->init_monsters_manager(&analyser);
	gEvent->init_EventsManager(gStatic, this, PicturesContainer);
	gEvent->load_events(&analyser);

	m_sets->load_sets(&analyser);
	gEvent->load_triggers(&analyser);

	analyser.close();

	m_spawn = SPAWN_TIME;
}

void GameEngine::update()
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

void GameEngine::update_pos()
{
//	gBabar->update_pos();
	gCollision->update_platforms_pos();
	gProj->update_pos();
	gProj->update_state();
	m_monsters_manager->monsters_update_pos();
}

void GameEngine::update_speed()
{
//	gBabar->update_speed();
	m_monsters_manager->monsters_update_speed();
	gCollision->update_platforms_speed();
	gProj->update_speed();
}

void GameEngine::delete_dead_things()
{
	gProj->delete_old_projectiles();
	m_monsters_manager->delete_dead_monsters();
	gCollision->update_dead_platforms();
}

void GameEngine::update_monsters_projectiles()
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
            if ( CollisionsManager::check_collision(monster->position(),(*it)->position()) && !(*it)->dead()) {
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

void GameEngine::update_babar_projectiles()
{
	for (std::list<Projectile *>::iterator it = gProj->proj_begin(MONSTERS);
				it != gProj->proj_end(MONSTERS); it++) {
            if ( CollisionsManager::check_collision(gPlayers->local_player()->damage_box(),(*it)->position()) && !(*it)->dead()) {
                gStats->hit();
				gPlayers->local_player()->damage(1);
				(*it)->kill();
			}
	}
}

void GameEngine::update_babar_damage()
{
    /* Si Babar sort de l'écran => on lui fait perdre des vie et on le remet à la bonne place */
    if ( !gPlayers->local_player()->locked() && gPlayers->local_player()->position().y + gPlayers->local_player()->position().h >= (int)gStatic->StaticData_height() ) {
//~         if ( m_spawn == SPAWN_TIME ) {
            m_sets->add_set(PIC_ANIMATIONS_R+"splash/splash",gPlayers->local_player()->position().x, (int)gStatic->StaticData_height()-100, false, true, true);
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

void GameEngine::display_events(Camera *camera)
{
	gEvent->display_events(camera);
}

void GameEngine::play_sounds()
{
	m_monsters_manager->play_sounds();
	gSound->play_sound(gPlayers->local_player());
}

void GameEngine::set_victory()
{
	m_victory = true;
}

bool GameEngine::has_won()
{
	return m_victory;
}

bool GameEngine::has_lost()
{
	return gPlayers->local_player()->lifes() <= 0;
}
