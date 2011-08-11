/**
 * 	@file game.cpp
 * 	@brief ImplÃ©mentation de la classe Game
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

/**
 * Contient la boucle de Game et les paramètres de la partie
 * Sera accessible �  partir de la touche "jouer" du menu
**/


#include "Game.h"

#include "actors/Babar.h"
#include "actors/ProjectilesManager.h"
#include "control/Keyboard.h"
#include "events/EventsManager.h"
#include <events/Stats.h>
#include <game/GameEngine.h>
#include "game/StaticData.h"
#include <menus/PauseMenu.h>
#include <sets/AnimatedSetsManager.h>
#include <sound/Sound.h>
#include <sound/SoundEngine.h>
#include "sprites/SpritesManager.h"
#include "util/debug.h"
#include "video/Camera.h"
#include "video/GraphicEngine.h"
#include "video/Talks.h"
#include <video/TransitionScreen.h>


Game::Game(int level, bool record_on, bool replay_on, std::string output_name, std::string input_name):
	m_pause(NULL)
{
	PRINT_CONSTR(1, "Construction de la classe Game")
    char str[3];
    std::string str_lvl;
    sprintf(str, "%d", level);
    str_lvl = str;
	init_game("level" + str_lvl + ".lvl");
}

Game::Game(std::string level_name)
{
	PRINT_CONSTR(1, "Construction de la classe Game")
	init_game(level_name);
}

void Game::init_game(std::string level_name)
{
	PRINT_TRACE(1, "ouverture de %s", level_name.c_str());
	TransitionScreen * loading = new TransitionScreen("loading.png");
	gSound->init_level(level_name);
	loading->display(gGraphics->get_camera());
    gCollision = new CollisionsManager();
    gProj = new ProjectilesManager();
    gEvent = new EventsManager();
    gStats = new Stats();

	gPlayers = NULL;
	gGameEngine = new GameEngine();
    gStatic = new StaticData();
	gStatic->init_StaticData(level_name);
	gGameEngine->init_GameEngine(level_name, gGraphics->get_camera(),
                                    gGraphics->get_pictures_container());
	gGraphics->init_graphic_engine();
	m_time = m_clock.GetElapsedTime() / 1000;
	m_previous_time = m_clock.GetElapsedTime() / 1000;
	m_pause = NULL;
	set_state_playing();

	gKeyboard->disable_all_keys();
	gKeyboard->disable_key_repeat();


	loading->wait_for_player();
	gSound->play_music();
	m_clock.Reset();
	delete loading;
}

Game::~Game()
{
	PRINT_CONSTR(1, "Destruction de la classe Game")
	delete gGameEngine;
	gGameEngine = NULL;
    delete gPlayers;
    gPlayers = NULL;
    delete gStats;
    gStats = NULL;
	delete gCollision;
	gCollision = NULL;
	delete gProj;
	gProj = NULL;
	delete gEvent;
	gGameEngine = NULL;
    delete gStatic;
	gStatic = NULL;
	gGraphics->clean();
	gKeyboard->disable_all_keys();
	gKeyboard->reset_menu_keys();
	delete m_pause;
	m_pause = NULL;

}

void Game::update_keyboard()
{
	gKeyboard->update_events();
}

void Game::update_game()
{
	gGameEngine->update();
}

void Game::play_sounds()
{
	gGameEngine->play_sounds();
//~ 	gSound->update();
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

	/* affichage des Ã©vÃ©nements */
	gGameEngine->display_events(camera);

    /* Plateformes */
    gCollision->display_platforms(camera);

    /* Sprites */
    gGraphics->display_sprites(camera);

	/* affichage du sprite babar */
	/*camera->display(gBabar);*/

	/* affichage des statics du premier plan */
	gStatic->display_statics_first(camera);

	#ifdef DEBUG_COLL
	gCollision->display_coll(camera);
	#endif

	/* affichage du tableau de board */
	gGraphics->draw_dashboard(camera);

	if (m_pause) {
		m_pause->update_graphics();
	} else if (m_state == gs_talks) {
		gGraphics->get_talks()->display();
	}

	/* mise Ã  jour */
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
	m_clock.Reset();
	while (!end){
		if (m_clock.GetElapsedTime() * 1000 > TIME_LOOP) {
			//** DEBUT DE LA BOUCLE DE JEU **//
			update_keyboard();
			if (m_state == gs_playing) {
				if (gKeyboard->key_down(k_exit)) {
					end = true;
					break;
				}
				update_game();
				if (gKeyboard->key_down(k_escape)) {
					set_state_pause();
				}
				if (gGraphics->get_talks()->isActive()) {
					set_state_talks();
				}
			} else if (m_state == gs_pause) {
				m_pause->update();
				if (m_pause->end_game()) {
					end = true;
					break;
				}
				if (m_pause->end_menu()) {
					set_state_playing();
				}
			} else if (m_state == gs_talks) {
				gGraphics->get_talks()->update();
				if (gGraphics->get_talks()->have_to_leave()) {
					end = true;
					break;
				}
				if (!gGraphics->get_talks()->isActive()) {
					set_state_playing();
				}
			}
			update_graphic();
			play_sounds();
			if (gGameEngine->has_won()) {
				this->play_victory();
				return victory;
			} else if (gGameEngine->has_lost()) {
				return defeat;
			}
			//** FIN DE LA BOUCLE DE JEU **//
			m_clock.Reset();
		} else  {
		    sf::Sleep(float(TIME_LOOP) / 1000 - m_clock.GetElapsedTime());
		}
	}
	return leave;
}

void Game::set_state_playing()
{
	gKeyboard->reset_menu_keys();
	gKeyboard->disable_all_keys();
	m_state = gs_playing;
	if (m_pause) {
		delete m_pause;
		m_pause = NULL;
	}
}

void Game::set_state_pause()
{
	m_state = gs_pause;
	m_pause = new PauseMenu();
}

void Game::set_state_talks()
{
	m_state = gs_talks;
	gKeyboard->reset_menu_keys();
}
