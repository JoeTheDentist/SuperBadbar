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


#include "../actors/babar.h"
#include "../actors/projectiles_manager.h"
#include "../video/camera.h"
#include "../video/graphic_engine.h"
#include "../sound/sound_engine.h"
#include "../menus/pause_menu.h"
#include "../game/game_engine.h"
#include "../game/static_data.h"
#include "../events/events_manager.h"
#include "../sprites/sprites_manager.h"
#include "../events/stats.h"
#include "../sets/animated_set_manager.h"



Game::Game(int level, bool record_on, bool replay_on, std::string output_name, std::string input_name)
{
	PRINT_CONSTR(1, "Construction de la classe Game")
    char str[3];
    std::string str_lvl;
    gKeyboard = new Keyboard(record_on, replay_on, output_name, input_name);
    sprintf(str, "%d", level);
    str_lvl = str;
	init_game(LEVELS_R + "level" + str_lvl + ".lvl");
}

Game::Game(std::string level_name)
{
    gKeyboard = new Keyboard(false, false, "", "");
	PRINT_CONSTR(1, "Construction de la classe Game")
	init_game(level_name);
}

void Game::init_game(std::string level_name)
{
    gCollision = new Collisions_manager();
    gProj = new Projectiles_manager();
    gEvent = new Events_manager();
    gStats = new Stats();

	gBabar = NULL;
	gGame_engine = new Game_engine();
    gStatic = new Static_data();
	gStatic->init_static_data(level_name);
	gGame_engine->init_game_engine(level_name, gGraphics->get_camera(),
                                    gGraphics->get_pictures_container());
	gGraphics->init_graphic_engine();
	m_time = SDL_GetTicks();
	m_previous_time = SDL_GetTicks();
}

Game::~Game()
{
	PRINT_CONSTR(1, "Destruction de la classe Game")
	delete gGame_engine;
	gGame_engine = NULL;
    delete gBabar;
    gBabar = NULL;
    delete gStats;
    gStats = NULL;
	delete gCollision;
	gCollision = NULL;
	delete gProj;
	gProj = NULL;
	delete gEvent;
	gGame_engine = NULL;
    delete gStatic;
	gStatic = NULL;
	gGraphics->clean();
}

void Game::update_keyboard()
{
	gKeyboard->update_events();
}

void Game::update_game()
{
	gGame_engine->update();
}

void Game::play_sounds()
{
	gGame_engine->play_sounds();
}

void Game::update_graphic()
{
	gGraphics->update();

	Camera *camera = gGraphics->get_camera();
	/* affichage du fond */
	camera->update_pos();
	camera->display_background(gStatic->background());

	/* affichage des statics du deuxieme plan */
	gStatic->display_statics_back(camera);

	/* affichage des événements */
	gGame_engine->display_events(camera);

    gGraphics->display_sprites(camera);
    /* */
    gCollision->display_platforms(camera);

	/* affichage du sprite babar */
	/*camera->display(gBabar);*/

	/* affichage des statics du premier plan */
	gStatic->display_statics_first(camera);

	#ifdef DEBUG_COLL
	gCollision->display_coll(camera);
	#endif

	/* affichage du tableau de board */
	gGraphics->draw_dashboard(camera);

	/* mise à jour */
	camera->flip_camera();
}

void Game::play_victory()
{
	std::cout << "You wooooooon" << std::endl;
}

result_game Game::game_loop()
{
	bool end = false;
	gSound->play_music();
	while (!end){
		m_time = SDL_GetTicks();
		if (m_time - m_previous_time > TIME_LOOP) {
			m_previous_time = m_time;
			update_keyboard();
			if (gKeyboard->key_down(k_escape)) {
				Pause_menu *pause = new Pause_menu(end); // end va etre modifie
				delete pause;
			}
			if (gKeyboard->key_down(k_exit)) {
				end = true;
				break;
			}
			update_game();
			update_graphic();
			play_sounds();
			if (gGame_engine->has_won()) {
				this->play_victory();
				return victory;
			} else if (gGame_engine->has_lost()) {
				return defeat;
			}
			m_time = SDL_GetTicks();
		} else  {
		    SDL_Delay(TIME_LOOP - (m_time - m_previous_time));
		}
	}
	return leave;
}

