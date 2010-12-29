/**
 * 	@file game.cpp
 * 	@brief Implémentation de la classe Game
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

/**
 * Contient la boucle de Game et les paramètres de la partie
 * Sera accessible à partir de la touche "jouer" du menu
**/


#include "../sound/sound.h"
#include "game.h"
#include "../util/debug.h"
#include "../control/keyboard.h"

#include "../sprites/babar.h"
#include "../video/camera.h"
#include "../video/graphic_engine.h"
#include "../game/game_engine.h"
#include "../game/static_data.h"
#include "../events/events_manager.h"
#include "../sound/sound_engine.h"



Game::Game(): m_keyboard(new Keyboard()),m_static_data(new Static_data()), m_game_engine(new Game_engine()), m_graphic_engine(new Graphic_engine()), m_sound_engine(new Sound_engine())
{
	PRINT_CONSTR(1, "Construction de la classe Game")
	m_static_data->init_static_data(1);
	m_game_engine->init_game_engine(1, m_graphic_engine->get_camera(), m_static_data, 
									m_keyboard, m_graphic_engine->get_pictures_container());
	m_graphic_engine->init_graphic_engine(m_game_engine->babar(), m_static_data);
	m_time = SDL_GetTicks();
	m_previous_time = SDL_GetTicks();
}

Game::~Game()
{
	
	PRINT_CONSTR(1, "Destruction de la classe Game")
	delete m_keyboard;
	delete m_static_data;
	delete m_game_engine;
	delete m_graphic_engine;
	delete m_sound_engine;

}

void Game::update_keyboard()
{
	m_keyboard->update_events();
}

void Game::update_game()
{
	
	m_game_engine->update_pos(m_static_data);	
	m_game_engine->update_speed();	
	m_game_engine->babar_update_state(m_static_data);	
	m_game_engine->update_monsters_projectiles();
	m_game_engine->babar_monsters_collision();
	m_game_engine->update_events_manager();
}

void Game::play_sounds()
{
	m_game_engine->play_sounds(m_sound_engine);
}

void Game::delete_dead_things()
{
	m_game_engine->delete_dead_things(m_static_data);
}

void Game::update_graphic()
{
	
	m_graphic_engine->update(m_static_data);

	Camera *camera = m_graphic_engine->get_camera();
	/* affichage du fond */
	camera->update_pos(m_static_data);
	camera->display_background(m_static_data->background());

	/* affichage des statics (à faire en premier car derrière -> p-e pas tous...) */
	m_static_data->display_statics(camera);
	
	/* affichage des événements */
	m_game_engine->display_events(camera);

    /* affichage des monstres */
	m_game_engine->display_monsters(camera);


	/* affichage des projectiles */
	m_game_engine->display_projectiles_friend(camera);
	
	/* affichage du sprite babar */
	camera->display_sprite(m_game_engine->babar());
	
	/* affichage du tableau de board */
	m_graphic_engine->draw_dashboard(m_game_engine->babar()->lifes(), camera, m_game_engine->babar());

	/* mise à jour */
	camera->flip_camera();
}

void Game::game_loop()
{
	int compteur = 0;
	float used_time = 0;
	float used_time_refresh_screen = 0;
	bool end = false;
	int begining = SDL_GetTicks();
	while (!end){
		m_time = SDL_GetTicks();
		if (m_time - m_previous_time > TIME_LOOP) {
			PRINT_TRACE(3,"Cycle de jeu n°%d", compteur)
			compteur++;
			m_previous_time = m_time;
			delete_dead_things();
			update_keyboard();
			if (m_keyboard->key_down(k_exit)) {
				end = true;
				break;
			}
			update_game();
			int begin_refresh = SDL_GetTicks();
			update_graphic();
			play_sounds();
			m_time = SDL_GetTicks();
			used_time += (float)(m_time - m_previous_time)/(float)TIME_LOOP;
			used_time_refresh_screen += (float)(m_time - begin_refresh)/(float)TIME_LOOP;
			if (compteur % PERF_CYCLES == 0) {
				PRINT_PERF("pourcentage d'utilisation du temps: %f", ((used_time * 100) / PERF_CYCLES))
				PRINT_PERF("pourcentage d'utilisation du temps pour le refresh: %f", ((used_time_refresh_screen * 100) / PERF_CYCLES))
				PRINT_PERF("pourcentage d'utilisation du temps pour les calculs: %f", (((used_time - used_time_refresh_screen) * 100) / PERF_CYCLES))
				used_time = 0;
				used_time_refresh_screen = 0;
				
			}
		} else  {
		    SDL_Delay(TIME_LOOP - (m_time - m_previous_time));
		}
	}
	float temps_moyen = (SDL_GetTicks() - begining)/compteur;

	PRINT_PERF("**************************************")
	PRINT_PERF("* temps moyen d'un cycle en ms = %f *", temps_moyen)
	PRINT_PERF("**************************************")
}

