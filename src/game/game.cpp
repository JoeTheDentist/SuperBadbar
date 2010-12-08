/**
 * Contient la boucle de Game et les paramètres de la partie
 * Sera accessible à partir de la touche "jouer" du menu
**/


#include "../sound/sound.h"
#include "game.h"
#include "../util/debug.h"
#include "../util/collisions.h"
#include "../control/keyboard.h"

#include "../sprites/babar.h"
#include "../sprites/monsters.h"
#include "../sprites/projectiles.h"
#include "../util/lists.h"
#include "../sprites/sprites.h"
#include "../sprites/babar.h"
#include "../video/camera.h"
#include "../video/talks.h"
#include "../game/game_engine.h"
#include "../game/static_data.h"
#include "../sound/sound.h"
#include "../sound/sound_manager.h"
#include "../video/statics.h"
#include "../video/dashboard.h"
#include "../events/events_manager.h"



Game::Game(): m_sound_manager(new Sound_manager()), m_keyboard(new Keyboard()),m_static_data(new Static_data()),   m_game_engine(new Game_engine()), m_camera(new Camera), m_talks(new Talks())
{
	PRINT_CONSTR(1, "Construction de la classe Game")
	m_static_data->init_static_data(1);
	m_game_engine->init_game_engine(m_camera, m_static_data, m_sound_manager, m_keyboard);
	m_camera->init_camera(m_game_engine->babar());
	m_talks->init_talks(m_camera, m_static_data->get_pictures_container());
	m_dashboard = new Dashboard(m_static_data->get_pictures_container());
	m_time = SDL_GetTicks();
	m_previous_time = SDL_GetTicks();
	update_camera();
}

Game::~Game()
{
	
	PRINT_CONSTR(1, "Destruction de la classe Game")
	delete m_sound_manager;
	delete m_keyboard;
	delete m_static_data;
	delete m_game_engine;
	delete m_camera;
	delete m_talks;
	delete m_dashboard;
	TTF_Quit();
	PRINT_TRACE(1, "Fermeture de la SDL")
	SDL_Quit();
}

void Game::update_pos()
{
	m_game_engine->babar_monsters_collision();
	m_game_engine->babar_update_pos(m_static_data);
	m_game_engine->projectiles_friend_update_pos(m_static_data);
	m_game_engine->monsters_update_pos(m_static_data);

	
}

void Game::update_speed()
{
	m_game_engine->babar_update_speed();
	m_game_engine->monsters_update_speed();
	m_game_engine->babar_update_state(m_static_data);
}

void Game::update_camera()
{
    m_camera->update_pos(m_static_data);
}

void Game::update_events_manager()
{
	m_game_engine->update_events_manager();
}


void Game::refresh_screen()
{
	/* affichage du fond */
	m_camera->update_pos(m_static_data);
	m_camera->display_background(m_static_data->background());

	/* affichage des statics (à faire en premier car derrière -> p-e pas tous...) */
	m_static_data->display_statics(m_camera);
	
	/* affichage des événements */
	m_game_engine->display_events(m_camera);

    /* affichage des monstres */
	m_game_engine->display_monsters(m_camera);


	/* affichage des projectiles */
	m_game_engine->display_projectiles_friend(m_camera);
	
	
	/* suppression de projectiles trop vieux */
	m_game_engine->delete_old_projectiles_friend(m_static_data);
	
	
	/* affichage du sprite babar */
	m_camera->display_sprite(m_game_engine->babar());
	
	/* affichage du tableau de board */
	m_dashboard->draw_dashboard(m_game_engine->babar()->lifes(), m_camera, m_game_engine->babar());

	/* mise à jour */
	m_camera->flip_camera();
}



void Game::game_loop()
{
	int compteur = 0;
	float used_time = 0;
	bool end = false;
	int begining = SDL_GetTicks();
	m_sound_manager->play_music();
	while (!end){
		m_time = SDL_GetTicks();
		if (m_time - m_previous_time > TIME_LOOP) {
			PRINT_TRACE(3,"Cycle de jeu n°%d", compteur)
			compteur++;
			m_previous_time = m_time;
			m_keyboard->update_events();
			update_events_manager();
			if (m_keyboard->key_down(k_exit))
				end = true;
            m_game_engine->update(m_camera);
			update_speed();
			update_pos();
			check_monsters();
			refresh_screen();
			m_time = SDL_GetTicks();
			used_time += (float)(m_time - m_previous_time)/(float)TIME_LOOP;
			if (compteur % PERF_CYCLES == 0) {
				PRINT_PERF("pourcentage d'utilisation du temps: %d", (int)((used_time * 100) / PERF_CYCLES))
				used_time = 0;
			}
		} else  {
		    SDL_Delay(TIME_LOOP - (m_time - m_previous_time));
		}
	}
	PRINT_PERF("**************************************")
	PRINT_PERF("* temps moyen d'un cycle en ms = %d *", ((SDL_GetTicks() - begining)/compteur))
	PRINT_PERF("**************************************")

}




void Game::check_monsters()
{
	m_game_engine->update_monsters_projectiles();
}


